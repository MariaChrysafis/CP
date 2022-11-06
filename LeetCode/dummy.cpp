class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(factory.begin(),factory.end());
        sort(robot.begin(), robot.end());
        //[position, limit]
        long long dp[robot.size()][factory.size()][110];
        for (int i = 0; i < robot.size(); i++) { 
            for (int j = 0; j < factory.size(); j++) {
                for (int k = 0; k < 110; k++) {
                    dp[i][j][k] = 1e17;
                }
            }
        }
        for (int j = 0; j < factory.size(); j++) {
            dp[0][j][factory[j][1]] = abs(robot[0] - factory[j][0]);
        }
        for (int i = 1; i < robot.size(); i++) {
            for (int j = 0; j < factory.size(); j++) {
                for (int k = 1; k <= 100; k++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k + 1] + abs(robot[i] - factory[j][0]));
                    for (int a = 1; a <= 100; a++) {
                        if (j != 0) {
                            for (int j1 = 0; j1 < j; j1++) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j1][a] + abs(robot[i] - factory[j][0]));
                            }
                        }
                    }
                }
            }
        }
        long long ans = LLONG_MAX;
        for (int j = 0; j < factory.size(); j++) {
            for (int k = 0; k <= 100; k++) {
                ans = min(ans, dp[robot.size() - 1][j][k]);
            }
        }
        return ans;
    }
};
