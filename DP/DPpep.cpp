#include <iostream>
#include <vector>
using namespace std;
long mod = (int)1e9 + 7;

void display(vector<int> &dp)
{
    for (auto ele : dp)
    {
        cout << ele << " ";
    }
    cout << endl;
}

void display2D(vector<vector<int>> &dp)
{
    for (auto d : dp)
    {
        display(d);
    }
    cout << endl;
}

int fibo_memo(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = n;

    if (dp[n] != 0)
        return dp[n];

    int ans = fibo_memo(n - 2, dp) + fibo_memo(n - 1, dp);
    return dp[n] = ans;
}

int fibo_tobu(int N)
{
    vector<int> dp(N + 1);
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }

        int ans = dp[n - 2] + dp[n - 1];
        dp[n] = ans;
    }
    return dp[N];
}

int fibo_opti(int N)
{
    int a = 0, b = 1;
    for (int i = 2; i <= N; i++)
    {
        int sum = a + b;
        a = b;
        b = sum;
        // cout<<a<<" "<<b<<endl;
    }
    return b;
}

// climbing stairs
int climbStairs(int n)
{
    int dp[n + 1];
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            dp[i] = 1;
            continue;
        }
        dp[i] = dp[i - 1];
        if (i >= 2)
        {
            dp[i] += dp[i - 2];
        }
    }
    return dp[n];
}

// 746. Min Cost Climbing Stairs
int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    int dp[n];
    for (int i = 0; i < n; i++)
    {
        if (i <= 1)
        {
            dp[i] = cost[i];
            continue;
        }
        int ans = min(dp[i - 1], dp[i - 2]) + cost[i];
        dp[i] = ans;
    }
    return min(dp[n - 2], dp[n - 1]);
}

