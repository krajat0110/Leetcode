#include <iostream>
#include <vector>
#include <string>
using namespace std;

int col=0;
int dig=0;
int antidig=0;

int nQueen_bitmasking(int n, int m , int tnq , int r , string ans){
    if (tnq == 0 || r == n){
        if(tnq == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    for(int c = 0 ; c < m; c++ ){

        if((col & ( 1 << c)) == 0 && (dig & (1 << (r + c ))) == 0 && (antidig & (1 << (r - c + m - 1))) == 0){

            col ^= (1 << c);
            dig ^= (1 << (r + c ));
            antidig ^= (1 << (r - c + m -1 ));

           count+=nQueen_bitmasking(n , m ,tnq - 1 , r + 1 , ans + "(" + to_string(r) + "," + to_string(c) + ")");

            col ^= (1 << c);
            dig ^= (1 << (r + c));
            antidig ^= (1 << (r - c + m - 1));
        }
    }
    return count;
}

void nQueen()
{
    int n = 4 , m = 4 , tnq = 4;

    cout << nQueen_bitmasking(n, m, tnq, 0, "") << endl;
}

int main(){
    // int n=5;
    // for(int i=0;i<n;i++){
    //     cout<<(n<<i)<<endl;
    // }
    // cout<<"++++++++++++++++++++++++++++"<<endl;
    // int q = 80;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << (q >> i) << endl;
    // }
    nQueen();
    return 0;
}