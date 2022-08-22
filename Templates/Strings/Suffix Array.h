class SuffixArray {
public:
    SuffixArray(string s) {
        s += '$';
        int64_t n = s.length();
        vector<int> eq(s.length());
        vector<pair<char, int> > vec;
        for (int i = 0; i < s.length(); i++) {
            vec.push_back(make_pair(s[i], i));
        }
        sort(vec.begin(), vec.end());
        int cntr = 0;
        eq[vec[0].second] = 0;
        for (int i = 1; i < vec.size(); i++) {
            eq[vec[i].second] = eq[vec[i - 1].second] + (vec[i].first != vec[i - 1].first);
        }
        for (int i = 0; (1 << i) < n; i++) {
            vector<pair<int64_t, int> > tot;
            for (int j = 0; j < vec.size(); j++) {
                tot.push_back(make_pair((n + 1) * eq[j] + eq[(j + (1 << i)) % n], j));
            }
            sort(tot.begin(), tot.end());
            eq[tot[0].second] = 0;
            for (int j = 1; j < vec.size(); j++) {
                eq[tot[j].second] = eq[tot[j - 1].second] + (tot[j].first != tot[j - 1].first);
            }
        }
        vector<pair<int,int> > v;
        for (int i = 0; i < n; i++) {
            v.push_back(make_pair(eq[i], i));
        }
        sort(v.begin(), v.end());
        for (int i = 1; i < v.size(); i++) {
            cout << v[i].second << ' ';
        }
        cout << '\n';
    }
};