int mazEPath_memo(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
{
    if (SR == ER && SC == EC)
    {
        return dp[SR][SC] = 1;
    }

    if (dp[SR][SC] != 0)
    {
        return dp[SR][SC];
    }

    int cnt = 0;
    for (auto d : dir)
    {
        int x = SR + d[0], y = SC + d[1];
        if (x >= 0 && y >= 0 && x < dp.size() && y < dp[0].size())
        {
            cnt += mazEPath_memo(x, y, ER, EC, dp, dir);
        }
    }
    return dp[SR][SC] = cnt;
}

int mazEPath_tabu(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
{ // start the loop from ending buz the ans is dependent on prev 3 blocks   up down and diagonal
    for (int er = ER; er >= SR; er--)
    {
        for (int ec = EC; ec >= SC; ec--)
        {
            if (er == ER && ec == EC)
            {
                dp[er][ec] = 1;
                continue;
            }

            int cnt = 0;
            for (auto d : dir)
            {
                int x = er + d[0], y = ec + d[1];
                if (x >= 0 && y >= 0 && x < dp.size() && y < dp[0].size())
                {
                    cnt += dp[x][y];
                }
            }
            dp[er][ec] = cnt;
        }
    }
    return dp[SR][SC];
}

int mazEPathmulti_memo(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
{
    if (SR == ER && SC == EC)
    {
        return dp[SR][SC] = 1;
    }

    if (dp[SR][SC] != 0)
    {
        return dp[SR][SC];
    }

    int cnt = 0;
    for (auto d : dir)
    {
        int x = SR + d[0], y = SC + d[1];
        while (x >= 0 && y >= 0 && x < dp.size() && y < dp[0].size())
        {
            cnt += mazEPathmulti_memo(x, y, ER, EC, dp, dir);
            x += d[0];
            y += d[1];
        }
    }
    return dp[SR][SC] = cnt;
}

int mazEPathmulti_tabu(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
{
    for (int er = ER; er >= SR; er--)
    {
        for (int ec = EC; ec >= SC; ec--)
        {
            if (er == ER && ec == EC)
            {
                dp[er][ec] = 1;
                continue;
            }

            int cnt = 0;
            for (auto d : dir)
            {
                int x = SR + d[0], y = SC + d[1];
                while (x >= 0 && y >= 0 && x < dp.size() && y < dp[0].size())
                {
                    cnt += mazEPathmulti_tabu(x, y, ER, EC, dp, dir);
                    x += d[0];
                    y += d[1];
                }
            }
            dp[er][ec] = cnt;
        }
    }
    return dp[SR][SC];
}

// unique path II

int mazEPath_memo(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir, vector<vector<int>> &grid)
{
    if (SR == ER && SC == EC)
    {
        dp[SR][SC] = 1;
    }

    if (dp[SR][SC] != -1)
    {
        return dp[SR][SC];
    }

    long cnt = 0;
    for (auto d : dir)
    {
        int x = SR + d[0];
        int y = SC + d[1];
        if (x >= 0 && y >= 0 && x < dp.size() && y < dp[0].size() && grid[x][y] == 0)
        {
            cnt += mazEPath_memo(x, y, ER, EC, dp, dir, grid);
        }
    }
    return dp[SR][SC] = cnt;
}

int mazEPath_tabu(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir, vector<vector<int>> &obstacleGrid)
{

    for (int sr = ER; sr >= SR; sr--)
    {
        for (int sc = EC; sc >= SC; sc--)
        {
            if (sr == ER && sc == EC)
            {
                dp[sr][sc] = 1;
                continue;
            }
            long count = 0;
            for (auto d : dir)
            {
                int r = sr + d[0];
                int c = sc + d[1];
                if (r >= 0 && c >= 0 && r < dp.size() && c < dp[0].size() && obstacleGrid[r][c] == 0)
                {
                    count += dp[r][c];
                }
            }

            dp[sr][sc] = count;
        }
    }
    return dp[SR][SC];
}

int uniquEPathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int SR = 0, SC = 0, ER = obstacleGrid.size(), EC = obstacleGrid[0].size();
    if (obstacleGrid[SR][SC] == 1 || obstacleGrid[ER - 1][EC - 1] == 1)
    {
        return 0;
    }
    vector<vector<int>> dp(ER, vector<int>(EC));

    vector<vector<int>> dir = {{1, 0}, {0, 1}};
    return mazEPath_tabu(SR, SC, ER - 1, EC - 1, dp, dir, obstacleGrid);
}

int boardGame_memo(int SP, int EP, vector<int> &dp)
{
    if (SP == EP)
    {
        return dp[SP] = 1;
    }

    if (dp[SP] != 0)
    {
        return dp[SP];
    }
    int cnt = 0;
    for (int s = 1; s <= 6 && s + SP < EP; s++)
    {
        cnt += boardGame_memo(SP + s, EP, dp);
    }
    return dp[SP] = cnt;
}

int boardGame_tabu(int SP, int EP, vector<int> &dp)
{
    for (int sp = EP; sp >= 0; sp--)
    {
        if (sp == EP)
        {
            dp[sp] = 1;
            continue;
        }

        int cnt = 0;
        for (int s = 1; s <= 6 && s + SP <= EP; s++)
        {
            cnt += dp[s + sp];
        }
        dp[sp] = cnt;
    }
    return dp[SP];
}

// leetcode 91
// memoization function
int helper(string s, int idx, vector<int> &dp)
{
    if (idx == s.size())
        return dp[idx] = 1;

    if (dp[idx] != -1)
        return dp[idx];

    char ch = s[idx];
    if (ch == '0')
        return dp[idx] = 0;
    int count = helper(s, idx + 1, dp);

    if (idx < s.size() - 1)
    {
        char ch1 = s[idx + 1];
        int num = (ch - '0') * 10 + (ch1 - '0');
        if (num <= 26)
            count += helper(s, idx + 2, dp);
    }
    return dp[idx] = count;
}

// tabulation function  leetocde 91

int helpertabu(string s, int IDX, vector<int> &dp)
{
    for (int idx = s.size(); idx >= 0; idx--)
    {
        if (idx == s.size())
        {
            dp[idx] = 1;
            continue;
        }

        char ch = s[idx];
        if (ch == '0')
        {
            dp[idx] = 0;
            continue;
        }

        int count = dp[idx + 1];

        if (idx < s.size() - 1)
        {
            char ch1 = s[idx + 1];
            int num = (ch - '0') * 10 + (ch1 - '0');
            if (num <= 26)
                count += dp[idx + 2];
        }
        dp[idx] = count;
    }
    return dp[IDX];
}

// optimized
int helpertabu(string s)
{
    int a = 1, b = 0;
    for (int idx = s.size(); idx >= 0; idx--)
    {
        char ch = s[idx];
        int sum = 0;
        if (ch != '0')
        {
            sum += a;
            if (idx < s.size() - 1)
            {
                char ch1 = s[idx + 1];
                int num = (ch - '0') * 10 + (ch1 - '0');
                if (num <= 26) // agar no 26 se bata ho gaya to idx +2 wala add mahi hoga
                    sum += b;
            }
        }
        b = a;
        a = sum;
    }
    return a;
}

// decode ways 2
// memoization function


long long helpermemo(string &s, int idx, vector<long long> &dp)
{
    int n = s.size();
    if (n == idx)
    {
        return dp[idx] = 1;
    }
    if (dp[idx] != -1)
        return dp[idx];

    char ch = s[idx];
    if (ch == '0')
        return dp[idx] = 0;

    long long cnt = 0;
    if (ch == '*')
    {
        cnt = cnt + (9 * helpermemo(s, idx + 1, dp)) % mod; // first char can be between 1 to 9;
        if (idx < n - 1)
        {
            char ch1 = s[idx + 1];
            if (ch1 >= '0' && ch1 <= '6')
            {
                cnt = (cnt + 2 * helpermemo(s, idx + 2, dp)) % mod; // if first ele is * then 2 ele can only be 1 or 2
            }
            else if (ch1 >= '7' && ch1 <= '9')
            {
                cnt = (cnt + 1 * helpermemo(s, idx + 2, dp)) % mod; // so no will be 17,18,19 therefore only 1 call occur
            }
            else
            {
                cnt = (cnt + 15 * helpermemo(s, idx + 2, dp)) % mod; // case =  * * so there are 15 possibilty 11,12 .... 26 axcept 20
            }
        }
    }
    else
    {
        cnt = (cnt + 1 * helpermemo(s, idx + 1, dp)) % mod;
        if (idx < n - 1)
        {
            char ch2 = s[idx + 1];
            if (ch == '1' && ch2 == '*')
            {
                cnt = (cnt + 9 * helpermemo(s, idx + 2, dp)) % mod;
            }
            else if (ch == '2' && ch2 == '*')
            {
                cnt = (cnt + 6 * helpermemo(s, idx + 2, dp)) % mod;
            }
            else if (ch2 != '*')
            {
                int num = (ch - '0') * 10 + (ch2 - '0');
                if (num <= 26)
                    cnt = (cnt + 1 * helpermemo(s, idx + 2, dp)) % mod;
            }
        }
    }
    return dp[idx] = cnt;
}

// tabulation function

long long helpertabu(string &s, int IDX, vector<long long> &dp)
{
    int n = s.size();
    for (int idx = n; idx >= 0; idx--)
    {
        if (n == idx)
        {
            dp[idx] = 1;
            continue;
        }

        char ch = s[idx];
        if (ch == '0')
        {
            dp[idx] = 0;
            continue;
        }
        long long cnt = 0;
        if (ch == '*')
        {
            cnt = cnt + (9 * dp[idx + 1]) % mod; // first char can be between 1 to 9;
            if (idx < n - 1)
            {
                char ch1 = s[idx + 1];
                if (ch1 >= '0' && ch1 <= '6')
                {
                    cnt = (cnt + 2 * dp[idx + 2]) % mod; // if first ele is * then 2 ele can only be 1 or 2
                }
                else if (ch1 >= '7' && ch1 <= '9')
                {
                    cnt = (cnt + 1 * dp[idx + 2]) % mod; // so no will be 17,18,19 therefore only 1 call occur
                }
                else
                {
                    cnt = (cnt + 15 * dp[idx + 2]) % mod; // case =  * * so there are 15 possibilty 11,12 .... 26 axcept 20
                }
            }
        }
        else
        {
            cnt = (cnt + 1 * dp[idx + 1]) % mod;
            if (idx < n - 1)
            {
                char ch2 = s[idx + 1];
                if (ch == '1' && ch2 == '*')
                {
                    cnt = (cnt + 9 * dp[idx + 2]) % mod;
                }
                else if (ch == '2' && ch2 == '*')
                {
                    cnt = (cnt + 6 * dp[idx + 2]) % mod;
                }
                else if (ch2 != '*')
                {
                    int num = (ch - '0') * 10 + (ch2 - '0');
                    if (num <= 26)
                        cnt = (cnt + 1 * dp[idx + 2]) % mod;
                }
            }
        }
        dp[idx] = cnt;
    }
    return dp[IDX];
}

int numDecodings(string s)
{
    int n = s.size();
    vector<long long> dp(n + 1, -1);
    // long long ans = helpermemo(s, 0, dp);
    long long ans = helpertabu(s, 0, dp);

    return (int)ans;
}

// gold mine
// https://practice.geeksforgeeks.org/problems/gold-mine-problem2608/1
int goldsum(int sr, int sc, vector<vector<int>> &M, vector<vector<int>> &dis, vector<vector<int>> &dp)
{
    int n = M.size(), m = M[0].size();
    if (sc == m - 1)
    {
        return dp[sr][sc] = M[sr][sc];
    }

    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int cnt = 0;
    for (auto d : dis)
    {
        int x = sr + d[0];
        int y = sc + d[1];
        if (x >= 0 && y >= 0 && x < n && y < m)
        {
            cnt = max(cnt, goldsum(x, y, M, dis, dp) + M[sr][sc]);
        }
    }
    return dp[sr][sc] = cnt;
}

int maxGold(int n, int m, vector<vector<int>> &M)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    vector<vector<int>> dis = {{0, 1}, {1, 1}, {-1, 1}};

    int maxgold = 0;
    for (int i = 0; i < n; i++)
    {
        maxgold = max(maxgold, goldsum(i, 0, M, dis, dp));
    }
    return maxgold;
}




// https://practice.geeksforgeeks.org/problems/friends-pairing-problem5425/1

long ways(int n, vector<long> &dp)
{
    if (n == 0)
        return dp[n] = 1;

    if (dp[n] != -1)
        return dp[n];

    long single = ways(n - 1, dp);
    long pair = n - 2 >= 0 ? ways(n - 2, dp) * (n - 1) : 0;

    return dp[n] = (single + pair % mod) % mod;
}

int countFriendsPairings(int n)
{
    if (n == 0)
        return 0;
    vector<long> dp(n + 1, -1);
    long ans = ways(n, dp);
    return (int)ans;
}

long long countFriendsPairings01(int n)
{
    long long a = 1, b = 1;
    for (int i = 2; i <= n; i++)
    {
        long sum = b + (a * (i - 1)) % mod;
        a = b;
        b = sum % mod;
    }
    return b;
}
// https://www.geeksforgeeks.org/count-the-number-of-ways-to-divide-n-in-k-groups-incrementally/

long long divideInKGroup(int n, int k, vector<vector<int>> &dp)
{
    if (n == k || k == 1)
    {
        return dp[n][k] = 1;
    }

    if (dp[n][k] != 0)
        return dp[n][k];

    long long singlepair = divideInKGroup(n - 1, k - 1, dp);
    long long makepair = divideInKGroup(n - 1, k, dp) * k;

    return dp[n][k] = singlepair + makepair;
}

int divideInKGroup01(int N, int K, vector<vector<int>> &dp)
{
    for (int n = 1; n <= N; n++)
    {
        for (int k = 1; k <= K; k++)
        {
            if (n == k || k == 1)
            {
                dp[n][k] = 1;
                continue;
            }
            long long singlepair = dp[n - 1][k - 1];
            long long makepair = (dp[n - 1][k] * k);

            dp[n][k] = (singlepair + makepair);
        }
    }
    return dp[N][K];
}

int makepair_02(int n, int k, vector<vector<int>> &dp)

{
    // vector<vector<long long>> dp(n+1, vector<long long>(k+1, 0));
    long long ans = divideInKGroup(n, k, dp);
    return (int)ans;
}

// 516. Longest Palindromic Subsequence

//memoization function

long long lps(int i , int j ,string &s, vector<vector<int>> &dp){
    if(i>= j){
        return dp[i][j] = i == j ? 1 : 0;
    }

    if(dp[i][j] != -1)
       return dp[i][j];

    if(s[i] == s[j]){
       return dp[i][j] = lps(i+1 , j - 1, s , dp) + 2;
    }else{
        return dp[i][j] = max(lps(i+1,j,s,dp) , lps(i , j -1 , s , dp));
    }
}

int longestPalindromeSubseq(string s){
    int n = s.size();
    vector<vector<int>>dp(n,vector<int>(n,-1));
    long long ans = lps(0 , n - 1, s, dp);
    return (int)ans;
}


//tabulation function
int lps_tubo(int I, int J, string &s, vector<vector<int>> &dp)
{
    int n = s.size();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i >= j)
            {
                dp[i][j] = (i == j ? 1 : 0);
                continue;
            }

            if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[I][J];
}

int longestPalindromeSubseq(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));
    return lps_tubo(0, n - 1, s, dp);
}

