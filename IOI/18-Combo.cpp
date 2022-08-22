#include <bits/stdc++.h>
#include "combo.h"
 
using namespace std;
string oracle = "YBY";
bool isSubstring (string substr, string s) {
    for (int i = 0; i < s.length(); i++) {
        if (i + substr.length() - 1 < s.length() && s.substr(i, substr.length()) == substr) {
            return true;
        }
    }
    return false;
}

string guess_sequence (int N) {
    string so_far = "";
    if (press("AX") != 0) {
        if (press("A")) {
            so_far = "A";
        } else {
            so_far = "X";
        }
    } else {
        if (press("B")) {
            so_far = "B";
        } else {
            so_far = "Y";
        }
    }
    if (N == 1) {
        return so_far;
    }
    for (int i = 1; i < N - 1; i ++) {
        vector<string> pos;
        for (string c: {"A", "B", "X", "Y"}) {
            if (so_far[0] != c[0]) {
                pos.push_back(c);
            }
        }
        string qry;
        for (string s: pos) {
            qry += so_far + pos[0] + s;
        }
        qry += so_far + pos[1];
        int res = press(qry);
        if (res == so_far.size()) {
            so_far += pos[2];
        } else if (res == so_far.size() + 1) {
            so_far += pos[1];
        } else {
            so_far += pos[0];
        }
    }
    assert(so_far.size() == N - 1);
    if (press(so_far + 'A' + so_far + 'X') == N) {
        if (press(so_far + 'A') == N) {
            return so_far + 'A';
        } else {
            return so_far + 'X';
        }
    } else {
        if (press(so_far + 'B') == N) {
            return so_far + 'B';
        } else {
            return so_far + 'Y';
        }
    }
    assert(so_far == oracle);
}
