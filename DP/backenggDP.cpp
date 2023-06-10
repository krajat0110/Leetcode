#include <bits/stdc++.h>
#include <vector>
using namespace std;
long mod = (int)1e9 + 7;

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

void goldminebackengg(vector<vector<int>> &dp, vector<vector<int>> dir, int sr, int sc, string psf)
{

    if (sc = dp.size())
    {
        cout << " ( " << to_string(sr) << " , " << to_string(sc) << " )" << endl;
        return;
    }

    int maxgold = 0, idx = -1;
    for (int d = 0; d < dir.size(); d++)
    {
        int s = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (s >= 0 && c >= 0 && s < dp.size() && c < dp[0].size() && dp[s][c] > maxgold)
        {
            maxgold = dp[s][c];
            idx = d;
        }
    }

    if (idx != -1)
    {
        int s = sr + dir[idx][0], c = sc + dir[idx][1];
        goldminebackengg(dp, dir, s, c, psf + " ( " + to_string(s) + " , " + to_string(c) + " )");
    }
}
int maxGold(int n, int m, vector<vector<int>> &M)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    vector<vector<int>> dis = {{0, 1}, {1, 1}, {-1, 1}};

    int maxgold = 0;
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        int ans = goldsum(i, 0, M, dis, dp);
        if (ans > maxgold)
        {
            ans = maxgold;
            idx = i;
        }
    }
    return maxgold;
}

// word break
bool wordBreak(string s, vector<string> &dic)
{
    int n = s.size();
    unordered_set<string> map;
    int len = -(int)1e9;
    for (string ele : dic)
    {
        map.insert(ele);
        int val = ele.size();
        len = max(val, len);
    }

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 0; i <= n; i++)
    {
        if (!dp[i])
            continue;

        for (int l = 1; l <= len && i + l <= n; l++)
        {
            string val = s.substr(i, l);
            if (map.find(val) != map.end())
            {
                dp[i + l] = true;
            }
        }
    }
    return dp[n];
}

// word break 2

void wordBreak_backEngg(string &s, int idx, vector<bool> &dp, int maxLen, vector<string> &wordDict, unordered_set<string> &set, string ssf, vector<string> &ans)
{
    if (idx >= s.length())
    {
        ans.push_back(ssf.substr(0, ssf.length() - 1));
        return;
    }

    for (int l = 1; l <= maxLen && idx + l <= s.length(); l++)
    {
        if (dp[idx + l])
        {
            string substr = s.substr(idx, l);
            if (set.find(substr) != set.end())
            {
                wordBreak_backEngg(s, idx + l, dp, maxLen, wordDict, set, ssf + substr + " ", ans);
            }
        }
    }
}

vector<string> wordBreak(string &s, vector<string> &wordDict)
{
    unordered_set<string> set;
    int len = 0, n = s.length();
    for (string ss : wordDict)
    {
        set.insert(ss);
        int val = ss.size();
        len = max(val, len);
    }

    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 0; i <= n; i++)
    {
        if (!dp[i])
        {
            continue;
        }

        for (int l = 1; l <= len && i + l <= n; l++)
        {
            string substr = s.substr(i, l);
            if (set.find(substr) != set.end())
            {
                dp[i + l] = true;
            }
        }
    }

    vector<string> ans;
    if (dp[n])
    {
        wordBreak_backEngg(s, 0, dp, len, wordDict, set, "", ans);
    }

    return ans;
}

// leetcode 300 longest increasing sequence
// memoization
int LIS(vector<int> &nums, int ei, vector<int> &dp)
{
    int n = nums.size();
    if (dp[ei] != 0)
        return dp[ei];
    int maxlen = 1;
    for (int i = ei - 1; i >= 0; i--)
    {
        if (nums[ei] > nums[i])
        {
            maxlen = max(maxlen, LIS(nums, i, dp) + 1);
        }
    }
    return dp[ei] = maxlen;
}

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size(), maxlen = -1e9;
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        maxlen = max(maxlen, LIS(nums, i, dp));
    }
    return maxlen;
}

