#include <bits/stdc++.h>
using namespace std;
struct Node {
    Node* left;
    Node* right;
    long long x, y;
    long long val1, val2;
    Node (long long x, long long val) {
        this->x = x, this->y = rand(), this->left = nullptr, this->right = nullptr, this->val1 = this->val2 = val;
    }
};
long long gcd (long long a, long long b) {
    if (!a || !b) return max(a,b );
    return gcd(max(a, b) % min(a, b), min(a, b));
}
void print (Node*x) {
    if (x != nullptr) {
        print(x->left);
        print(x->right);
    }
}
long long g (Node*x) {
    return ((x == nullptr) ? 0 : x->val2);
}
void upd (Node*&x) {
    x->val2 = gcd(gcd(g(x->left), g(x->right)), x->val1);
}
pair<Node*, Node*> splitX (Node*cur, long long x) {
    if (cur == nullptr) return make_pair(nullptr, nullptr);
    if (cur->right == nullptr && cur->x <= x) {
        return make_pair(cur, nullptr);
    } 
    if (cur->left == nullptr && cur->x > x) {
        return make_pair(nullptr, cur);
    }
    if (cur->x <= x) {
        auto p = splitX(cur->right, x);
        cur->right = p.first;
        upd(cur);
        return make_pair(cur, p.second);
    } else {
        auto p = splitX(cur->left, x);
        cur->left = p.second;
        upd(cur);
        return make_pair(p.first, cur);
    }
}
Node* merge (Node* node1, Node* node2) {
    if (node1 == nullptr) return node2;
    if (node2 == nullptr) return node1;
    if (node2->y <= node1->y) {
        node2->left = merge(node1, node2->left);
        upd(node2);
        return node2;
    } else {
        node1->right = merge(node1->right, node2);
        upd(node1);
        return node1;
    }
}
 
int64_t query (Node* root, int l, int r) {
    auto p = splitX(root, l - 1); //[<= l - 1, >= l]
    auto q = splitX(p.second, r); //[>= l <= r, >r]
    long long ans = g(q.first);
    root = merge(p.first, merge(q.first, q.second));
    return ans;
}
 
void update (Node*& root, int x, long long val) {
    //update the thing at index x to be val
    auto p = splitX(root, x - 1); //<=x - 1, >= x
    auto q = splitX(p.second, x); //>= x and <= x
    root = merge(p.first, merge(new Node(x, val), q.second));
}
 
struct SegmentTree {
    Node* root;
    SegmentTree* l;
    SegmentTree* r;
    int left, right;
    SegmentTree () {
        this->l = this->r = nullptr;
    }
    SegmentTree (int left, int right) {
        this->left = left, this->right = right, this->l = nullptr, this->r = nullptr, this->root = nullptr;
    }
    void upd (int x, int y, int64_t val) {
        if (left > y || right < y) {
            return;
        }
        if (left == y && right == y) {
            update(root, x, val);
            return;
        }
        if (y >= left && y <= (left + right)/2) {
            if (l == nullptr) l = new SegmentTree(left, (left + right)/2);
            l->upd(x, y, val);
        } else {
            if (r == nullptr) r = new SegmentTree((left + right)/2 + 1, right);
            r->upd(x, y, val);
        }
        int64_t ans = 0;
        if (l != nullptr) ans = gcd(ans, query(l->root, x, x));
        if (r != nullptr) ans = gcd(ans, query(r->root, x, x));
        update(root, x, ans);
    }
    int64_t get (int x1, int y1, int x2, int y2) {
        if (left > y2 || right < y1) {
            return 0;
        }
        if (left >= y1 && right <= y2) {
            return query(root, x1, x2);
        }
        int64_t ans = 0;
        if (l != nullptr) {
            ans = gcd(ans, l->get(x1, y1, x2, y2));
        }
        if (r != nullptr) {
            ans = gcd(ans, r->get(x1, y1, x2, y2));
        }
        return ans;
    }
};

SegmentTree* st;

void init (int n, int m) {
    st = new SegmentTree(0, max(n, m) + 1);
}

void update (int x, int y, long long z) {
    st->upd(x, y, z);
}

long long calculate (int x1, int y1, int x2, int y2) {
    return st->get(x1, y1, x2, y2);
}