//1143. Longest Common Subsequence

int lcs(string &s, int n, string &t, int m, vector<vector<int>> &dp)
{
    if (m == 0 || n == 0)
    {
        return dp[n][m] = 0;
    }

    if (dp[n][m] != -1)
        return dp[n][m];

    if (s[n - 1] == t[m - 1])
        dp[n][m] = lcs(s, n - 1, t, m - 1, dp) + 1;
    else
        dp[n][m] = max(lcs(s, n - 1, t, m, dp), lcs(s, n, t, m - 1, dp));

    return dp[n][m];
}

int lcs01(string &s, int N, string &t, int M, vector<vector<int>> &dp)
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

int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return lcs(text1, n, text2, m, dp);
}

//distint subsequence
int helper(string s, int n, string t, int m, vector<vector<int>> &dp)
{

    if (m == 0)
        return dp[n][m] = 1;
    if (n < m)
        return dp[n][m] = 0;

    if (dp[n][m] != -1)
        return dp[n][m];

    if (s[n - 1] == t[m - 1])
        return dp[n][m] = helper(s, n - 1, t, m - 1, dp) + helper(s, n - 1, t, m, dp);
    else
        return dp[n][m] = helper(s, n - 1, t, m, dp);
}


//tabulation function
int mod = (int)1e9 + 7;
long long helper(string &s, int N, string &t, int M, vector<vector<long long>> &dp)
{
    for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            if (m == 0)
            {
                dp[n][m] = 1;
                continue;
            }
            if (n < m)
            {
                dp[n][m] = 0;
                continue;
            }

            if (s[n - 1] == t[m - 1])
                dp[n][m] = dp[n - 1][m - 1] + dp[n - 1][m] % mod;
            else
                dp[n][m] = dp[n - 1][m] % mod;
        }
    }
    return dp[N][M] % mod;
}

