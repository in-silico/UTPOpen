// Santiago Gutierrez.
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
import java.util.StringTokenizer;

public class TobbyTree {
  private static final boolean SHOULD_BUFFER_OUTPUT = false;

  static final SuperWriter sw = new SuperWriter(System.out);

  static final SuperScanner sc = new SuperScanner();

  static int gcd(int u, int v) {
    while(u != 0){v %= u; int tmp = u; u = v; v = tmp;} return v;
  }

  static class SegmentTree {
    int[] M;

    public SegmentTree(int size) {
      M = new int[size * 4 + 4];
    }

    void init(int node, int b, int e, int[] startValues) {
      if (b == e) {
        M[node] = startValues[b];
        return;
      }
      int node2 = node << 1;
      int be2 = (b + e) >> 1;
      init(node2, b, be2, startValues);
      init(node2 + 1, be2 + 1, e, startValues);
      M[node] = gcd(M[node2], M[node2 + 1]);
    }

    void update(int node, int b, int e, int pos, int value) {
      if (pos > e || pos < b) {
        return;
      }
      if (b == e) {
        M[node] = value;
        return;
      }
      int node2 = node << 1;
      int be2 = (b + e) >> 1;
      update(node2, b, be2, pos, value);
      update(node2 + 1, be2 + 1, e, pos, value);
      M[node] = gcd(M[node2], M[node2 + 1]);
    }

    int query(int node, int b, int e, int i, int j) {
      if (i > e || j < b) {
        return 0;
      }
      if (b >= i && e <= j) {
        return M[node];
      }
      int node2 = node << 1;
      int be2 = (b + e) >> 1;
      int p1 = query(node2, b, be2, i, j);
      int p2 = query(node2 + 1, be2 + 1, e, i, j);
      return gcd(p1, p2);
    }
  }

  static class Path {
    Path parentPath;
    Node parentNode;
    ArrayList<Node> nodesInOrder = new ArrayList<Node>();
    int rootHeight;

    ///

    SegmentTree segment;
    int allGcd = 0;

    void initSegment() {
      if (segment != null) {
        return;
      }
      int[] initValue = new int[nodesInOrder.size()];
      for (int i = 0; i < initValue.length; i++) {
        initValue[i] = nodesInOrder.get(i).value;
      }
      segment = new SegmentTree(initValue.length);
      segment.init(1, 0, initValue.length - 1, initValue);
      allGcd = segment.query(1, 0, initValue.length - 1, 0, initValue.length - 1);
    }

    void update(Node node) {
      segment.update(1, 0, nodesInOrder.size() - 1, node.idInPath, node.value);
      allGcd = segment.query(1, 0, nodesInOrder.size() - 1, 0, nodesInOrder.size() - 1);
    }

    int query(int i, int j) {
      return segment.query(1, 0, nodesInOrder.size() - 1, i, j);
    }
  }

  static class Node {
    final ArrayList<Node> edges = new ArrayList<Node>();
    final int id;

    int height;
    int size;
    Node heavyNode;
    Node parent;
    Path path;
    int idInPath;

    Node(int id) {
      this.id = id;
    }

    void visit(Node parent, int height) {
      this.parent = parent;
      this.height = height;
      this.size = 1;
      int heavySize = 0;
      for (Node node : edges) {
        if (node != parent) {
          node.visit(this, this.height + 1);
          if (node.size > heavySize) {
            heavyNode = node;
            heavySize = node.size;
          }
          this.size += node.size;
        }
      }
    }

    public String toString() {
      return id + " - " + value;
    }

    void getPaths(Path[] paths, Path parentPath, Path currentPath) {
      if (currentPath == null) {
        currentPath = new Path();
        currentPath.parentPath = parentPath;
        currentPath.parentNode = parent;
        currentPath.rootHeight = height;
      }
      path = currentPath;
      idInPath = currentPath.nodesInOrder.size();
      currentPath.nodesInOrder.add(this);
      paths[id] = currentPath;
      if (heavyNode != null) {
        heavyNode.getPaths(paths, parentPath, currentPath);
      }
      for (Node node : edges) {
        if ((node != heavyNode) && (node != parent)) {
          node.getPaths(paths, currentPath, null);
        }
      }
    }

    ///

    int value;
  }

  static int getGcd(Node a, Node b) {
    Path pathA = a.path;
    Path pathB = b.path;
    Node lastParentA = a;
    Node lastParentB = b;
    int gcd = 0;
    while (pathA != pathB) {
      if (pathB.rootHeight <= pathA.rootHeight) {
        gcd = gcd(gcd, pathA.query(0, lastParentA.idInPath));
        lastParentA = pathA.parentNode;
        pathA = pathA.parentPath;
      } else {
        gcd = gcd(gcd, pathB.query(0, lastParentB.idInPath));
        lastParentB = pathB.parentNode;
        pathB = pathB.parentPath;
      }
    }
    int idA = lastParentA.idInPath;
    int idB = lastParentB.idInPath;
    if (idA > idB) {
      int tmp = idA;
      idA = idB;
      idB = tmp;
    }
    gcd = gcd(gcd, pathA.query(idA, idB));
    return gcd;
  }

  public static void main() {
    while (true) {
      int n = sc.nextIntOrQuit();
      Node[] nodes = new Node[n];
      for (int i = 0; i < n; i++) {
        nodes[i] = new Node(i);
        nodes[i].value = sc.nextInt();
      }
      for (int i = 0; i < n - 1; i++) {
        int u = sc.nextInt();
        int v = sc.nextInt();
        nodes[u].edges.add(nodes[v]);
        nodes[v].edges.add(nodes[u]);
      }
      nodes[0].visit(null, 0);
      Path[] paths = new Path[n];
      nodes[0].getPaths(paths, null, null);
      for (Path path : paths) {
        path.initSegment();
      }
      int q = sc.nextInt();
      for (int i = 0; i < q; i++) {
        int type = sc.nextInt();
        if (type == 1) {
          int u = sc.nextInt();
          int v = sc.nextInt();
          sw.printLine(getGcd(nodes[u], nodes[v]));
        } else {
          int u = sc.nextInt();
          int x = sc.nextInt();
          nodes[u].value = x;
          nodes[u].path.update(nodes[u]);
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

