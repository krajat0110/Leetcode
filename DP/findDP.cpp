#include <bits/stdc++.h>
#include <vector>
using namespace std;
long mod = (int)1e9 + 7;

// infinite coin permutation
int permutation(vector<int> &coins, int tar, vector<int> &dp)
{
    int n = coins.size();
    if (tar == 0)
        return dp[tar] = 1;

    if (dp[tar] != -1)
        return dp[tar];

    int cnt = 0;
    for (int ele : coins)
    {
        if (tar - ele >= 0)
            cnt += permutation(coins, tar - ele, dp);
    }
    return dp[tar] = cnt;
}

// premutation tabu
// https://leetcode.com/problems/combination-sum-iv/
int combinationSum4(vector<int> &nums, int Tar)
{
    int n = nums.size();
    vector<long> dp(Tar + 1, -1);
    dp[0] = 1;
    for (int tar = 1; tar <= Tar; tar++)
    {
        int cnt = 0;
        for (int ele : nums)
        {
            if (tar - ele >= 0)
                cnt += dp[tar - ele];
            dp[tar] = cnt;
        }
    }
    return dp[Tar];
}

// combination memoization
int combination(vector<int> &coins, int n, int tar, vector<vector<int>> &dp)
{
    int n = coins.size();
    if (tar == 0)
        return dp[n][tar] = 1;

    if (dp[n][tar] != -1)
        return dp[n][tar];

    int cnt = 0;
    for (int i = n; i > 0; i--)
    {
        if (tar - coins[i - 1] >= 0)
            cnt += combination(coins, i - 1, tar - coins[i - 1], dp);
    }
    return dp[n][tar] = cnt;
}

int combination_tabu(vector<int> &coins, int Tar, vector<int> &dp) // don't fill DP with -1 ele
{
    dp[0] = 1;
    for (auto ele : coins)
    {
        for (int tar = ele; tar <= Tar; tar++)
        {
            if (tar - ele >= 0)
                dp[tar] += dp[tar - ele];
        }
    }
    return dp[Tar];
}

// https://leetcode.com/problems/coin-change/
int coinChange(vector<int> &nums, int Tar)
{
    int n = nums.size();
    vector<long> dp(Tar + 1, 1e9);
    dp[0] = 0;
    for (int tar = 1; tar <= Tar; tar++)
    {
        for (int ele : nums)
        {
            if (tar - ele >= 0)
                dp[tar] = min(dp[tar - ele] + 1, dp[tar]);
        }
    }
    return dp[Tar] != 1e9 ? dp[Tar] : -1;
}

// for back engg we have to use tabulation because we can't visit all the states using memoization

// Subset Sum Problem
// -1 : not explored, 0 : false, 1 : true
int isequal(vector<int> &arr, int n, int tar, vector<vector<long long>> &dp) // targetsum
{
    if (n == 0 || tar == 0)
    {
        return dp[n][tar] = (tar == 0 ? 1 : 0);
    }

    if (dp[n][tar] != -1)
        return dp[n][tar];

    bool res = false;
    if (tar - arr[n - 1] >= 0)
        res = res || isequal(arr, n - 1, tar - arr[n - 1], dp) == 1;
    res = res || isequal(arr, n - 1, tar, dp) == 1;

    return dp[n][tar] = res ? 1 : 0;
}

// subsetsum tabulation
bool isequal_tabu(vector<int> &arr, int N, int Tar, vector<vector<bool>> &dp) // targetsum
{
    for (int n = 0; n <= N; n++)
    {
        for (int tar = 0; tar <= Tar; tar++)
        {
            if (n == 0 || tar == 0)
            {
               dp[n][tar] = (tar == 0);
               continue;
            }

            // if (dp[n][tar] != -1)
            //     return dp[n][tar];

            bool res = false;
            if (tar - arr[n - 1] >= 0)
                dp[n][tar] = dp[n][tar] || dp[n - 1][tar - arr[n - 1]];
            dp[n][tar] = dp[n][tar] || dp[n - 1][tar];
        }
    }
    return dp[N][Tar];
}

bool isSubsetSum(vector<int> arr, int tar)
{
    int n = arr.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(tar + 1, -1));
    int ans = isequal(arr, n, tar, dp);
    return ans == 1;
}

// 0 - 1 Knapsack Problem

int isequal(int w, int wt[], int val[], int n, vector<vector<int>> &dp)
{

    if (n == 0 || w == 0)
        return dp[n][w] = 0;

    if (dp[n][w] != -1)
        return dp[n][w];

    int maxans = 0;
    if (w - wt[n - 1] >= 0)
        maxans = max(maxans, isequal(w - wt[n - 1], wt, val, n - 1, dp) + val[n - 1]);
    maxans = max(maxans, isequal(w, wt, val, n - 1, dp));

    return dp[n][w] = maxans;
}

int knapSack(int W, int wt[], int val[], int n)
{
    vector<vector<int>> dp(n, vector<int>(W, -1));
    return isequal(W, wt, val, n, dp);
}

// knapsackpath back engg

int target(vector<int> arr, int n, vector<vector<int>> &dp, int tar, string psf)
{
    if (n == 0 || tar == 0)
    {
        if (tar == 0)
        {
            cout << psf;
            return 1;
        }
        return 0;
    }
    int count = 0;
    if (tar - arr[n - 1] >= 0 && dp[n - 1][tar - arr[n - 1]] == 1)
        count += target(arr, n - 1, dp, tar - arr[n - 1], psf + to_string(arr[n - 1]) + " ");
    if (dp[n - 1][tar] == 1)
    {
        count += target(arr, n - 1, dp, tar, psf + " ");
    }
    return count;
}

int main()
{
}