int numDistinct(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -1));
    long long ans = helper(s, n, t, m, dp);
    return (int)ans % mod;
}

//edit distance
int ways(string &s, int i, string &t, int j, vector<vector<int>> &dp)
{
    if (i == 0){
        return dp[i][j] = j;
    }
    if (j == 0)
    {
        return dp[i][j] = i;
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    int insert = ways(s, i, t, j - 1, dp);
    int dlt = ways(s, i - 1, t, j, dp);
    int replace = ways(s, i - 1, t, j - 1, dp);

    if (s[i - 1] == t[j - 1])
        return dp[i][j] = replace;
    else
        return dp[i][j] = min(insert, min(dlt, replace)) + 1;
}

//tabulation function
int ways(string &s, int I, string &t, int J, vector<vector<int>> &dp)
{
    for (int i = 0; i <= I; i++)
    {
        for (int j = 0; j <= J; j++)
        {
            if (i == 0){
                dp[i][j] = j;
                continue;
            }
            if (j == 0){
                dp[i][j] = i;
                continue;
            }

            int insert = dp[i][j - 1];
            int dlt = dp[i - 1][j];
            int replace = dp[i - 1][j - 1];

            if (s[i - 1] == t[j - 1])
                dp[i][j] = replace;
            else
                dp[i][j] = min(insert, min(dlt, replace)) + 1;
        }
    }
    return dp[I][J];
}

int minDistance(string word1, string word2)
{
    int i = word1.size(), j = word2.size();
    vector<vector<int>> dp(i + 1, vector<int>(j + 1, -1));
    return ways(word1, i, word2, j, dp);
}


//follow up of edit distance 
//1. given cost of insert , delete and replace return the cost of replacing the string;
//0 = insert , 1 = delete , 2 = replace;
int ways(string &s, int i, string &t, int j, vector<int>&cost,vector<vector<int>> &dp)
{
    if (i == 0)
    {
        return dp[i][j] = j * cost[0]; //first string become 0 so now i just have to insert;
    }
    if (j == 0)
    {
        return dp[i][j] = i * cost[1]; // second string become 0 so now i just have to delete 1 string;

    }

    if (dp[i][j] != -1)
        return dp[i][j];

    int insert = ways(s, i, t, j - 1,cost, dp);
    int dlt = ways(s, i - 1, t, j,cost,dp);
    int replace = ways(s, i - 1, t, j - 1,cost ,dp);

    if (s[i - 1] == t[j - 1])
        return dp[i][j] = replace;
    else
        return dp[i][j] = min(insert + cost[0], min(dlt + cost[1], replace + cost[2])) + 1;
}

//2. given 3 array with cost of each operation like delete , insert and replace  dlt[i] = cost of dlt i charater and so on ...size()



//wildcard matching
string removestar(string &p)
{
    string ans = "";
    if (p.size() == 0)
        return p;

    ans += p[0];
    int i = 1;
    while (i < p.size())
    {
        while (i < p.size() && ans[ans.size() - 1] == '*' && p[i] == '*')
            i++;

        if (i < p.size())
            ans += p[i];
        i++;
    }
    return ans;
}

int isequal(string &s, int n, string &t, int m, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
    {
        if (n == 0 && m == 0)
            return dp[n][m] = 1;
        else if (m == 1 && t[m - 1] == '*')
            return dp[n][m] = 1;
        else
            return dp[n][m] = 0;
    }

    if (dp[n][m] != -1)
        return dp[n][m];

    char ch1 = s[n - 1];
    char ch2 = t[m - 1];

    if (ch1 == ch2 || ch2 == '?'){
        return dp[n][m] = isequal(s, n - 1, t, m - 1, dp);
    }
    else if (ch2 == '*'){
        bool res = false;

        res = res || isequal(s, n - 1, t, m, dp) == 1; // sequence of charater
        res = res || isequal(s, n, t, m - 1, dp) == 1; // empty string

        return dp[n][m] = res ? 1 : 0;
    }
    else{
        return dp[n][m] = 0;
    }
}

int isequal_tabu(string &s, int N, string &t, int M, vector<vector<int>> &dp)
{
    for (int n = 0; n <= N; n++){
        for (int m = 0; m <= M; m++){
            if (n == 0 || m == 0){
                if (n == 0 && m == 0){
                    dp[n][m] = 1;
                    continue;
                }else if (m == 1 && t[m - 1] == '*'){
                    dp[n][m] = 1;
                    continue;
                }else{
                    dp[n][m] = 0;
                    continue;
                }
            }

            char ch1 = s[n - 1];
            char ch2 = t[m - 1];
            if (ch1 == ch2 || ch2 == '?'){
                dp[n][m] = dp[n - 1][m - 1]; // isequal(s,n-1,t,m-1,dp);
            }
            else if (ch2 == '*'){
                bool res = false;

                res = res || dp[n - 1][m] == 1; // isequal(s,n - 1,t,m,dp) == 1; //sequence of charater
                res = res || dp[n][m - 1] == 1; // isequal(s,n,t,m-1,dp) == 1; //empty string

                dp[n][m] = res ? 1 : 0;
            }
            else
                dp[n][m] = 0;
        }
    }
    return dp[N][M];
}

bool isMatch(string s, string p)
{
    if (s == p)
        return true;
    p = removestar(p);
    int n = s.size(), m = p.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    int ans = isequal(s, n, p, m, dp);

    return ans == 1;
}

//leetcode 1035
int linescnt(vector<int> &s, int N, vector<int> &t, int M, vector<vector<int>> &dp)
{
    for (int n = 0; n <= N; n++)
    {
        for (int m = 0; m <= M; m++)
        {
            if (n == 0 || m == 0)
            {
                dp[n][m] = 0;
                continue;
            }

            if (s[n - 1] == t[m - 1])
                dp[n][m] = dp[n - 1][m - 1] + 1; // linescnt(s, n-1,t,m-1,dp) + 1;
            else
                dp[n][m] = max(dp[n - 1][m], dp[n][m - 1]); // max(linescnt(s,n-1,t,m,dp) , linescnt(s,n, t ,m - 1, dp));
        }
    }
    return dp[N][M];
}

int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    int ans = linescnt(nums1, n, nums2, m, dp);
    return ans;
}

