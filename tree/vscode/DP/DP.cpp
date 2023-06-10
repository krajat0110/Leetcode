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

int fibo(int n, vector<int> &dp){
    if(n<=1){
        return dp[n] = n;
    }

    if(dp[n]!= 0) return dp[n];

    int ans = fibo (n - 1,dp) + fibo(n - 2 , dp);
    return dp[n] = ans;
}

int fibtabu(int N)
{
    int dp[N + 1];
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }
        int ans = dp[n - 1] + dp[n - 2];
        dp[n] = ans;
    }

    return dp[N];
}

// climbing stairs Leetcode
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

int mazePath_memo(int sr, int sc, int er, int ec,vector<vector<int>> &dp, vector<vector<int>> &dir)
{
    if (er == sr && ec == sc)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
    {
        return dp[sr][sc];
    }

    int count = 0;
    for (auto d : dir)
    {
        int r = sr + d[0], c = sc + d[1];
        if (r >= 0 && c >= 0 && r < dp.size() && c < dp[0].size())
        {
            count += mazePath_memo(r, c, er, ec, dp, dir);
        }
    }
    return dp[sr][sc] = count;
}



int mazePath_tabu(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
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
            int count = 0;
            for (auto d : dir)
            {
                int r = sr + d[0], c = sc + d[1];
                if (r >= 0 && c >= 0 && r < dp.size() && c < dp[0].size())
                {
                    count += dp[r][c];
                }
            }
            dp[sr][sc] = count;
        }
    }
    return dp[SR][SC];
}

int mazepathmulti_tabu(int SR, int SC, int ER, int EC, vector<vector<int>> &dp, vector<vector<int>> &dir)
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
            int count = 0;
            for (auto d : dir)
            {
                int r = sr + d[0];
                int c = sc + d[1];
                while (r >= 0 && c >= 0 && r < dp.size() && c < dp[0].size())
                {
                    count += dp[r][c];
                    r += d[0];
                    c += d[1];
                }
            }
            dp[sr][sc] = count;
        }
    }
    return dp[SR][SC];
}


int boardGame_memo(int sp, int ep, vector<int> &dp)
{
    if (sp == ep)
    {
        return dp[sp] = 1;
    }
    if (dp[sp] != 0)
        return dp[sp];

    int count = 0;
    for (int s = 1; s <= 6 && s + sp <= ep; s++)
    {
        count += boardGame_memo(sp + s, ep, dp);
    }
    return dp[sp] = count;
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
        int count = 0;
        for (int dice = 1; dice <= 6 && dice + sp <= EP; dice++)
        {
            count += dp[sp + dice]; //boardGame_tabu(sp + dice, ep, dp);
        }
        dp[sp] = count;
    }
    return dp[SP];
}

//leetcode 91   
//memoization function
class Solution
{
public:
    int numDecodings1(string s, int idx, vector<int> &dp)
    {
        if (idx == s.length())
        {
            return dp[idx] = 1;
        }
        if (dp[idx] != -1)
        {
            return dp[idx];
        }
        char ch = s[idx];
        if (ch == '0')
        {
            return dp[idx] = 0;
        }
        int count = numDecodings1(s, idx + 1, dp);
        if (idx < s.length() - 1)
        {
            char ch1 = s[idx + 1];
            int num = (ch - '0') * 10 + (ch1 - '0');
            if (num <= 26)
            {
                count += numDecodings1(s, idx + 2, dp);
            }
        }
        return dp[idx] = count;
    }

    int numDecodings(string s)
    {
        int n = s.length();
        vector<int> dp(n + 1, -1);
        return numDecodings1(s, 0, dp);
    }
};

//tabulation function
int numDecodings1(string s, int IDX, vector<int> &dp)
{

    for (int idx = s.length(); idx >= 0; idx--)
    {
        if (idx == s.length())
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
        int count = dp[idx + 1]; //numDecodings1(s, idx + 1, dp);
        if (idx < s.length() - 1)
        {
            char ch1 = s[idx + 1];
            int num = (ch - '0') * 10 + (ch1 - '0');
            if (num <= 26)
            {
                count += dp[idx + 2]; //numDecodings1(s, idx + 2, dp);
            }
        }
        dp[idx] = count;
    }
    return dp[IDX];
}

