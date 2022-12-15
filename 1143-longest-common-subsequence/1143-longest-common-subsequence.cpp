class Solution {
public:
    
int lcs(string &s, int N, string &t, int M, vector<vector<int>> &dp)
{
    for(int n = 0 ; n <= N ; n++){
        for(int m = 0; m <= M;m++){
            if (m == 0 || n == 0)
            {
                dp[n][m] = 0;
                continue;
            }

            // if (dp[n][m] != -1)
            //     return dp[n][m];

            if (s[n - 1] == t[m - 1])
                dp[n][m] = dp[n - 1][m - 1] + 1; // lcs(s, n - 1, t, m - 1, dp) + 1;
            else
                dp[n][m] = max(dp[n - 1][m], dp[n][m - 1]); // max(lcs(s, n - 1, t, m, dp), lcs(s, n, t, m - 1, dp));
        }
    }
    return dp[N][M];
}
    int longestCommonSubsequence(string text1, string text2) {
       int n = text1.size() , m = text2.size();
       vector<vector<int>>dp(n+1,vector<int>(m+1,-1));
       return lcs(text1,n,text2,m,dp); 
    }
};