// 1458. Max Dot Product of Two Subsequences

int maxprod(vector<int>&s,int n , vector<int>&t, int m , vector<vector<int>>&dp){
   
   if(n == 0 || m == 0)
    return dp[n][m] = -(int)1e8;

   if(dp[n][m] != -(int)1e9)
    return dp[n][m];
   
   int val = s[n-1] * t[m-1];
   int both = maxprod(s,n - 1, t, m - 1, dp);
   int a = maxprod(s,n-1, t, m, dp);
   int b = maxprod(s,n, t, m - 1, dp);

   return dp[n][m] = max(both,max(a,max(b,val)));
}

int maxDotProduct(vector<int> &nums1, vector<int> &nums2){
    int n = nums1.size() , m = nums2.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,-1e9));
    int ans = maxprod(nums1,n,nums2,m,dp);
    return ans;
}

// 132. Palindrome Partitioning II
int minCut1(string s, int si, int ei, vector<int> &dp, vector<vector<bool>> &pdp)
{
    if (pdp[si][ei])
        return 0;
    if (dp[si] != -1)
        return dp[si];

    int minans = (int)1e8;
    for (int cut = si; cut <= ei; cut++)
    {
        if (pdp[si][cut])
            minans = min(minans, minCut1(s, cut + 1, ei, dp, pdp) + 1);
    }
    return dp[si] = minans;
}

