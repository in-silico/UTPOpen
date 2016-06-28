import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Writer;
import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.StringTokenizer;

public class tobbybones {
  private static final boolean SHOULD_BUFFER_OUTPUT = false;

  static final SuperWriter sw = new SuperWriter(System.out);

  static final SuperScanner sc = new SuperScanner();

  static class Node {
    int priority;
    Node left, right;
    Node lastParent;
    int valueSum;
    int value;
    final int key;

    Node(int key) {
      this.key = key;
    }

    Node get(boolean isLeft) {
      return isLeft ? left : right;
    }

    void set(boolean isLeft, Node node) {
      if (isLeft) {
        left = node;
      } else {
        right = node;
      }
      if (node != null) {
        node.lastParent = this;
      }
    }

    void afterChange() {
      valueSum = value;
      if (left != null) {
        valueSum += left.valueSum;
      }
      if (right != null) {
        valueSum += right.valueSum;
      }
    }
  }

  static enum VisitAnswer {
    CURRENT, LEFT, RIGHT;

    Node lastNode;
  }

  static abstract class NodeVisitor {

    void allBefore(Node node) {}

    void before(Node node) {}

    abstract VisitAnswer visitNode(Node node);
  }

  static abstract class Treap {
    static final int MAX_RANDOM = Integer.MAX_VALUE >> 1;
    static final Random random = new Random(2);

    Node root;

    static class Answer {
      Node node;
      VisitAnswer answer;
    }

    VisitAnswer visit(NodeVisitor visitor) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      lastAnswer.lastNode = null;
      Node current = root;
      while (current != null) {
        current.lastParent = lastAnswer.lastNode;
        lastAnswer = visitor.visitNode(current);
        lastAnswer.lastNode = current;
        if (lastAnswer == VisitAnswer.LEFT) {
          current = current.left;
        } else if (lastAnswer == VisitAnswer.RIGHT) {
          if (current.left != null) {
            visitor.allBefore(current.left);
          }
          visitor.before(current);
          current = current.right;
        } else {
          if (current.left != null) {
            visitor.allBefore(current.left);
          }
          break;
        }
      }
      return lastAnswer;
    }

