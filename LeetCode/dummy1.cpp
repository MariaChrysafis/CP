class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(factory.begin(),factory.end());
        sort(robot.begin(), robot.end());
        //[position, limit]
        long long dp[robot.size()][factory.size()][110];
        long long dp1[robot.size()][factory.size()];
        long long dp2[robot.size()][factory.size() + 1];
        for (int i = 0; i < robot.size(); i++) { 
            for (int j = 0; j < factory.size(); j++) {
                for (int k = 0; k < 110; k++) {
                    dp[i][j][k] = 1e17;
                    dp1[i][j] = 1e17;
                    dp2[i][j] = dp2[i][j + 1] = 1e17;
                }
            }
        }
        for (int j = 0; j < factory.size(); j++) {
            dp[0][j][factory[j][1]] = abs(robot[0] - factory[j][0]);
            dp1[0][j] = dp[0][j][factory[j][1]];
            dp2[0][j + 1] = min(dp2[0][j], dp1[0][j]);
        }
        for (int i = 1; i < robot.size(); i++) {
            for (int j = 0; j < factory.size(); j++) {
                for (int k = 1; k <= 100; k++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k + 1] + abs(robot[i] - factory[j][0]));                                            dp[i][j][k] = min(dp[i][j][k], dp2[i - 1][j] + abs(robot[i] - factory[j][0]));
                    dp1[i][j] = min(dp1[i][j], dp[i][j][k]);
                }
                dp2[i][j + 1] = min(dp2[i][j], dp1[i][j]);
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
