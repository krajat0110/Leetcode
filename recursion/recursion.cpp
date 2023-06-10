#include <iostream>
#include <vector>
#include <string>
using namespace std;

//only ans;
vector<string> subSeq(string str, int idx)
{
    if (idx == str.length())
    {
        vector<string> base;
        base.push_back("");
        return base;
    }
    vector<string> recAns = subSeq(str, idx + 1);
    vector<string> myAns(recAns);
    for (string s : recAns)
        myAns.push_back(str[idx] + s);

    return myAns;
}
//ans + count
int subseq(string str, int idx, string ans, vector<string> res)
{
    if (idx == str.size())
    {
        res.push_back(ans);
        return 1;
    }

    int count = 0;
    count += subseq(str, idx + 1, ans + str[idx], res);
    count += subseq(str, idx + 1, ans, res);

    return count;
}

// top to bottomPP
vector<string> mazePath_HVD(int sr, int sc, int er, int ec)
{
    // cout<<"TEST"<<endl;
    if (sr == er && sc == ec)
    {
        vector<string> base;
        base.push_back("");
        //  cout<<"in base"<<endl;
        return base;
    }
    vector<string> ans;
    if (sr + 1 <= er) //is next step is valid
    {
        vector<string> vertical = mazePath_HVD(sr + 1, sc, er, ec); //r1 ke neeche r2 to r1 +1 = r2 neeche jana padega downward direction
        for (auto s : vertical)
        {
            // cout<< s<<endl;
            ans.push_back("V" + s);
        }
    }
    if (sc + 1 <= ec && sr + 1 <= er) // is next step valid checking both bcz we are moving in diagonal direction
    {
        vector<string> diagonal = mazePath_HVD(sr + 1, sc + 1, er, ec);
        for (auto s : diagonal)
        {
            ans.push_back("D" + s);
        }
    }
    if (sc + 1 <= ec) //is next step valid
    {
        vector<string> horizontal = mazePath_HVD(sr, sc + 1, er, ec); //c1 ke neeche c2 to c1 +1 = c2 neeche jana padega  toward right direction
        for (auto s : horizontal)
        {
            ans.push_back("H" + s);
        }
    }
    return ans;
}

//bottom to top with path
int mazePath_HVD_1(int sr, int sc, int er, int ec, vector<string> &ans, string psf)
{
    if (sc == ec && sr == er)
    {
        ans.push_back(psf);
        return 1;
    }

    int count = 0;
    if (sr + 1 <= er)
        count += mazePath_HVD_1(sr + 1, sc, er, ec, ans, psf + "V");
    if (sr + 1 <= er && sc + 1 <= ec)
        count += mazePath_HVD_1(sr + 1, sc + 1, er, ec, ans, psf + "D");
    if (sc + 1 <= ec)
        count += mazePath_HVD_1(sr, sc + 1, er, ec, ans, psf + "H");
    return count;
}

vector<string> mazePath_HVD_multi(int sr, int sc, int er, int ec)
{
    if (sc == ec && sr == sc)
    {
        vector<string> base;
        base.push_back("");
        return base;
    }
    vector<string> ans;
    for (int j = 1; sr + j <= er; j++) //j=jump
    {
        vector<string> vertical = mazePath_HVD_multi(sr + 1, sc, er, ec);
        for (auto s : vertical)
            ans.push_back(string(1, 'V') + to_string(j) + s);
    }
    for (int j = 1; sc + j <= ec && sr + j <= er; j++)
    {
        vector<string> diagonal = mazePath_HVD_multi(sr + 1, sc + 1, er, ec);
        for (auto s : diagonal)
            ans.push_back(string(1, 'D') + to_string(j) + s);
    }
    for (int j = 1; sc + j <= ec; j++)
    {
        vector<string> horizontal = mazePath_HVD_multi(sr, sc + 1, er, ec);
        for (auto s : horizontal)
            ans.push_back(string(1, 'H') + to_string(j) + s);
    }
    return ans;
}

int mazePath_HVD_multi1(int sr, int sc, int er, int ec, vector<string> &ans1, string psf)
{
    if (sr == er && sc == er)
    {
        ans1.push_back(psf);
        return 1;
    }
    int count = 0;
    for (int j = 1; sr + j <= er; j++)
        count += mazePath_HVD_multi1(sr + 1, sc, er, ec, ans1, psf + to_string(j) + "V");
    for (int j = 1; sr + j <= er && sc + j <= ec; j++)
        count += mazePath_HVD_multi1(sr + 1, sc + 1, er, ec, ans1, psf + to_string(j) + "D");
    for (int j = 1; sc + j <= ec; j++)
        count += mazePath_HVD_multi1(sr, sc + 1, er, ec, ans1, psf + to_string(j) + "H");

    // cout<<"/";
    return count;
}

int maze_path2(int sr, int sc, int er, int ec, vector<vector<int>> dir, vector<string> dirS, vector<string> &ans, string psf)
{
    if (sr == er && sc == ec)
    {
        ans.push_back(psf); // ye bas store kar raha he
                            // cout << psf << " ";
        return 1;
    }
    int count = 0;
    for (int d = 0; d < dir.size(); d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (x >= 0 && y >= 0 && x <= er && y <= ec)
            count += maze_path2(x, y, er, ec, dir, dirS, ans, psf + dirS[d]);
    }
    return count;
}

