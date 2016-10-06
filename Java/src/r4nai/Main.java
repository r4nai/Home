package r4nai;

import java.io.*;
import java.math.BigInteger;
import java.util.Arrays;

import static java.lang.Integer.parseInt;

public class Main {
    private static final boolean ONLINE_JUDGE = false;
//    private static final boolean ONLINE_JUDGE = true;
    public static BufferedReader inp;
    public static PrintWriter out;

    public static int[] a;
    public static int[] b;

    public static int[] lefts,
                        rights,
                        counts,
                        xs;
    public static boolean[] sets;
    public static int[][] bs;

    public static int aa, bb, cc, mm;

    public static int rnd(int last) {
        aa = (36969 + (last >> 3)) * (aa & mm) + (aa >> 16);
        bb = (18000 + (last >> 3)) * (bb & mm) + (bb >> 16);
        return (cc & ((aa << 16) + bb)) % 1000000000;
    }

    public static int find(int[] a, int l, int r, int x) {
        int left = l, right = r;
        while (left != right) {
            int m = left + (right - left) / 2 + (right - left) % 2;
            if (x < a[m]) {
                right = m - 1;
            }
            else {
                left = m;
            }
        }
        if (x >= a[left]) {
            return left;
        }
        else {
            return left - 1;
        }
    }

    public static void set_x(int node, int l, int r, int x) {
        if (lefts[node] == l && rights[node] == r) {
            xs[node] = x;
            sets[node] = true;
            int i = find(bs[node], 0, r - l, x);
            counts[node] = i + 1;
            return;
        }
        int m = lefts[node] + (rights[node] - lefts[node]) / 2;
        int left_i = node * 2 + 1,
            right_i = node * 2 + 2;
        if (sets[node]) {
            if (lefts[node] < rights[node]) {
                set_x(left_i, lefts[left_i], rights[left_i], xs[node]);
                set_x(right_i, lefts[right_i], rights[right_i], xs[node]);
            }
            sets[node] = false;
        }

        if (r <= m) {
            set_x(left_i, l, r, x);
            counts[node] = counts[left_i] + counts[right_i];
        }
        else if (l > m) {
            set_x(right_i, l, r, x);
            counts[node] = counts[left_i] + counts[right_i];
        }
        else {
            set_x(left_i, l, m, x);
            set_x(right_i, m + 1, r, x);
            counts[node] = counts[left_i] + counts[right_i];
        }
    }

    public static int get_count(int node, int l, int r) {
        if (lefts[node] == l && rights[node] == r) {
            return counts[node];
        }
        if (sets[node]) {
            int i = find(bs[node], l - lefts[node], r - lefts[node], xs[node]) - l;
            return i + 1;
        }

        int m = lefts[node] + (rights[node] - lefts[node]) / 2;
        if (r <= m) {
            return get_count(node * 2 + 1, l, r);
        }
        else if (l > m) {
            return get_count(node * 2 + 2, l, r);
        }
        else {
            int ml = get_count(node * 2 + 1, l, m);
            int mr = get_count(node * 2 + 2, m + 1, r);
            return ml + mr;
        }
    }

    public static void build(int cur) {
        int l = lefts[cur], r = rights[cur];
        if (l == r) {
            counts[cur] = (a[l] >= b[l] ? 1 : 0);
            return;
        }
        int m = l + (r - l) / 2;
        int left_i = cur * 2 + 1;
        lefts[left_i] = l; rights[left_i] = m;
        sets[left_i] = false;
        bs[left_i] = new int[m - l + 1];
        for (int i = l; i <= m; ++i) {
            bs[left_i][i - l] = b[i];
        }
        Arrays.sort(bs[left_i]);

        int right_i = cur * 2 + 2;
        lefts[right_i] = m + 1; rights[right_i] = r;
        sets[right_i] = false;
        bs[right_i] = new int[r - m - 1 + 1];
        for (int i = m + 1; i <= r; ++i) {
            bs[right_i][i - m - 1] = b[i];
        }
        Arrays.sort(bs[right_i]);

        build(left_i);
        build(right_i);
        counts[cur] = counts[left_i] + counts[right_i];
    }

    public static void solve() throws IOException {
        int n, m;
        String tokens[] = inp.readLine().split(" ");
        n = parseInt(tokens[0]); m = parseInt(tokens[1]);
        aa = parseInt(tokens[2]); bb = parseInt(tokens[3]);
        cc = (int)~((int)1 << (int)31); mm = (1 << 16) - 1;

        tokens = inp.readLine().split(" ");
        a = new int[n]; b = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = parseInt(tokens[i]);
        }
        tokens = inp.readLine().split(" ");
        for (int i = 0; i < n; ++i) {
            b[i] = parseInt(tokens[i]);
        }

        lefts = new int[4 * n];
        rights = new int[4 * n];
        counts = new int[4 * n];
        xs = new int[4 * n];
        sets = new boolean[4 * n];
        bs = new int[4 * n][];

        lefts[0] = 0;
        rights[0] = n - 1;
        bs[0] = new int[n];
        for (int i = 0; i < n; ++i) {
            bs[0][i] = b[i];
        }
        Arrays.sort(bs[0]);
        build(0);

        BigInteger ret = BigInteger.ZERO;
        BigInteger modulo = BigInteger.valueOf(100000007);
        int last = 0;
        int root = 0;
        for (int i = 1; i <= m; ++i) {
            int l, r, x;
            l = rnd(last) % n + 1;
            r = rnd(last) % n + 1;
            x = rnd(last) + 1;
            if (l > r) {
                int t = l;
                l = r;
                r = t;
            }
            int res = 0;
            if ((l + r + x) % 2 == 0) {
                res = get_count(root, l - 1, r - 1);
                last = res;
                out.printf("? %d %d -> %d\n", l, r, res);
            }
            else {
                set_x(root, l - 1, r - 1, x);
                out.printf("+ %d %d %d\n", l, r, x);
            }
            BigInteger tmp = BigInteger.valueOf(i);
            ret = ret.add(tmp.multiply(BigInteger.valueOf(res)));//.mod(modulo);
//            ret = (ret + i * res) % (1000000007);
        }
        out.println(ret);
//        set_x(root, 0, 2, 10);
//        set_x(root, 0, 1, 12);
    }

    public static void main(String[] args) throws IOException {
        if (ONLINE_JUDGE) {
            inp = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
//            inp = new BufferedReader(new FileReader("vier.in"));
//            out = new PrintWriter(new File("vier.out"));
        }
        else {
            inp = new BufferedReader(new FileReader("input.txt"));
            out = new PrintWriter("output.txt");
        }
        int t = parseInt(inp.readLine());
        for (int i = 0; i < t; ++i) {
            solve();
        }
        out.close();
    }
}

