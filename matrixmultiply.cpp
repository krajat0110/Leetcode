#include <bits/stdc++.h>
#include <climits>
#include <iostream>
using namespace std;
int mcm(int *q, int m)
{

    n++;
    int m[n][n];
    int i, j, k, L, q;

    for (i = 0; i < m; i++)
    {
        m[i][i] = 0;
    }
    for (L = 2; L < m; L++)
    {

        for (i = 1; i < m - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + q[i - 1] * q[k] * q[j];
                if (q < m[i][j])

                    m[i][j] = q;
            }
        }
    }

    return m[1][m - 1];
}

int main()
{

    int m;
    cin >> m;
    int *q = new int[m];

    for (int i = 0; i <= m; i++)
    {
        cin >> q[i];
    }

    cout << mcm(q, m);
}