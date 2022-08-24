#include <bits/stdc++.h>
using namespace std;
vector<vector<bool>> hasVisited;
vector<string> grid;
vector<pair<int, int>> pos = {{0,  1}, {-1, 0}, {0,  -1}, {1,  0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    deque<pair<int, pair<int, int>>> q;
    grid.resize(n), hasVisited.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        hasVisited[i].assign(m, false);
    }
    q.push_back({1, {0, 0}});
    int myMax = 0;
    while (!q.empty()) {
        pair<int, int> loc = q.front().second;
        int dist = q.front().first;
        q.pop_front();
        if (hasVisited[loc.first][loc.second]) {
            continue;
        }
        myMax = max(myMax, dist);
        hasVisited[loc.first][loc.second] = true;
        for (auto p: pos) {
            int nx = loc.first + p.first;
            int ny = loc.second + p.second;
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != '.') {
                if (grid[nx][ny] != grid[loc.first][loc.second]) {
                    q.push_back(make_pair(dist + 1, make_pair(nx, ny)));
                } else {
                    q.push_front(make_pair(dist, make_pair(nx, ny)));
                }
            }
        }
    }
    cout << myMax;
}
