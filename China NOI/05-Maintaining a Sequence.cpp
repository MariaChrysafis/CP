#include <bits/stdc++.h>
using namespace std;
struct Node {
    bool rev;
    int val;
    int sum;
    int sz;
    int y;
    bool val1;
    int max_left;
    int max_right;
    int best;
    Node* left;
    Node* right;
    Node (int val) {
        this->val = val;
        sum = val, rev = false;
        left = nullptr, right = nullptr;
        this->y = rand(), sz = 1, val1 = false;
        max_left = max_right = best = val;
    }
    ~Node() {
        if (left) delete left;
        if (right) delete right;
    }
};

struct ImplicitTreap {
    Node*root;
    inline void chng (Node*& x) {
        x->sum = x->sz * x->val;
        x->best = x->max_left = x->max_right = max(x->val, x->sum);
    }
    inline void push (Node*& x) {
        if (x == nullptr) return;
        if (x->rev) {
            swap(x->left, x->right);
            swap(x->max_left, x->max_right);
            if (x->left) {
                x->left->rev ^= 1;
            }
            if (x->right) {
                x->right->rev ^= 1;
            }
            x->rev = false;
        }
        x->sz = (x->left ? x->left->sz : 0) + 1 + (x->right ? x->right->sz : 0);
        if (x->val1) {
            chng(x);
            if (x->left) {
                x->left->val1 = true, x->left->val = x->val;
                chng(x->left);
            }
            if (x->right) {
                x->right->val1 = true, x->right->val = x->val;
                chng(x->right);
            }
            x->val1 = false;
        }
    }
    inline void upd (Node*& x) {
        if (!x) return;
        push(x->left);
        push(x->right);
        x->sum = (x->left ? x->left->sum : 0) + x->val + (x->right ? x->right->sum : 0);
        if (x->left && x->right) {
            x->max_left = max(x->left->max_left, x->left->sum + x->val + max(0, x->right->max_left));
            x->max_right = max(x->right->max_right, x->right->sum + x->val + max(0, x->left->max_right));
            x->best = x->val + max(x->left->max_right, 0) + max(x->right->max_left, 0);
            x->best = max(x->best, max(x->left->best, x->right->best));
        } else if (x->left) {
            x->max_left = max(x->left->max_left, x->sum);
            x->max_right = x->val + max(x->left->max_right, 0);
            x->best = max(x->left->best, x->max_right);
        } else if (x->right) {
            x->max_right = max(x->right->max_right, x->sum);
            x->max_left = x->val + max(x->right->max_left, 0);
            x->best = max(x->right->best, x->max_left);
        } else {
            x->max_left = x->max_right = x->best = x->val;
        }
    }

    inline Node* merge (Node* left, Node*right) {
        push(left), push(right);
        if (!left || !right) {
            return (right ? right : left);
        }
        if (left->y < right->y) {
            left->right = merge(left->right, right);
            upd(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            upd(right);
            return right;
        }
    }

    void merge(Node *&treap, Node *left, Node *right) {
        push(left), push(right);
        if (left == NULL) {
            treap = right;
            return;
        }
        if (right == NULL) {
            treap = left;
            return;
        }
        if (left->y < right->y) {
            merge(left->right, left->right, right);
            treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }
        upd(treap);
    }

    inline int f (Node* x) {
        if (x == nullptr) return 0;
        upd(x);
        return x->sz;
    }
    
    inline Node* insert (int l, Node*dum) {
        Node* a; Node*b;
        split(root, a, b, l + 1);
        merge(root, a, dum);
        merge(root, root, b);
        return root;
    }

    inline void to_delete (int l, int r) {
        if (r < l) return;
        Node* a; Node* b; Node* c; Node* d;
        split(root, a, b, l);
        split(b, c, d, r - l + 1);
        merge(root, a, d);
        delete c;
    }

    inline void to_reverse (int l, int r) {
        if (r < l) return;
        Node* a; Node* b; Node* c; Node* d;
        split(root, a, b, l);
        split(b, c, d, r - l + 1);
        c->rev = c->rev ^ 1;
        root = merge(merge(a,c), d);
    }

    inline void modify (int l, int r, int x) {
        Node* a; Node* b; Node* c; Node* d;
        split(root, a, b, l);
        split(b, c, d, r - l + 1);
        c->val1 = true, c->val = x;
        root = merge(a, merge(c, d));
    }
    inline void split(Node *treap, Node *&left, Node *&right, int val) {
        if (!treap) {
            left = right = NULL;
            return;
        }
        upd(treap);
        if (f(treap->left) < val) {
            split(treap->right, treap->right, right, val - f(treap->left) - 1);
            left = treap;
        } else {
            split(treap->left, left, treap->left, val);
            right = treap;
        }
        upd(treap);
    }
    inline int get_sum (int l, int r) {
        if (r < l) return 0;
        Node* a; Node* b; Node* c; Node* d;
        split(root, a, b, l);
        split(b, c, d, r - l + 1);
        int ans = c->sum;
        root = merge(a, merge(c, d));
        return ans;
    }
    inline int get_max_sum () {
        upd(root);
        return root->best;
    }
    void heapify (Node* t) {
        if (!t) return;
        Node* max = t;
        if (t->left != NULL && t->left->y > max->y)
            max = t->left;
        if (t->right != NULL && t->right->y > max->y)
            max = t->right;
        if (max != t) {
            swap (t->y, max->y);
            heapify (max);
        }
    }

    Node* build (int * a, int n) {
        // Construct a treap on values {a[0], a[1], ..., a[n - 1]}
        if (n == 0) return NULL;
        int mid = n / 2;
        Node* t = new Node (a[mid]);
        t->left = build (a, mid);
        t->right = build (a + mid + 1, n - mid - 1);
        heapify (t);
        upd(t);
        return t;
    }

    ImplicitTreap() : root(nullptr) {}
};

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ImplicitTreap it;
    int n, q;
    cin >> n >> q;
    Node* root = nullptr;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    it.root = it.build(arr, n);
    int l, sz, x, pos;
    string s;
    vector<int> tot;
    while (q--) {
        cin >> s;
        if (s == "GET-SUM") {
            cin >> l >> sz;
            l--;
            tot.push_back(it.get_sum(l, l + sz - 1));
        } else if (s == "INSERT") {
            cin >> pos; pos--;
            cin >> sz;
            int a[sz];
            for (int i = 0; i < sz; i++) {
                cin >> a[i];
            }
            it.insert(pos, it.build(a, sz));
        } else if (s == "DELETE") {
            cin >> l >> sz;
            l--;
            it.to_delete(l, l + sz - 1);
        } else if (s == "REVERSE") {
            cin >> l >> sz;
            l--;
            it.to_reverse(l, l + sz - 1);
        } else if (s == "MAKE-SAME") {
            cin >> l >> sz >> x;
            l--;
            it.modify(l, l + sz - 1, x);
        } else {
            tot.push_back(it.get_max_sum());
        }
    }
    for (int i: tot) {
        printf("%d\n", i);
    }
}
