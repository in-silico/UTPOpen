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

public class tobbystones {

  private static final boolean SHOULD_BUFFER_OUTPUT = false;

  static final SuperWriter sw = new SuperWriter(System.out);

  static final SuperScanner sc = new SuperScanner();

  static class Node {
    //   BASE NODE   //
    int priority;
    Node left, right;
    Node lastParent;

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
    // END BASE NODE //

    boolean reversePending = false;
    boolean reverseColorPending = false;
    Boolean setPending;
    boolean white = true;
    int whiteCount;
    int blackCount;

    void beforeVisit() {
      if (reversePending) {
        if (left != null) {
          left.reversePending = !left.reversePending;
        }
        if (right != null) {
          right.reversePending = !right.reversePending;
        }
        Node tmp = left;
        left = right;
        right = tmp;
        reversePending = false;
      }
      if (reverseColorPending) {
        if (left != null) {
          left.flipReverseColorPending();
        }
        if (right != null) {
          right.flipReverseColorPending();
        }
        white = !white;
        reverseColorPending = false;
        int tmp = whiteCount;
        whiteCount = blackCount;
        blackCount = tmp;
      }
      if (setPending != null) {
        if (left != null) {
          left.setSetPending(setPending);
        }
        if (right != null) {
          right.setSetPending(setPending);
        }
        white = setPending;
        int count = getCount();
        if (setPending) {
          whiteCount = count;
          blackCount = 0;
        } else {
          whiteCount = 0;
          blackCount = count;
        }
        setPending = null;
      }
    }

    void flipReverseColorPending() {
      if (setPending != null) {
        setPending = !setPending;
      } else {
        reverseColorPending = !reverseColorPending;
      }
    }

    void setSetPending(boolean value) {
      if (reverseColorPending) {
        reverseColorPending = false;
      }
      setPending = value;
    }

    int whiteCount() {
      if (setPending != null) {
        return setPending ? getCount() : 0;
      }
      return reverseColorPending ? blackCount : whiteCount;
    }

    int blackCount() {
      if (setPending != null) {
        return setPending ? 0 : getCount();
      }
      return reverseColorPending ? whiteCount : blackCount;
    }

    boolean currentColor() {
      if (setPending != null) {
        return setPending;
      }
      return reverseColorPending ? !white : white;
    }

    void afterChange() {
      whiteCount = white ? 1 : 0;
      if (left != null) {
        whiteCount += left.whiteCount();
      }
      if (right != null) {
        whiteCount += right.whiteCount();
      }
      blackCount = white ? 0 : 1;
      if (left != null) {
        blackCount += left.blackCount();
      }
      if (right != null) {
        blackCount += right.blackCount();
      }
    }

    int getCount() {
      return whiteCount + blackCount;
    }
  }

  static enum VisitAnswer {
    CURRENT, LEFT, RIGHT;
  }

  static abstract class NodeVisitor {
    Node lastNode;

    abstract VisitAnswer visitNode(Node node);

