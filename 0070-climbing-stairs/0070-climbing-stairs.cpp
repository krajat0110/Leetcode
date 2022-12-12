class Solution {
public:
    int climbStairs(int N) {
        vector<int> dp(N+1);
        for(int n = 0 ; n <= N ; n++){
            if(n == 0){
                dp[n] = 1;
                continue;
            }
            
            dp[n] = dp[n-1];
            
            if(n>=2){
            dp[n] += dp[n-2];
            }
        }
        return dp[N];
    }
};