//leetcode decode ways 2 

class Solution {
public:
     long mod = (int)1e9 + 7;
    virtual long long numDecodings1(string &s , int idx , vector<long long> &dp){
        int n = s.length();
        if(idx == n){
            return dp[idx]=1;
        }
        if(dp[idx] != -1 ){
            return dp[idx];
        }
        char ch = s[idx];
        if(ch == '0'){
            return dp[idx] = 0;
        }
        long long count = 0;
        if(ch == '*'){
           count = (count + 9 * numDecodings1(s , idx + 1 , dp)) % mod; //* cam be represented in 9 ways
            if(idx < n - 1){
            char ch1 = s[idx + 1];
             if(ch1 >= '0' && ch1 <= '6'){
                 count = (count + 2 * numDecodings1(s , idx + 2 , dp)) % mod; //26 se bada ho jaega wo no banega he nahi
             }
             else if(ch1 >= '7' && ch1 <='9') { 
                 count = (count + 1 * numDecodings1(s , idx + 2 , dp)) % mod; //only one way he 
             }
                else {
                    count = (count + 15 * numDecodings1(s , idx + 2 , dp )) % mod; //next wla bhi star he 
                }
        }      
    }else{
         count += 1 * numDecodings1(s , idx + 1 , dp) % mod;
            if(idx < n - 1){
                char ch1 = s[idx + 1];
                if(ch1 == '*'&& ch == '1' ) count = (count + 9 * numDecodings1(s , idx + 2 , dp)) % mod;
                else if(ch1 == '*'&& ch == '2') count = (count + 6 * numDecodings1(s , idx + 2 , dp)) % mod;
                else if(ch1 != '*'){
                    int num = (ch -'0')*10 + (ch1 - '0');
                    if(num <=26)
                    count = (count + 1 * numDecodings1(s , idx + 2 , dp)) % mod;
                }
            }
        }
        return dp[idx] = count;
    }  
    
    int numDecodings(string s) {
        int n = s.length();
        vector<long long >dp(n + 1 , -1);
       long long ans =  numDecodings1(s , 0 , dp);
        return (int)ans;
    }
};

//leetcode goldmine
class Solution{
public:

   int maxGold1(int sr , int sc ,vector<vector<int>> &arr , vector<vector<int>>&dp , vector<vector<int>>&dis){
     int n = arr.size(), m = arr[0].size();
       if(sc == m - 1 ){
           return dp[sr][sc]=arr[sr][sc];
       }
       if(dp[sr][sc] != -1){
           return dp[sr][sc];
       }
       int maxgold = 0;
       for(auto d : dis){
           int r = sr + d[0];
           int c = sc + d[1];
           
           if(r >= 0 && c >= 0 && r < n && c < m){
               maxgold = max(maxgold , maxGold1(r , c , arr ,dp ,dis) + arr[sr][sc]);
           }
       }
        return dp[sr][sc] = maxgold;
   }
   
    int maxGold(int n, int m, vector<vector<int>> arr)
    {
        vector<vector<int>>dp(n,vector<int>(m));
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
         dp[i][j] = -1;
    }
}
         vector<vector<int>> dis = {{0, 1}, {1, 1}, {-1, 1}};
         int maxGold = 0;
         for(int i = 0 ; i < n ; i++){
         maxGold = max(maxGold,maxGold1( i , 0 , arr , dp , dis));
         }
        return maxGold;
    }
};

void printans()
{
    int sr = 0, sc = 0, er = 3, ec = 3;
    vector<vector<int>> dp(er + 1, vector<int>(ec + 1));

    vector<vector<int>> dir = {{1, 0}, {0, 1}, {1, 1}};
    cout << mazepathmulti_tabu(sr, sc, er, ec, dp, dir) << endl;
    display2D(dp);
}

int main()
{
    int n;
    cin>>n;
    vector<int> dp(n + 1);
    cout<<fibo(n , dp)<<endl;
    printans();
    return 0;
}