    VisitAnswer visitSearch(int key) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      lastAnswer.lastNode = null;
      Node current = root;
      while (current != null) {
        current.lastParent = lastAnswer.lastNode;
        if (current.key > key) {
          VisitAnswer.LEFT.lastNode = current;
          current = current.left;
          lastAnswer = VisitAnswer.LEFT;
        } else if (current.key < key) {
          VisitAnswer.RIGHT.lastNode = current;
          current = current.right;
          lastAnswer = VisitAnswer.RIGHT;
        } else {
          VisitAnswer.CURRENT.lastNode = current;
          lastAnswer = VisitAnswer.CURRENT;
          break;
        }
      }
      return lastAnswer;
    }

    void rotateLeft(Node node) {
      Node previousParent = node.lastParent;
      Node p = node.left;
      Node a = p.left;
      Node b = p.right;
      Node c = node.right;
      if (previousParent != null) {
        previousParent.set(previousParent.left == node, p);
      } else {
        p.lastParent = null;
        root = p;
      }
      p.right = node;
      p.left = a;
      node.left = b;
      node.right = c;
      node.lastParent = p;
      if (a != null) {
        a.lastParent = p;
      }
      if (b != null) {
        b.lastParent = node;
      }
      if (c != null) {
        c.lastParent = node;
      }
      node.afterChange();
      p.afterChange();
      if (previousParent != null) {
        previousParent.afterChange();
      }
    }

    void rotateRight(Node node) {
      Node previousParent = node.lastParent;
      Node p = node.right;
      Node a = p.right;
      Node b = p.left;
      Node c = node.left;
      if (previousParent != null) {
        previousParent.set(previousParent.left == node, p);
      } else {
        p.lastParent = null;
        root = p;
      }
      p.left = node;
      p.right = a;
      node.right = b;
      node.left = c;
      node.lastParent = p;
      if (a != null) {
        a.lastParent = p;
      }
      if (b != null) {
        b.lastParent = node;
      }
      if (c != null) {
        c.lastParent = node;
      }
      node.afterChange();
      p.afterChange();
      if (previousParent != null) {
        previousParent.afterChange();
      }
    }

    boolean fixPriorityDown(Node node) {
      int highestPriority = node.priority;
      boolean isLeft = true;
      if (node.left != null) {
        highestPriority = node.left.priority;
      }
      if (node.right != null) {
        if (node.right.priority > highestPriority) {
          highestPriority = node.right.priority;
          isLeft = false;
        }
      }
      if (highestPriority <= node.priority) {
        return false;
      }
      if (isLeft) {
        rotateLeft(node);
      } else {
        rotateRight(node);
      }
      return true;
    }

    void fixPriority(Node node) {
      while (true) {
        if (node.lastParent != null && node.priority > node.lastParent.priority) {
          if (node.lastParent.left == node) {
            rotateLeft(node.lastParent);
          } else {
            rotateRight(node.lastParent);
          }
        } else {
          if (!fixPriorityDown(node)) {
            return;
          }
          fixPriority(node.lastParent);
        }
      }
    }

    void propagateChange(Node node) {
      while (node != null) {
        node.afterChange();
        node = node.lastParent;
      }
    }

    void add(Node node, int key) {
      node.priority = random.nextInt(MAX_RANDOM);
      if (root == null) {
        root = node;
        root.lastParent = null;
        return;
      }
      VisitAnswer visitAnswer = visitSearch(key);
      node.lastParent = visitAnswer.lastNode;
      node.lastParent.set(visitAnswer == VisitAnswer.LEFT, node);
      node.lastParent.afterChange();
      fixPriority(node);
      propagateChange(node);
    }

    void remove(int key) {
      VisitAnswer visitAnswer = visitSearch(key);
      Node toDelete = visitAnswer.lastNode;
      toDelete.priority = -1;
      fixPriority(toDelete);
      if (toDelete.lastParent != null) {
        toDelete.lastParent.set(toDelete.lastParent.left == toDelete, null);
        toDelete.lastParent.afterChange();
        propagateChange(toDelete.lastParent);
      } else {
        root = null;
      }
    }
  }

  static class LessThanVisitor extends NodeVisitor {
    final int searchedKey;
    int answer = 0;

    LessThanVisitor(int searchedKey) {
      this.searchedKey = searchedKey;
    }

    @Override
    void allBefore(Node node) {
      answer += node.valueSum;
    }

    @Override
    void before(Node node) {
      answer += node.value;
    }

    @Override
    VisitAnswer visitNode(Node node) {
      if (node.key == searchedKey) {
        return VisitAnswer.CURRENT;
      } else if (node.key < searchedKey) {
        return VisitAnswer.RIGHT;
      } else {
        return VisitAnswer.LEFT;
      }
    }
  }

  static class ValueMapTreap extends Treap {

    public void add(int key) {
      VisitAnswer answer = visitSearch(key);
      if (root != null && answer == VisitAnswer.CURRENT) {
        Node valueNode = answer.lastNode;
        valueNode.value++;
        propagateChange(valueNode);
        return;
      }
      Node newNode = new Node(key);
      newNode.value = 1;
      add(newNode, key);
    }

    public int get(int key) {
      VisitAnswer answer = visitSearch(key);
      if (answer == VisitAnswer.CURRENT) {
        Node valueNode = answer.lastNode;
        return valueNode.value;
      }
      return 0;
    }

    public void removeKey(int key) {
      VisitAnswer answer = visitSearch(key);
      if (answer == VisitAnswer.CURRENT) {
        Node valueNode = answer.lastNode;
        if (valueNode.value == 1) {
          remove(key);
        } else {
          valueNode.value--;
          propagateChange(valueNode);
        }
      }
    }

    public int getLessThan(int key) {
      LessThanVisitor visitor = new LessThanVisitor(key);
      visit(visitor);
      return visitor.answer;
    }
  }

  static class SegmentTree
  {
    ValueMapTreap[] M;

    public SegmentTree(int size)
    {
      M = new ValueMapTreap[size * 4 + 4];
      for (int i = 0; i < M.length; i++) {
        M[i] = new ValueMapTreap();
      }
    }

    //it's initially called update(1, 0, size - 1, pos, value)
    void update(int node, int b, int e, int pos, int previousValue, int newValue)
    {
      //if the current interval doesn't intersect
      //the updated position return -1
      if (pos > e || pos < b)
        return;
      //if the current interval is the updated position
      //then update it
      if (b != e) {
        update(2 * node, b, (b + e) / 2, pos, previousValue, newValue);
        update(2 * node + 1, (b + e) / 2 + 1, e, pos, previousValue, newValue);
      }
      if (previousValue != -1) {
        M[node].removeKey(previousValue);
      }
      M[node].add(newValue);
    }

    //it's initially called query(1, 0, size - 1, i, j)
    int query(int node, int b, int e, int i, int j, int lessThan)
    {
      //if the current interval doesn't intersect
      //the query interval return 0
      if (i > e || j < b)
        return 0;

      //if the current interval is completely included in
      //the query interval return the value of this node
      if (b >= i && e <= j) {
        return M[node].getLessThan(lessThan);
      }

      //compute the value from
      //left and right part of the interval
      int p1 = query(2 * node, b, (b + e) / 2, i, j, lessThan);
      int p2 = query(2 * node + 1, (b + e) / 2 + 1, e, i, j, lessThan);
      //join them to generate result
      return p1 + p2;
    }
  }

  public static void main() {
    while (true) {
      int n = sc.nextIntOrQuit();
      int m = sc.nextInt();
      SegmentTree st = new SegmentTree(n);
      int[] values = new int[n];
      Arrays.fill(values, -1);
      for (int l = 0; l < m; l++) {
        int q = sc.nextInt();
        if (q == 0) {
          int i = sc.nextInt();
          int b = sc.nextInt();
          st.update(1, 0, n - 1, i, values[i], b);
          values[i] = b;
        } else {
          int i = sc.nextInt();
          int j = sc.nextInt();
          int s = sc.nextInt();
          int answer = st.query(1, 0, n - 1, i, j, s + 1);
          sw.printLine(answer);
        }
      }
    }
  }

  static class LineScanner extends Scanner {
    private StringTokenizer st;

    public LineScanner(String input) {
      st = new StringTokenizer(input);
    }

    @Override
    public String next() {
      return st.hasMoreTokens() ? st.nextToken() : null;
    }

    @Override
    public String nextLine() {
      throw new RuntimeException("not supported");
    }

    public boolean hasNext() {
      return st.hasMoreTokens();
    }

    private final ArrayList<Object> temp = new ArrayList<Object>();

    private void fillTemp() {
      while (st.hasMoreTokens()) {
        temp.add(st.nextToken());
      }
    }

    public String[] asStringArray() {
      fillTemp();
      String[] answer = new String[temp.size()];
      for (int i = 0; i < answer.length; i++) {
        answer[i] = (String) temp.get(i);
      }
      temp.clear();
      return answer;
    }

    public int[] asIntArray() {
      fillTemp();
      int[] answer = new int[temp.size()];
      for (int i = 0; i < answer.length; i++) {
        answer[i] = Integer.parseInt((String) temp.get(i));
      }
      temp.clear();
      return answer;
    }

    public long[] asLongArray() {
      fillTemp();
      long[] answer = new long[temp.size()];
      for (int i = 0; i < answer.length; i++) {
        answer[i] = Long.parseLong((String) temp.get(i));
      }
      temp.clear();
      return answer;
    }

    public double[] asDoubleArray() {
      fillTemp();
      double[] answer = new double[temp.size()];
      for (int i = 0; i < answer.length; i++) {
        answer[i] = Double.parseDouble((String) temp.get(i));
      }
      temp.clear();
      return answer;
    }
  }

  static class SuperScanner extends Scanner {
    private InputStream stream;
    private byte[] buf = new byte[8096];
    private int curChar;
    private int numChars;

    public SuperScanner() {
        this.stream = System.in;
    }

    public int read() {
        if (numChars == -1)
          return -1;
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0)
                return -1;
        }
        return buf[curChar++];
    }

    public static boolean isWhitespace(int c) {
      return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }

    public static boolean isLineEnd(int c) {
      return c == '\n' || c == -1;
    }

    private final StringBuilder sb = new StringBuilder();

    @Override
    public String next() {
      int c = read();
      while (isWhitespace(c)) {
          if (c == -1) {
            return null;
          }
          c = read();
      }
      sb.setLength(0);
      do {
          sb.append((char) c);
          c = read();
      } while (!isWhitespace(c));
      return sb.toString();
    }

    @Override
    public String nextLine() {
      sb.setLength(0);
      int c;
      while (true) {
        c = read();
        if (!isLineEnd(c)) {
          sb.append((char) c);
        } else {
          break;
        }
      }
      if (c == -1 && sb.length() == 0) {
        return null;
      } else {
        if (sb.length() > 0 && sb.charAt(sb.length() - 1) == '\r') {
          return sb.substring(0, sb.length() - 1);
        } else {
          return sb.toString();
        }
      }
    }

    public LineScanner nextLineScanner() {
      String line = nextLine();
      if (line == null) {
        return null;
      } else {
        return new LineScanner(line);
      }
    }

    public LineScanner nextNonEmptyLineScanner() {
      while (true) {
        String line = nextLine();
        if (line == null) {
          return null;
        } else if (!line.isEmpty()) {
          return new LineScanner(line);
        }
      }
    }

    @Override
    public int nextInt() {
        int c = read();
        while (isWhitespace(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9')
                throw new InputMismatchException();
            res = (res << 3) + (res << 1);
            res += c - '0';
            c = read();
        } while (!isWhitespace(c));
        return res * sgn;
    }

    @Override
    public long nextLong() {
        int c = read();
        while (isWhitespace(c))
            c = read();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        long res = 0;
        do {
            if (c < '0' || c > '9')
                throw new InputMismatchException();
            res = (res << 3) + (res << 1);
            res += c - '0';
            c = read();
        } while (!isWhitespace(c));
        return res * sgn;
    }
  }

  static abstract class Scanner {

    public abstract String next();

    public abstract String nextLine();

    public int nextIntOrQuit() {
      Integer n = nextInteger();
      if (n == null) {
        sw.close();
        System.exit(0);
      }
      return n.intValue();
    }

    public int nextInt() {
      return Integer.parseInt(next());
    }

    public long nextLong() {
      return Long.parseLong(next());
    }

    public double nextDouble() {
      return Double.parseDouble(next());
    }

    public int[] nextIntArray(int n) {
      int[] res = new int[n];
      for (int i = 0; i < res.length; i++)
        res[i] = nextInt();
      return res;
    }

    public long[] nextLongArray(int n) {
      long[] res = new long[n];
      for (int i = 0; i < res.length; i++)
        res[i] = nextLong();
      return res;
    }

    public double[] nextDoubleArray(int n) {
      double[] res = new double[n];
      for (int i = 0; i < res.length; i++)
        res[i] = nextDouble();
      return res;
    }

    public void sortIntArray(int[] array) {
      Integer[] vals = new Integer[array.length];
      for (int i = 0; i < array.length; i++)
        vals[i] = array[i];
      Arrays.sort(vals);
      for (int i = 0; i < array.length; i++)
        array[i] = vals[i];
    }

    public void sortLongArray(long[] array) {
      Long[] vals = new Long[array.length];
      for (int i = 0; i < array.length; i++)
        vals[i] = array[i];
      Arrays.sort(vals);
      for (int i = 0; i < array.length; i++)
        array[i] = vals[i];
    }

    public void sortDoubleArray(double[] array) {
      Double[] vals = new Double[array.length];
      for (int i = 0; i < array.length; i++)
        vals[i] = array[i];
      Arrays.sort(vals);
      for (int i = 0; i < array.length; i++)
        array[i] = vals[i];
    }

    public String[] nextStringArray(int n) {
      String[] vals = new String[n];
      for (int i = 0; i < n; i++)
        vals[i] = next();
      return vals;
    }

    public Integer nextInteger() {
      String s = next();
      if (s == null)
        return null;
      return Integer.parseInt(s);
    }

    public int[][] nextIntMatrix(int n, int m) {
      int[][] ans = new int[n][];
      for (int i = 0; i < n; i++)
        ans[i] = nextIntArray(m);
      return ans;
    }

    public char[][] nextGrid(int r) {
      char[][] grid = new char[r][];
      for (int i = 0; i < r; i++)
        grid[i] = next().toCharArray();
      return grid;
    }

    public static <T> T fill(T arreglo, int val) {
      if (arreglo instanceof Object[]) {
        Object[] a = (Object[]) arreglo;
        for (Object x : a)
          fill(x, val);
      } else if (arreglo instanceof int[])
        Arrays.fill((int[]) arreglo, val);
      else if (arreglo instanceof double[])
        Arrays.fill((double[]) arreglo, val);
      else if (arreglo instanceof long[])
        Arrays.fill((long[]) arreglo, val);
      return arreglo;
    }

    public <T> T[] nextObjectArray(Class<T> clazz, int size) {
      @SuppressWarnings("unchecked")
      T[] result = (T[]) java.lang.reflect.Array.newInstance(clazz, size);
      for (int c = 0; c < 3; c++) {
        Constructor<T> constructor;
        try {
          if (c == 0)
            constructor = clazz.getDeclaredConstructor(Scanner.class,
                Integer.TYPE);
          else if (c == 1)
            constructor = clazz.getDeclaredConstructor(Scanner.class);
          else
            constructor = clazz.getDeclaredConstructor();
        } catch (Exception e) {
          continue;
        }
        try {
          for (int i = 0; i < result.length; i++) {
            if (c == 0)
              result[i] = constructor.newInstance(this, i);
            else if (c == 1)
              result[i] = constructor.newInstance(this);
            else
              result[i] = constructor.newInstance();
          }
        } catch (Exception e) {
          throw new RuntimeException(e);
        }
        return result;
      }
      throw new RuntimeException("Constructor not found");
    }

    public Collection<Integer> wrap(int[] as) {
      ArrayList<Integer> ans = new ArrayList<Integer>();
      for (int i : as)
        ans.add(i);
      return ans;
    }

    public int[] unwrap(Collection<Integer> collection) {
      int[] vals = new int[collection.size()];
      int index = 0;
      for (int i : collection)
        vals[index++] = i;
      return vals;
    }

    int testCases = Integer.MIN_VALUE;

    boolean testCases() {
      if (testCases == Integer.MIN_VALUE) {
        testCases = nextInt();
      }
      return --testCases >= 0;
    }
  }

  static class SuperWriter {

    private final PrintWriter writer;

    public SuperWriter(OutputStream outputStream) {
      writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
    }

    public SuperWriter(Writer writer) {
        this.writer = new PrintWriter(writer);
    }

    public void close() {
        writer.flush();
        writer.close();
    }

    public void printLine(String line) {
      writer.println(line);
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public void printLine(int... vals) {
      if (vals.length == 0) {
        writer.println();
      } else {
        writer.print(vals[0]);
        for (int i = 1; i < vals.length; i++)
          writer.print(" ".concat(String.valueOf(vals[i])));
        writer.println();
      }
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public void printLine(long... vals) {
      if (vals.length == 0) {
        writer.println();
      } else {
        writer.print(vals[0]);
        for (int i = 1; i < vals.length; i++)
          writer.print(" ".concat(String.valueOf(vals[i])));
        writer.println();
      }
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public void printLine(double... vals) {
      if (vals.length == 0) {
        writer.println();
      } else {
        writer.print(vals[0]);
        for (int i = 1; i < vals.length; i++)
          writer.print(" ".concat(String.valueOf(vals[i])));
        writer.println();
      }
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public void printLine(int prec, double... vals) {
      if (vals.length == 0) {
        writer.println();
      } else {
        String precision = "%." + prec + "f";
        writer.print(String.format(precision, vals[0]).replace(',', '.'));
        precision = " " + precision;
        for (int i = 1; i < vals.length; i++)
          writer.print(String.format(precision, vals[i]).replace(',', '.'));
        writer.println();
      }
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public <Z> void printLine(Collection<Z> vals) {
      if (vals.size() == 0) {
        writer.println();
      } else {
        int i = 0;
        for (Z val : vals) {
          if (i++ == 0) {
            writer.print(val.toString());
          } else {
            writer.print(" ".concat(val.toString()));
          }
        }
        writer.println();
      }
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public void printSimple(String value) {
      writer.print(value);
      if (!SHOULD_BUFFER_OUTPUT) {
        writer.flush();
      }
    }

    public boolean ifZeroExit(Number... values) {
    	for (Number number : values) {
    		if (number.doubleValue() != 0.0d || number.longValue() != 0) {
    			return false;
    		}
    	}
    	close();
    	System.exit(0);
    	return true;
    }
  }

  public static void main(String[] args) {
    main();
    sw.close();
  }
}
