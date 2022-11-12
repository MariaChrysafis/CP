import numpy as np
class Solution:
    def split (self, nums: List[int]) -> List[List[int]]:
        n = len(nums) 
        dp = [ [] for _ in range(n + 1) ]
        pw = (1 << (n - 1))
        sm = sum(nums)
        for i in range(pw) :
            x = sum(nums[j] for j in range(len(nums)) if i & (1 << j))
            dp[i.bit_count()].append(sm - 2 * x)
            dp[n - i.bit_count()].append(-(sm - 2 * x))
        for i in range(len(dp)) :
            dp[i].sort()
        return dp    

    def minimumDifference(self, nums: List[int]) -> int:
        n = len(nums)
        a = self.split(nums[0:int(n/2)])
        b = self.split(nums[int(n/2):n])
        mn = 100000000
        for i1 in range(len(a)) :
            i2 = int(n/2) - i1
            r = len(b[i2]) - 1
            for j1 in range(len(a[i1])) :
                if len(b[i2]) == 0 or b[i2][len(b[i2]) - 1] + a[i1][j1] < 0 :
                    continue
                l = bisect.bisect_left(b[i2], -a[i1][j1])
                if mn > a[i1][j1] + b[i2][l] :
                    mn = a[i1][j1] + b[i2][l]
        return mn
