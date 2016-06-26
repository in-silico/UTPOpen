import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
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

public class adventurerd2 {
  private static final boolean IN_DEBUG = false;

  static final SuperWriter sw = new SuperWriter(System.out);

  static final Scanner sc = new SuperScanner();

  static final int inf = 0x3f3f3f3f;

  static class edge
  {
    int a,b,c;
    edge(){}
    edge(int aa,int bb,int cc){
      a = aa;
      b = bb;
      c = cc;
    }
  }

  public static void main() {
    outer:
    while (sc.testCases()) {
      int n,m,i,j,k,ans,u,v,tn,rt,sum,on,om,ttt;
      n = sc.nextInt();
      m = sc.nextInt();
      rt = sc.nextInt();
      int[] pre = new int[n];
      int[] id = new int[n];
      int[] in = new int[n];
      int[] vis = new int[n];
      ArrayList<edge> ed = new ArrayList<>();
      ArrayList<edge> edans = new ArrayList<>();
      on=n;
      om=m;
      ed.clear();
      edans.clear();
      sum=1;
      while(m-- != 0)
      {
        i = sc.nextInt();
        j = sc.nextInt();
        k = sc.nextInt();
        if(i!=j)
        {
          ed.add(new edge(i,j,k));
          sum+=k;
        }
      }
      ans=0;
      while(true)
      {
        Arrays.fill(in, inf);
        for(i=0;i<ed.size();++i)
          if(ed.get(i).a!=ed.get(i).b && in[ed.get(i).b]>ed.get(i).c)
          {
            in[ed.get(i).b]=ed.get(i).c;
            pre[ed.get(i).b]=ed.get(i).a;
            if(ed.get(i).a==rt)
              j=i;
          }
        for(i=0;i<n;++i)
          if(i!=rt && in[i]==inf) {
            sw.printLine("impossible");
            continue outer;
          }
        Arrays.fill(id, -1);
        Arrays.fill(vis, -1);
        tn=in[rt]=0;
        for(i=0;i<n;++i)
        {
          ans+=in[i];
          if (i !=rt && in[i] > 0) {
            edans.add(new edge(pre[i], i, in[i]));
          }
          for(v=i;vis[v]!=i && id[v]==-1 && v!=rt;v=pre[v]) {
            vis[v]=i;
          }
          if(v!=rt && id[v]==-1)
          {
            for(u=pre[v];u!=v;u=pre[u])
              id[u]=tn;
            id[v]=tn++;

          }
        }
        if(tn == 0)
          break;
        for(i=0;i<n;++i)
          if(id[i]==-1)
            id[i]=tn++;
        for(i=0;i<ed.size();++i)
        {
          v=ed.get(i).b;
          ed.get(i).a=id[ed.get(i).a];
          ed.get(i).b=id[ed.get(i).b];
          if(ed.get(i).a!=ed.get(i).b)
            ed.get(i).c-=in[v];
        }
        n=tn;
        rt=id[rt];
      }
      if(ans>=2*sum)
        sw.printLine("impossible");
      else {
        sw.printLine(ans);
        for (int qq = 0; qq < edans.size(); qq++) {
          sw.printLine(edans.get(qq).a,edans.get(qq).b,edans.get(qq).c);
        }
      }
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
        throw new InputMismatchException();
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
    public int nextInt() {
      int c = read();
      while (isWhitespace(c))
        c = read();
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

  static class Scanner {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer("");

    public String nextLine() {
      try {
        return br.readLine();
      } catch (Exception e) {
        throw (new RuntimeException());
      }
    }

    public int nextIntOrQuit() {
      Integer n = nextInteger();
      if (n == null) {
        sw.close();
        System.exit(0);
      }
      return n.intValue();
    }

    public String next() {
      while (!st.hasMoreTokens()) {
        String l = nextLine();
        if (l == null)
          return null;
        st = new StringTokenizer(l);
      }
      return st.nextToken();
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
      if (IN_DEBUG) {
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
      if (IN_DEBUG) {
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
      if (IN_DEBUG) {
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
      if (IN_DEBUG) {
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
      if (IN_DEBUG) {
        writer.flush();
      }
    }

    public <E> void printLine(Collection<E> vals) {
      if (vals.size() == 0) {
        writer.println();
      } else {
        int i = 0;
        for (E val : vals) {
          if (i++ == 0) {
            writer.print(val.toString());
          } else {
            writer.print(" ".concat(val.toString()));
          }
        }
        writer.println();
      }
      if (IN_DEBUG) {
        writer.flush();
      }
    }

    public void print(String value) {
      writer.print(value);
      if (IN_DEBUG) {
        writer.flush();
      }
    }

    public void zeroCheck(Number... values) {
      for (Number number : values) {
        if (number.doubleValue() != 0.0d || number.longValue() != 0) {
          return;
        }
      }
      close();
      System.exit(0);
    }
  }


  public static void main(String[] args) {
    main();
    sw.close();
  }
}
