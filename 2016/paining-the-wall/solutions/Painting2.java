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
import java.util.HashMap;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.StringTokenizer;

public class Painting2 {
  private static final boolean SHOULD_BUFFER_OUTPUT = false;

  static final SuperWriter sw = new SuperWriter(System.out);

  static final SuperScanner sc = new SuperScanner();

  static class BipartiteMatchingSparse {
    final ArrayList<Integer>[] w;
    final int[] mr;
    final int[] mc;
    final boolean[] seen;

    @SuppressWarnings("unchecked")
    BipartiteMatchingSparse(int n) {
      w = new ArrayList[n];
      for (int i = 0; i < n; i++) {
        w[i] = new ArrayList<Integer>();
      }
      mr = new int[n];
      mc = new int[n];
      seen = new boolean[n];
    }

    boolean findMatch(int i) {
      for (int j : w[i]) {
        if (!seen[j]) {
          seen[j] = true;
          if (mc[j] < 0 || findMatch(mc[j])) {
            mr[i] = j;
            mc[j] = i;
            return true;
          }
        }
      }
      return false;
    }

    int bipartiteMatching() {
      Arrays.fill(mr, -1);
      Arrays.fill(mc, -1);
      int ct = 0;
      for (int i = 0; i < w.length; i++) {
        Arrays.fill(seen, false);
        if (findMatch(i)) ct++;
      }
      return ct;
    }
  }

  static int currentId;
  static ArrayList<Node> nodes = new ArrayList<Node>();
  static ArrayList<Node> horizontalNodes = new ArrayList<Node>();
  static ArrayList<Node> verticalNodes = new ArrayList<Node>();

  static class Node {
    int id;
    Integer matching = null;
    HashSet<Integer> adjacent = new HashSet<Integer>();
    HashMap<Integer, Integer> visited = new HashMap<Integer, Integer>();
    String line;
    int start, end;
    boolean isInZ = false;

    Node() {
      id = currentId++;
      nodes.add(this);
    }

    public void visitZ(Node last, boolean visitMatching) {
      if (last != null) {
        if (!visited.containsKey(last.id)) {
          visited.put(last.id, 0);
        }
        int visitedBit = 1 << (visitMatching ? 1 : 0);
        if ((visited.get(last.id) & visitedBit) != 0) {
          return;
        }
        visited.put(last.id, visited.get(last.id) | visitedBit);
      }
      isInZ = true;
      if (visitMatching) {
        if ((matching != null) && (matching != last.id)) {
          nodes.get(matching).visitZ(this, !visitMatching);
        }
      } else {
        for (int node : adjacent) {
          Node current = nodes.get(node);
          if (current != last) {
            current.visitZ(this, !visitMatching);
          }
        }
      }
    }
  }

  static Node[][] getNodes(boolean[][] painting, boolean horizontal) {
    Node[][] nodes = new Node[painting.length][painting[0].length];
    if (horizontal) {
      for (int i = 0; i < painting.length; i++) {
        Node currentNode = null;
        for (int j = 0; j < painting[i].length; j++) {
          if (painting[i][j]) {
            if (currentNode == null) {
              currentNode = new Node();
              horizontalNodes.add(currentNode);
              currentNode.start = j;
            }
            nodes[i][j] = currentNode;
            currentNode.end = j;
          } else {
            currentNode = null;
          }
        }
      }
      for (int i = 0; i < painting.length; i++) {
        for (int j = 0; j < painting[i].length; j++) {
          if (nodes[i][j] != null && nodes[i][j].line == null) {
            nodes[i][j].line = "hline " + (i + 1) + " " + (nodes[i][j].start + 1) + " " + (nodes[i][j].end + 1);
          }
        }
      }
    } else {
      for (int i = 0; i < painting[0].length; i++) {
        Node currentNode = null;
        for (int j = 0; j < painting.length; j++) {
          if (painting[j][i]) {
            if (currentNode == null) {
              currentNode = new Node();
              verticalNodes.add(currentNode);
              currentNode.start = j;
            }
            nodes[j][i] = currentNode;
            currentNode.end = j;
          } else {
            currentNode = null;
          }
        }
      }
      for (int i = 0; i < painting[0].length; i++) {
        for (int j = 0; j < painting.length; j++) {
          if (nodes[j][i] != null && nodes[j][i].line == null) {
            nodes[j][i].line = "vline " + (i + 1) + " " + (nodes[j][i].start + 1) + " " + (nodes[j][i].end + 1);
          }
        }
      }
    }
    return nodes;
  }

  public static void main() {
    while (true) {
      int r = sc.nextIntOrQuit();
      int c = sc.nextInt();
      boolean[][] painting = new boolean[r][c];
      for (int i = 0; i < r; i++) {
        char[] row = sc.next().toCharArray();
        for (int j = 0; j < c; j++) {
          painting[i][j] = row[j] == '*';
        }
      }
      currentId = 0;
      nodes.clear();
      horizontalNodes.clear();
      verticalNodes.clear();
      Node[][] horizontal = getNodes(painting, true);
      Node[][] vertical = getNodes(painting, false);
      BipartiteMatchingSparse sparse = new BipartiteMatchingSparse(currentId);
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
          if (horizontal[i][j] != null && vertical[i][j] != null) {
            sparse.w[horizontal[i][j].id].add(vertical[i][j].id);
            horizontal[i][j].adjacent.add(vertical[i][j].id);
            vertical[i][j].adjacent.add(horizontal[i][j].id);
          }
        }
      }
      int answer = sparse.bipartiteMatching();
      for (int i = 0; i < sparse.mr.length; i++) {
        if (sparse.mr[i] != -1) {
          nodes.get(i).matching = sparse.mr[i];
        }
      }
      for (int i = 0; i < sparse.mc.length; i++) {
        if (sparse.mc[i] != -1) {
          nodes.get(i).matching = sparse.mc[i];
        }
      }
      for (Node node : horizontalNodes) {
        if (node.matching == null) {
          node.visitZ(null, false);
        }
      }
      sw.printLine(answer);
      for (Node node : verticalNodes) {
        if (node.isInZ) {
          sw.printLine(node.line);
        }
      }
      for (Node node : horizontalNodes) {
        if (!node.isInZ) {
          sw.printLine(node.line);
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

