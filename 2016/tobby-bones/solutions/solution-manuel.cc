#include <bits/stdc++.h>

#define D(x) cout << #x " = " << (x) << endl
#define null NULL
#define endl '\n'

using namespace std;

struct node{
  int x, y, size, frec;
  node *l, *r, *p;
  node(int _x) : x(_x), y(rand()), size(1), frec(1) {
    l = r = p = null;
  }
};

typedef node* pnode;

struct treap{
  pnode root;
  treap () : root(null) {}

  pnode find(pnode cur, int x) {
    while (cur != null and cur-> x != x) {
      if (x < cur-> x) cur = cur-> l;
      else             cur = cur-> r;
    }
    return cur;
  }

  pnode relax(pnode p) {
    if (p) {
      p-> size = p-> frec;
      if (p-> l)
        p-> size += p-> l-> size;
      if (p-> r)
        p-> size += p-> r-> size;
    }
    return p;
  }

  void split(pnode t, int x, pnode &l, pnode &r) {
    if (t == null)
      l = r = null;
    else {
      if (t-> x <= x) {
        split(t-> r, x, t-> r, r);
        l = relax(t);
      } else {
        split(t-> l, x, l, t-> l);
        r = relax(t);
      }
    }
  }

  pnode merge(pnode l, pnode r) {
    if (l == null) return relax(r);
    if (r == null) return relax(l);
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      return relax(l);
    } else {
      r->l = merge(l, r->l);
      return relax(r);
    }
  }

  pnode insert(pnode t, pnode m) {
    if (t == null || m->y > t->y) {
      split(t, m->x, m->l, m->r);
      return relax(m);
    }
    if (m->x < t->x) t->l = insert(t->l, m);
    else t->r = insert(t->r, m);
    return relax(t);
  }

  pnode erase(pnode t, int x) {
    if (t == null) return null;
    if (t->x == x) {
      pnode q = merge(t->l, t->r);
      delete t;
      return relax(q);
    } else {
      if (x < t->x) t->l = erase(t->l, x);
      else t->r = erase(t->r, x);
      return relax(t);
    }
  }

  void add(int x) {
    pnode cur = find(root, x);
    if (cur == null)
      root = insert(root, new node(x));
    else {
      cur-> frec++;
      cur = relax(cur);
      pnode t = root;
      while (t != cur) {
        t-> size++;
        if (x > t-> x) t = t-> r;
        else t = t-> l;
      }
    }
  }

  void del(int x) {
    pnode cur = find(root, x);
    assert(cur);
    if (cur-> frec == 1)
      root = erase(root, x);
    else {
      cur-> frec--;
      cur = relax(cur);
      pnode t = root;
      while (t != cur) {
        t-> size--;
        if (x > t-> x) t = t-> r;
        else t = t-> l;
      }
    }
  }

  int get_size(pnode t) {
    return t ? t-> size : 0;
  }

  int left_count(pnode p, int x) {
    if (p == null) return 0;
    if (p-> x > x) return left_count(p-> l, x);
    int ans = get_size(p-> l) + p-> frec + left_count(p-> r, x);
    return ans;
  }

  int left_count(int val) {
    return left_count(root, val);
  }

  void traverse(pnode p) {
    if (p == null) return;
    traverse(p-> l);
    cout << p-> x << " : " << p-> frec << endl;
    traverse(p-> r);
  }
};

struct seg_tree{
  vector<treap> tree;

  seg_tree() {}
  seg_tree(int N) {
    tree.resize(4 * N + 10);
    init(1, 0, N - 1);
  }

  void init(int node, int b, int e) {
    tree[node] = treap();
    if (b == e) return;
    int mid = (b + e) >> 1;
    init(node << 1, b, mid);
    init(node << 1 | 1, mid + 1, e);
  }

  void add(int node, int b, int e, int pos, int val) {
    tree[node].add(val);
    if (b == e) {
      assert(b == pos);
      return;
    }
    int mid = (b + e) >> 1;
    if (mid >= pos) add(node << 1, b, mid, pos, val);
    else            add(node << 1 | 1, mid + 1, e, pos, val);
  }

  void del(int node, int b, int e, int pos, int val) {
    tree[node].del(val);
    if (b == e) {
      assert(b == pos);
      return;
    }
    int mid = (b + e) >> 1;
    if (mid >= pos) del(node << 1, b, mid, pos, val);
    else            del(node << 1 | 1, mid + 1, e, pos, val);
  }

  int query(int node, int b, int e, int l, int r, int s) {
    if (b >= l && e <= r) {
      return tree[node].left_count(s);
    }
    if (b > r || e < l)
      return 0;
    int mid = (b + e) >> 1;
    return query(node << 1, b, mid, l, r, s) +
      query(node << 1 | 1, mid + 1, e, l, r, s);
  }
};


int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  srand(time(0));

  int n, m;
  while (cin >> n >> m) {
    seg_tree tree(n);
    vector<int> bones(n);
    while (m--) {
      int q;
      cin >> q;
      if (q == 0) {
        int id, b;
        cin >> id >> b;
        if (bones[id])
          tree.del(1, 0, n - 1, id, bones[id]);
        bones[id] = b;
        tree.add(1, 0, n - 1, id, bones[id]);
      } else if (q == 1) {
        int i, j, s;
        cin >> i >> j >> s;
        cout << tree.query(1, 0, n - 1, i, j, s) << endl;
      } else {
        assert(false);
      }
    }
  }

  return 0;
}
