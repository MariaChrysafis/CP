#include <bits/stdc++.h>
using namespace std;
struct Node {
    Node* child[26];
    Node () {
        for (int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
    }
};
struct Trie {
    Node* root;
    int cntr = 0;
    Trie () {
        root = new Node();
    }
    void insert (string s) {
        Node* cur = root;
        for (int i = 0; i < s.size(); i++) {
            if (cur->child[s[i] - 'A'] == nullptr) {
                cur->child[s[i] - 'A'] = new Node();
                cntr++;
            }
            cur = cur->child[s[i] - 'A'];
        }
    }
};
int main() {
    string a;
    Trie* myTrie = new Trie();
    while (cin >> a) {
        myTrie->insert(a);
    }
    cout << myTrie->cntr + 1;
}