int minCut(string s)
{
    int n = s.size();
    vector<vector<bool>> pdp(n, vector<bool>(n, false));
    for (int gap = 0; gap < n; gap++)
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (gap == 0)
                pdp[i][j] = true;
            else if (gap == 1 && s[i] == s[j])
            {
                pdp[i][j] = true;
            }
            else
                pdp[i][j] = s[i] == s[j] && pdp[i + 1][j - 1];
        }
    vector<int> dp(n + 1, -1);
    return minCut1(s, 0, n - 1, dp, pdp);
}

// 5. Longest Palindromic Substring

 // length of lps , ans  , no of palindromic substring
string longestPalindrome(string s)
{
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int max = 0, cnt = 0, si = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = true;
            else if (gap == 1 && s[i] == s[j])
                dp[i][j] = true;
            else
                dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];

            if (dp[i][j])
            { // dp[i][j] == true
                cnt++;
                if (j - i + 1 > max)
                {
                    max = j - i + 1;
                    si = i;
                }
            }
        }
    }
    return s.substr(si, max);
}

// 583. Delete Operation for Two Strings

int nodlt(string &s, int n, string &t, int m, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
        return dp[n][m] = m == 0 ? n : m;

    if (dp[n][m] != -1)
        return dp[n][m];

    if (s[n - 1] == t[m - 1])
        return dp[n][m] = nodlt(s, n - 1, t, m - 1, dp);
    else
        return dp[n][m] = min(nodlt(s, n, t, m - 1, dp), nodlt(s, n - 1, t, m, dp)) + 1;
}