int floodfill(int sr, int sc, vector<vector<int>> &vis, string psf, vector<string> res, vector<vector<int>> &dis, vector<string> dirS)
{
    //meanings == vis = visited,
    int n = vis.size(), m = vis[0].size();
    if (sr == n - 1 && sc == m - 1)
    {
        //vector<string> base;
        cout << psf << " ";
        // res.push_back(psf);
        return 1;
    }

    vis[sr][sc] = 1; // block
    int count = 0;   //cout << "#";
    for (int d = 0; d < dis.size(); d++)
    {
        int r = sr + dis[d][0];
        int c = sc + dis[d][1];
        //cout << r << " " << c << " " << sr << " " << sc << " " << endl;
        if (r >= 0 && c >= 0 && r < n && c < m && vis[r][c] == 0)
        {
            count += floodfill(r, c, vis, psf + dirS[d], res, dis, dirS);
        }
    }
    vis[sr][sc] = 0; // unblock
    return count;
}

int floodfill_multi(int sr, int sc, vector<vector<int>> &vis, string psf, vector<string> res, vector<vector<int>> &dis, vector<string> dirS)
{
    int n = vis.size();
    int m = vis[0].size();
    if (sc == m - 1 && sr == n - 1)
    {
        //res.push_back(psf);
        cout << psf << " ";
        return 1;
    }
    int count = 0;
    vis[sr][sc] = 1;
    for (int d = 0; d < dis.size(); d++)
        for (int rad = 1; rad <= max(n, m); rad++)
        {
            //cout << "@";
            int r = sr + rad * dis[d][0];
            int c = sc + rad * dis[d][1];
            //  cout<<r<<" "<<c<<endl;
            if (r >= 0 && c >= 0 && r < n && c < m)
            {
                if (vis[r][c] == 0)
                    //cout << "*"<<count<<endl;
                    count += floodfill_multi(r, c, vis, psf + dirS[d] + to_string(rad), res, dis, dirS);
                // cout<<"/"<<count<<endl;
            }
            else
                break;
        }
    vis[sr][sc] = 0;
    return count;
}
    class pair_
    {
    public:
        string psf = " ";
        int len = 0;

        pair_(string psf, int len)
        {
            this->psf = psf;
            this->len = len;
        }
};

pair_ longestpath(int sr, int sc, vector<vector<int>> &vis, vector<vector<int>> &dir, vector<string> &dirS)
{
    int n = vis.size(), m = vis[0].size();
    if (sr == n - 1 && sc == m - 1)
    {
        pair_ base("", 0);
        return base;
    }

    vis[sr][sc] = 1; // blocked
    pair_ myAns("", -1);
    for (int d = 0; d < dir.size(); d++)
    {
        int r = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (r >= 0 && c >= 0 && r < n && c < m)
        {
            if (vis[r][c] == 0)
            {
                pair_ recAns = longestpath(r, c, vis, dir, dirS);
                if (recAns.len != -1 && recAns.len + 1 > myAns.len)
                {
                    myAns.len = recAns.len + 1;
                    myAns.psf = dirS[d] + recAns.psf;
                }
            }
        }
    }

    vis[sr][sc] = 0; // unblocked
    return myAns;
}

pair_ shortestpath(int sr, int sc, vector<vector<int>> &vis, vector<vector<int>> &dir, vector<string> &dirS)
{
    int n = vis.size(), m = vis[0].size();
    if (sr == n - 1 && sc == m - 1)
    {
        pair_ base("", 0);
        return base;
    }

    vis[sr][sc] = 1; // blocked
    pair_ myAns("", (int)1e9);
    for (int d = 0; d < dir.size(); d++)
    {
        int r = sr + dir[d][0];
        int c = sc + dir[d][1];

        if (r >= 0 && c >= 0 && r < n && c < m)
        {
            if (vis[r][c] == 0)
            {
                pair_ recAns = shortestpath(r, c, vis, dir, dirS);
                if (recAns.len != (int)1e9 && recAns.len + 1 < myAns.len)
                {
                    myAns.len = recAns.len + 1;
                    myAns.psf = dirS[d] + recAns.psf;
                }
            }
        }
    }
    vis[sr][sc] = 0; // unblocked
    return myAns;
}

void l_path()
{
    vector<vector<int>> dis = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<string> dirS = {"D", "R", "U", "L"};
    int row = 3, col = 3;
    vector<vector<int>> vis(row, vector<int>(col));

    // pair_ ans1=longestpath(0,0,vis,dis,dirS);

    pair_ ans1 = shortestpath(0, 0, vis, dis, dirS);
    cout << ans1.psf << "@" << ans1.len << endl;
}

void mazePath()
{
    int sr = 0, sc = 0, er = 2, ec = 2;
    vector<string> ans1;
    //  int dir[][]= {{1,0},{0,1},{1,1}};
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}};
    vector<string> dirS = {"V", "H", "D", "E"};
    int ans = maze_path2(sr, sc, er, ec, dir, dirS, ans1, "");
    // vector<string> ans= mazePath_HVD(sr, sc, er, ec);
    //auto ans= maze_path2(sr, sc, er, ec,dir,dirS,ans1,"");

    // for (auto s : ans)
    // {
    //     cout<<s<<endl;
    // }
    cout << ans;
}
void floodfill_1()
{
    int sr = 0, sc = 0, n = 3, m = 3;
    vector<vector<int>> vis(n, vector<int>(m));
    vector<string> res;
    vector<vector<int>> dis = {{1, 0}, {0, 1}, {1, 1}};
    vector<string> dirS = {"V", "H", "D"};
    vector<vector<int>> &ans
        //vector<vector<int>> dis = {{1, 0}, {0,1}, {1, 1}, {-1, -1}};
        //  vector<string> dirS = {"V", "H", "D", "E"};

        // int ans = floodfill(sr, sc, vis, " ", res, dis, dirS);
        int ans1 = ratmultijump(sr, sc, vis, dis, ans)
        cout<< ans1;
}

int main()
{
    //mazePath();
    floodfill_1();
    //l_path();
    return 0;

    //maximun of m,n use kara he in case of rectangle 
    
}