    VisitAnswer visit(Node root) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      Node current = root;
      lastNode = null;
      while (current != null) {
        current.lastParent = lastNode;
        current.beforeVisit();
        lastNode = current;
        lastAnswer = visitNode(current);
        if (lastAnswer == VisitAnswer.LEFT) {
          current = current.left;
        } else if (lastAnswer == VisitAnswer.RIGHT) {
          current = current.right;
        } else {
          break;
        }
      }
      return lastAnswer;
    }
  }

  static abstract class BeforeNodeVisitor extends NodeVisitor {

    abstract void before(Node node);

    abstract void allBefore(Node node);

    @Override
    VisitAnswer visit(Node root) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      Node current = root;
      lastNode = null;
      while (current != null) {
        current.lastParent = lastNode;
        current.beforeVisit();
        lastNode = current;
        lastAnswer = visitNode(current);
        if (lastAnswer == VisitAnswer.LEFT) {
          current = current.left;
        } else if (lastAnswer == VisitAnswer.RIGHT) {
          if (current.left != null) {
            current.left.beforeVisit();
            allBefore(current.left);
          }
          before(current);
          current = current.right;
        } else {
          if (current.left != null) {
            current.left.beforeVisit();
            allBefore(current.left);
          }
          break;
        }
      }
      return lastAnswer;
    }
  }

  static abstract class AfterNodeVisitor extends NodeVisitor {

    abstract void after(Node node);

    abstract void allAfter(Node node);

    @Override
    VisitAnswer visit(Node root) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      Node current = root;
      lastNode = null;
      while (current != null) {
        current.lastParent = lastNode;
        current.beforeVisit();
        lastNode = current;
        lastAnswer = visitNode(current);
        if (lastAnswer == VisitAnswer.LEFT) {
          if (current.right != null) {
            current.right.beforeVisit();
            allAfter(current.right);
          }
          after(current);
          current = current.left;
        } else if (lastAnswer == VisitAnswer.RIGHT) {
          current = current.right;
        } else {
          if (current.right != null) {
            current.right.beforeVisit();
            allAfter(current.right);
          }
          break;
        }
      }
      return lastAnswer;
    }
  }

  static abstract class ComplexNodeVisitor extends NodeVisitor {

    abstract void before(Node node);

    abstract void allBefore(Node node);

    abstract void after(Node node);

    abstract void allAfter(Node node);

    @Override
    VisitAnswer visit(Node root) {
      VisitAnswer lastAnswer = VisitAnswer.CURRENT;
      Node current = root;
      lastNode = null;
      while (current != null) {
        current.lastParent = lastNode;
        current.beforeVisit();
        lastNode = current;
        lastAnswer = visitNode(current);
        if (lastAnswer == VisitAnswer.LEFT) {
          if (current.right != null) {
            current.right.beforeVisit();
            allAfter(current.right);
          }
          after(current);
          current = current.left;
        } else if (lastAnswer == VisitAnswer.RIGHT) {
          if (current.left != null) {
            current.left.beforeVisit();
            allBefore(current.left);
          }
          before(current);
          current = current.right;
        } else {
          if (current.left != null) {
            current.left.beforeVisit();
            allBefore(current.left);
          }
          if (current.right != null) {
            current.right.beforeVisit();
            allAfter(current.right);
          }
          break;
        }
      }
      return lastAnswer;
    }
  }

  static abstract class Treap {
    static final int MAX_RANDOM = Integer.MAX_VALUE >> 1;
    final Random random = new Random(2);

    Node root;

    static class Answer {
      Node node;
      VisitAnswer answer;
    }

    void rotateLeft(Node node) {
      Node previousParent = node.lastParent;
      Node p = node.left;
      if (previousParent != null) {
        previousParent.set(previousParent.left == node, p);
      } else {
        p.lastParent = null;
        root = p;
      }
      node.left = p.right;
      p.right = node;
      node.lastParent = p;
    }

    void rotateRight(Node node) {
      Node previousParent = node.lastParent;
      Node p = node.right;
      if (previousParent != null) {
        previousParent.set(previousParent.left == node, p);
      } else {
        p.lastParent = null;
        root = p;
      }
      node.right = p.left;
      p.left = node;
      node.lastParent = p;
    }

    boolean fixPriorityDown(Node node) {
      int highestPriority = node.left == null ? node.priority : node.left.priority;
      boolean isLeft = true;
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
        node.left.beforeVisit();
        rotateLeft(node);
      } else {
        node.right.beforeVisit();
        rotateRight(node);
      }
      return true;
    }

    void fixPriority(Node node) {
      while (true) {
        if (node.lastParent != null && node.priority > node.lastParent.priority) {
          Node toChange = node.lastParent;
          if (node.lastParent.left == node) {
            rotateLeft(toChange);
          } else {
            rotateRight(toChange);
          }
          toChange.afterChange();
        } else {
          if (!fixPriorityDown(node)) {
            return;
          }
        }
      }
    }

    void propagateChange(Node node) {
      while (node != null) {
        node.afterChange();
        node = node.lastParent;
      }
    }

    void add(Node node, NodeVisitor visitor) {
      node.priority = random.nextInt(MAX_RANDOM);
      if (root == null) {
        root = node;
        root.lastParent = null;
        return;
      }
      VisitAnswer visitAnswer = visitor.visit(root);
      node.lastParent = visitor.lastNode;
      node.lastParent.set(visitAnswer == VisitAnswer.LEFT, node);
      fixPriority(node);
      propagateChange(node);
    }

    void remove(NodeVisitor visitor) {
      VisitAnswer visitAnswer = visitor.visit(root);
      Node toDelete = visitor.lastNode;
      toDelete.priority = -1;
      fixPriority(toDelete);
      if (toDelete.lastParent != null) {
        toDelete.lastParent.set(toDelete.lastParent.left == toDelete, null);
        propagateChange(toDelete.lastParent);
      } else {
        root = null;
      }
    }

    int makeRoot(Node node) {
      int previousPriority = node.priority;
      node.priority = MAX_RANDOM;
      fixPriority(node);
      return previousPriority;
    }

    int makeRoot(NodeVisitor visitor) {
      visitor.visit(root);
      return makeRoot(visitor.lastNode);
    }

    Node splitBeforeRoot(NodeVisitor visitor) {
      int previousPriority = makeRoot(visitor);
      Node toReturn = root.left;
      root.left = null;
      root.priority = previousPriority;
      Node node = root;
      fixPriority(node);
      propagateChange(node);
      return toReturn;
    }

    Node splitAfterRoot(NodeVisitor visitor) {
      int previousPriority = makeRoot(visitor);
      Node toReturn = root.right;
      root.right = null;
      root.priority = previousPriority;
      Node node = root;
      fixPriority(node);
      propagateChange(node);
      return toReturn;
    }

    Node visitFirst() {
      Node current = root;
      Node last = null;
      while (true) {
        current.lastParent = last;
        last = current;
        current.beforeVisit();
        if (current.left == null) {
          return current;
        }
        current = current.left;
      }
    }

    Node visitLast() {
      Node current = root;
      Node last = null;
      while (true) {
        current.lastParent = last;
        last = current;
        current.beforeVisit();
        if (current.right == null) {
          return current;
        }
        current = current.right;
      }
    }

    void mergeLeft(Node leftRoot) {
      int previousPriority = makeRoot(visitFirst());
      root.left = leftRoot;
      root.priority = previousPriority;
      Node node = root;
      fixPriority(node);
      propagateChange(node);
    }

    void mergeRight(Node rightRoot) {
      int previousPriority = makeRoot(visitLast());
      root.right = rightRoot;
      root.priority = previousPriority;
      Node node = root;
      fixPriority(node);
      propagateChange(node);
    }
  }

  static class ImplicitNodeVisitor extends BeforeNodeVisitor {

    int remaining;

    ImplicitNodeVisitor(int searched) {
      this.remaining = searched + 1;
    }

    @Override
    void before(Node node) {
      remaining--;
    }

    @Override
    void allBefore(Node node) {
      remaining -= node.getCount();
    }

    @Override
    VisitAnswer visitNode(Node node) {
      if (node.left != null) {
        node.left.beforeVisit();
        if (remaining <= node.left.getCount()) {
          return VisitAnswer.LEFT;
        } else if (remaining == (node.left.getCount() + 1)) {
          return VisitAnswer.CURRENT;
        } else {
          return VisitAnswer.RIGHT;
        }
      } else {
        if (remaining == 1) {
          return VisitAnswer.CURRENT;
        } else {
          return VisitAnswer.RIGHT;
        }
      }
    }
  }

  static class ColorCounterNodeVisitor extends ComplexNodeVisitor {

    int remaining;
    int whiteCount = 0;
    int blackCount = 0;

    ColorCounterNodeVisitor(int searched) {
      this.remaining = searched + 1;
    }

    @Override
    void before(Node node) {
      remaining--;
    }

    @Override
    void allBefore(Node node) {
      remaining -= node.getCount();
    }

    @Override
    void after(Node node) {
      whiteCount += node.currentColor() ? 1 : 0;
      blackCount += node.currentColor() ? 0 : 1;
    }

    @Override
    void allAfter(Node node) {
      whiteCount += node.whiteCount();
      blackCount += node.blackCount();
    }

    @Override
    VisitAnswer visitNode(Node node) {
      if (node.left != null) {
        node.left.beforeVisit();
        if (remaining <= node.left.getCount()) {
          return VisitAnswer.LEFT;
        } else if (remaining == (node.left.getCount() + 1)) {
          return VisitAnswer.CURRENT;
        } else {
          return VisitAnswer.RIGHT;
        }
      } else {
        if (remaining == 1) {
          return VisitAnswer.CURRENT;
        } else {
          return VisitAnswer.RIGHT;
        }
      }
    }
  }

  static class LastVisitor extends NodeVisitor {

    @Override
    VisitAnswer visitNode(Node node) {
      return VisitAnswer.RIGHT;
    }
  }

  static class StonesTreap extends Treap {
    final int size;

    StonesTreap(int size) {
      this.size = size;
      LastVisitor lastVisitor = new LastVisitor();
      for (int i = 0; i < this.size; i++) {
        add(new Node(), lastVisitor);
      }
    }

    void reverse(int from, int to) {
      if (from == 0 && to == size - 1) {
        root.reversePending = !root.reversePending;
        return;
      }
      Node previous = from == 0 ? null : splitBeforeRoot(new ImplicitNodeVisitor(from));
      Node after = to == size - 1 ? null : splitAfterRoot(new ImplicitNodeVisitor(to - from));
      root.reversePending = !root.reversePending;
      root.beforeVisit();
      if (previous != null) {
        mergeLeft(previous);
      }
      if (after != null) {
        mergeRight(after);
      }
    }

    void reverseColor(int from, int to) {
      if (from == 0 && to == size - 1) {
        root.flipReverseColorPending();
        return;
      }
      Node previous = from == 0 ? null : splitBeforeRoot(new ImplicitNodeVisitor(from));
      Node after = to == size - 1 ? null : splitAfterRoot(new ImplicitNodeVisitor(to - from));
      root.flipReverseColorPending();
      root.beforeVisit();
      if (previous != null) {
        mergeLeft(previous);
      }
      if (after != null) {
        mergeRight(after);
      }
    }

    void setColor(int from, int to, boolean white) {
      if (from == 0 && to == size - 1) {
        root.setSetPending(white);
        return;
      }
      Node previous = from == 0 ? null : splitBeforeRoot(new ImplicitNodeVisitor(from));
      Node after = to == size - 1 ? null : splitAfterRoot(new ImplicitNodeVisitor(to - from));
      root.setSetPending(white);
      root.beforeVisit();
      if (previous != null) {
        mergeLeft(previous);
      }
      if (after != null) {
        mergeRight(after);
      }
    }

    int[] getCounts(int from, int to) {
      if (from == 0) {
        int[] currentCounts = new int[]{root.blackCount(), root.whiteCount()};
        ColorCounterNodeVisitor visitor = new ColorCounterNodeVisitor(to);
        visitor.visit(root);
        currentCounts[0] -= visitor.blackCount;
        currentCounts[1] -= visitor.whiteCount;
        return currentCounts;
      } else {
        ColorCounterNodeVisitor visitor = new ColorCounterNodeVisitor(from - 1);
        visitor.visit(root);
        int[] currentCounts = new int[]{visitor.blackCount, visitor.whiteCount};
        visitor = new ColorCounterNodeVisitor(to);
        visitor.visit(root);
        currentCounts[0] -= visitor.blackCount;
        currentCounts[1] -= visitor.whiteCount;
        return currentCounts;
      }
    }
  }

  public static void main() {
    while (true) {
      int n = sc.nextIntOrQuit();
      StonesTreap treap = new StonesTreap(n);
      int q = sc.nextInt();
      for (int i = 0; i < q; i++) {
        int type = sc.nextInt();
        if (type == 0) {
          sw.printLine(treap.getCounts(sc.nextInt(), sc.nextInt()));
        } else if (type == 1) {
          treap.reverse(sc.nextInt(), sc.nextInt());
        } else if (type == 2) {
          treap.reverseColor(sc.nextInt(), sc.nextInt());
        } else {
          treap.setColor(sc.nextInt(), sc.nextInt(), sc.nextInt() == 1);
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
