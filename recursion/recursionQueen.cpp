#include <iostream>
#include <vector>

using namespace std;

//tnb=total no of box tnq= total no of queen
int queencombination(int tnb, int tnq, int bno, int qno, string ans)
{
    if (qno == tnq)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = bno; i < tnb; i++)
    {
      count += queencombination(tnb, tnq, i + 1, qno + 1, ans + "b" + to_string(i) + "q" + to_string(qno) + " ");
    }
    return count;
}

int queenpermutation(vector<bool> &boxes, int tnq, int bno, int qno, string ans)
{
    if (qno == tnq)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = bno; i < boxes.size(); i++)
    {
        if (!boxes[i])
        {
            boxes[i] = true;
            count += queenpermutation(boxes, tnq, 0, qno + 1, ans + "b" + to_string(i) + "q" + to_string(qno) + " ");
            boxes[i] = false;
        }
    }
    return count;
}

int queencombination2D(vector<vector<bool>> board, int tnq, int bno, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0, n = board.size(), m = board[0].size();
    for (int i = bno; i < m * n; i++)
    {
        int r = i / m; //straight lime me like ke is formula se indexing aa jati he
        int c = i % m;

        count += queencombination2D(board, tnq - 1, i + 1, ans + "(" + to_string(r) + "," + to_string(c) + ") ");
    }
    return count;
}

int queenpermution2D(vector<vector<bool>> board, int tnq, int bno, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0, n = board.size(), m = board[0].size();
    for (int i = bno; i < m * n; i++)
    {
        int r = i / m; //straight lime me like ke is formula se indexing aa jati he
        int c = i % m;
        if (!board[r][c])
        {
            board[r][c] = true;
            count += queenpermution2D(board, tnq - 1, 0, ans + "(" + to_string(r) + "," + to_string(c) + ") ");
            board[r][c] = false;
        }
    }
    return count;
}

//================================================================================================//
// using subsequence method

//================================================================================================//
// n queen

bool issafetoplace(vector<vector<bool>> &board, int row, int col)
{
    vector<vector<int>> dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}; //for combinatin only 4 direction backside
                                                                     //  vector<vector<int>> dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1},{0,1},{1,1},{1,0},{1,-1}};
    int n = board.size(), m = board[0].size();
    for (int d = 0; d < dir.size(); d++)
    {
        for (int rad = 1; rad < board.size(); rad++)
        {

            int r = row + rad * dir[d][0];
            int c = col + rad * dir[d][1];
            if (r >= 0 && c >= 0 && r < n && c < m)
            {
                if (board[r][c])
                    return false;
            }
            else
                break;
        }
    }
    return true;
}

int nqueen_1combination(vector<vector<bool>> &board, int tnq, int idx, string ans)
{

    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0, n = board.size(), m = board[0].size();
    for (int i = idx; i < m * n; i++)
    {
        int r = i / m;
        int c = i % m;
        if (issafetoplace(board, r, c))
        {
            board[r][c] = true;
            count += nqueen_1combination(board, tnq - 1, i + 1, ans + "(" + to_string(r) + "," + to_string(c) + ")");
            board[r][c] = false;
        }
    }
    return count;
}

int nqueen_1permutation(vector<vector<bool>> &board, int tnq, int idx, string ans)
{

    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0, n = board.size(), m = board[0].size();
    for (int i = idx; i < m * n; i++)
    {
        int r = i / m;
        int c = i % m;
        if (issafetoplace(board, r, c) && !board[r][c])
        {
            board[r][c] = true;
            count += nqueen_1permutation(board, tnq - 1, 0, ans + "(" + to_string(r) + "," + to_string(c) + ")");
            board[r][c] = false;
        }
    }
    return count;
}

int nqueen_1combination_sub(vector<vector<bool>> &board, int tnq, int idx, string ans)
{
    int count = 0, n = board.size(), m = board[0].size();

    if (tnq == 0 || idx == m * n)
    { // takki overflow na ho jae idx ki value
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int r = idx / m;
    int c = idx % m;
    if (issafetoplace(board, r, c))
    {
        board[r][c] = true;
        count += nqueen_1combination_sub(board, tnq - 1, idx + 1, ans + "(" + to_string(r) + "," + to_string(c) + ")");
        board[r][c] = false;
    }
    count += nqueen_1combination_sub(board, tnq, idx + 1, ans);

    return count;
}

vector<bool> row;
vector<bool> col;
vector<bool> diagonal;
vector<bool> antidiagonal;

int queencombination_shadow(int n, int m, int tnq, int idx, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = idx; i < m * n; i++)
    {
        int r = i / m;
        int c = i % m;
        if (!row[r] && !col[c] && !diagonal[r + c] && !antidiagonal[r - c + m - 1])
        {
            row[r] = col[c] = diagonal[r + c] = antidiagonal[r - c + m - 1] = true;
            count += queencombination_shadow(n, m, tnq - 1, i + 1, ans + "(" + to_string(r) + "," + to_string(c) + ")");
            row[r] = col[c] = diagonal[r + c] = antidiagonal[r - c + m - 1] = false;
        }
    }
    return count;
}

int queenpermutation_shadow(int n, int m, int tnq, int idx, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = idx; i < m * n; i++)
    {
        int r = i / m;
        int c = i % m;
        if (!row[r] && !col[c] && !diagonal[r + c] && !antidiagonal[r - c + m - 1])
        {
            row[r] = col[c] = diagonal[r + c] = antidiagonal[r - c + m - 1] = true;
            count += queenpermutation_shadow(n, m, tnq - 1, 0, ans + "(" + to_string(r) + "," + to_string(c) + ")");
            row[r] = col[c] = diagonal[r + c] = antidiagonal[r - c + m - 1] = false;
        }
    }
    return count;
}

void queen()
{
    int tnb = 5;
    int tnq = 3;
    string ans = "";
    vector<bool> boxes(5, false);
    vector<vector<bool>> board(4, vector<bool>(4, false));
    cout << queencombination(tnb, tnq, 0, 0, ans);
    //cout<<endl;
    //   cout << queenpermutation(boxes,tnq, 0, 0, ans);
    // cout << queencombination2D(board, 4, 0, ans);
    //cout << queenpermution2D(board, 4, 0, ans);
}

void queen_sub()
{
    int tnb = 5;
    int tnq = 3;
    string ans = "";
    vector<bool> boxes(5, false);
    vector<vector<bool>> board(4, vector<bool>(4, false));
    //  cout << queencombination_sub(tnb, tnq, 0, 0, ans);
    //   cout << queenpermutation_sub(boxes,tnq, 0, 0, ans);
    //   cout << queencombination2D_sub(board, 4, 0, ans);
    // cout << queenpermution2D_sub(board, 4, 0, ans);
}

void nQueen()
{
    int n = 10, m = 10;
    vector<vector<bool>> board(n, vector<bool>(m, false));
    //  cout <<nqueen_1combination(board,4,0," ")<<endl;
    //cout << nqueen_1permutation(board, 4, 0, " ") << endl;
    // cout << nqueen_1combination_sub(board, 4, 0, " ") << endl;
    int tnq=10;
    row.resize(n, false);
    col.resize(m, false);
    diagonal.resize(m + n - 1, false);
    antidiagonal.resize(m + n - 1, false);

    // cout << queencombination_shadow(n,m, 4, 0, " ") << endl;
    //cout << queenpermutation_shadow(n, m, 4, 0, " ") << endl;

    cout << nqueencombi_obtimize(n, m, tnq, 0, "") << endl;
}

int main()
{
    //queen();
    //queen_sub();
    nQueen();
    return 0;
}