int minDistance(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return nodlt(word1, n, word2, m, dp);
}
//alternate ans;
// word1 length + word2 length  - 2 * LCS;

// Number of subsequences of the form a^i b^j c^k
int fun(string &s)
{
    int n = s.size();
    long long emptycnt = 1, acnt = 0, bcnt = 0, ccnt = 0, mod = (long long)1e9 + 7;
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];

        if (ch == 'a')
            acnt = acnt + (emptycnt + acnt) % mod;
        else if (ch == 'b')
            bcnt = bcnt + (acnt + bcnt) % mod;
        else if (ch == 'c')
            ccnt = ccnt + (bcnt + ccnt) % mod;
    }

    return (int)(ccnt % mod);
}

//longest palindrome string;
//abcbba = abcba;

string longestpalindromesubstring(string str , int si , int ei , vector<vector<int>>dp) {
    if(si >= ei){
        return si == ei ? str[si]+" " : " ";
    }

    if(str[si] == str[ei]){
        return str[si] + longestpalindromesubstring(str , si+1 , ei - 1 , dp) + str[ei]; 
    }else{
        if(dp[si+1][ei] > dp[si][ei - 1]){
            return longestpalindromesubstring(str, si + 1, ei, dp);
        }else
           return  longestpalindromesubstring(str, si, ei - 1, dp);
    }
}


void printans()
{
    int SR = 0, SC = 0, ER = 2, EC = 2;
    vector<vector<int>> dp(ER + 1, vector<int>(EC + 1));

    vector<vector<int>> dir = {{1, 0}, {0, 1}};
    // cout << mazEPathmulti_tabu(SR, SC, ER, EC, dp, dir) << endl;
    cout << mazEPath_memo(SR, SC, ER, EC, dp, dir) << endl;
    display2D(dp);
}

int main()
{
    int n , k;
    cin >> n>>k;
    // vector<int> dp(n + 1);
    // cout << fibo_memo(n, dp) << endl;
    // cout << boardGame_memo(0, 10, dp) << endl;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    cout << makepair_02(n,k , dp)<<endl;
        display2D(dp);
        // printans();
        return 0;
}

