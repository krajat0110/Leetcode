#include <iostream>
#include <vector>
using namespace std;

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


//unique path II

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

int boardGame_memo(int SP, int EP, vector<int> &dp){
   if(SP == EP){
    return dp[SP] = 1;
   }

   if(dp[SP] != 0){
       return dp[SP];
   }
   int cnt = 0;
   for(int s = 1 ; s <= 6 && s + SP < EP ; s++){
       cnt += boardGame_memo(SP + s , EP , dp);
   }
   return dp[SP]=cnt;
}

int boardGame_tabu(int SP, int EP, vector<int> &dp)
{
    for(int sp = EP ; sp >= 0 ; sp--){
    if (sp == EP)
    {
        dp[sp] = 1;
        continue;
    }

    int cnt = 0;
    for (int s = 1; s <= 6 && s + SP <= EP; s++)
    {
        cnt += dp[s+sp];
    }
     dp[sp] = cnt;
  }
    return dp[SP];
}

    void printans()
    {
        int SR = 0, SC = 0, ER = 2, EC = 2;
        vector<vector<int>> dp(ER + 1, vector<int>(EC + 1));

        vector<vector<int>> dir = {{1, 0}, {0, 1}, {1, 1}};
        cout << mazEPathmulti_tabu(SR, SC, ER, EC, dp, dir) << endl;
        // cout << mazEPath_memo(SR, SC, ER, EC, dp, dir) << endl;
        display2D(dp);
    }

    int main()
    {
        int n;
        // cin >> n;
        //   vector<int> dp(n + 1);
        //    cout << fibo_memo(n, dp) << endl;
        //   cout << fibo_opti(n) << endl;
        //   display(dp);
        printans();
        return 0;
    }