int lengthOfLIS_01(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LIS01(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 0);
    return lengthOfLIS_01(nums, dp);
}

// longest decresing subsequence and idx given represent the value of no on which the lis is ending

// 1 , 3 ,12 , 4 , 7, 8 ,10 , 1 , 6 so longest lds ending which 6 is [12 , 10 , 6]

int lengthOfLDS_01(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] < nums[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LIS01(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 0);
    return lengthOfLDS_01(nums, dp);
}

// Longest Bitonic subsequence

int LIS_LR(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LIS_RL(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LongestBitonicSequence(vector<int> nums)
{
    int n = nums.size(), maxLen = 0;
    vector<int> LIS(n, 0);
    vector<int> LDS(n, 0);

    LIS_LR(nums, LIS);
    LIS_RL(nums, LDS);

    for (int i = 0; i < n; i++)
    {
        maxLen = max(maxLen, LIS[i] + LDS[i] - 1);
    }

    return maxLen;
}

// longest reverse botonic sequence

int LIS_RL(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LDS_RL(vector<int> &nums, vector<int> &dp)
{
    int n = nums.size(), maxlen = -1e9;

    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] < nums[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int LongestBitonicSequence(vector<int> nums)
{
    int n = nums.size(), maxLen = 0;
    vector<int> LIS(n, 0);
    vector<int> LDS(n, 0);

    LIS_LR(nums, LIS);
    LDS_RL(nums, LDS);

    for (int i = 0; i < n; i++)
    {
        maxLen = max(maxLen, LIS[i] + LDS[i] - 1);
    }
    return maxLen;
}

// Maximum sum increasing subsequence
int maxSumIS(int nums[], int n)
{
    vector<int> dp(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = nums[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j] + nums[i]);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// Maximum Sum Bitonic Subsequence
int maxSumBS(int nums[], int n)
{
    vector<int> LIS(n, 0);
    vector<int> LDS(n, 0);

    for (int i = 0; i < n; i++)
    {
        LIS[i] = nums[i];
        int mx = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                mx = max(mx, LIS[j]);
            }
        }
        LIS[i] += mx;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        LDS[i] = nums[i];
        int mx = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] > nums[j])
            {
                mx = max(mx, LDS[j]);
            }
        }
        LDS[i] += mx;
    }

    int maxLen = -1e9;
    for (int i = 0; i < n; i++)
    {
        maxLen = max(maxLen, LIS[i] + LDS[i] - nums[i]);
    }

    return maxLen;
}

// minimun deletion required to make array sorted

int minDeletions(int nums[], int n)
{
    int maxlen = -1e9;
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return n - maxlen;
}
// 673. Number of Longest Increasing Subsequence

int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size(), maxcnt = 0, maxlen = 0;
    vector<int> dp(n, 0);
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        cnt[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (dp[i] == dp[j] + 1)
                    cnt[i] += cnt[j];
            }
        }
        if (dp[i] > maxlen)
        {
            maxlen = dp[i];
            maxcnt = cnt[i];
        }
        else if (dp[i] == maxlen)
        {
            maxcnt += cnt[i];
        }
    }
    return maxcnt;
}

// Building Bridges

int maxBridges(vector<vector<int>> nums)
{
    sort(nums[1].begin(), nums[1].end());
    int n = nums.size(), maxlen = -1e9;
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i][0] >= nums[j][0] && nums[i][1] > nums[j][1]) //[1] idx is already sorted
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

//leetcode 354 n2 gives tle 
int maxEnvelopes(vector<vector<int>> &nums)
{
    sort(nums.begin(), nums.end());
    int n = nums.size(), maxlen = -1e9;
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i][0] > nums[j][0] && nums[i][1] > nums[j][1]) //[1] idx is already sorted
                dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(dp[i], maxlen);
    }
    return maxlen;
}

int main()
{
}