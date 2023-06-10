#include <iostream>
#include <vector>
#include <string>

using namespace std;

int equalset(vector<int> &arr, int idx, int sum1, int sum2, string set1, string set2)
{
    if (idx == arr.size())
    {
        if (sum1 == sum2)
        {
            // cout<<"k";
            for (auto ele1 : set1)
                cout << ele1;
            cout << "=";
            for (auto ele2 : set2)
                cout << ele2;
            cout << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    count += equalset(arr, idx + 1, sum1 + arr[idx], sum2, set1 + to_string(arr[idx]) + " ", set2);
    count += equalset(arr, idx + 1, sum1, sum2 + arr[idx], set1, set2 + to_string(arr[idx]) + " ");

    return count;
}

int permutation(string str,string ans){

    if(str.length()==0){
        cout<<ans<<endl;
        return 1;
    }
    int count=0;
    for(int i=0;i<str.length();i++){
    char ch = str[i];
    string ros=str.substr(0,i)+str.substr(i+1);
    count+=permutation(ros,ans+ch);
    }
    return count;
}


int permutation1(string str,string ans){
    if(str.length()==0){
        cout<<ans<<endl;
        return 1;
    }

     vector<bool> vis(26,false);
    int count=0;
    for(int i=0;i<str.length();i++){
        char ch=str[i];
        if(!vis[ch-'a']){
        //ros=rest of string
        vis[ch-'a']= true;
        string ros = str.substr(0,i)+str.substr(i+1);
        count+=permutation1(ros,ch+ans);
        }
    }
    return count;
}

int permutation2(string str,string ans){
    if(str.length()==0){
        cout<<ans<<endl;
        return 1;
    }
 // this code will give only unique output but inout should be sorted
    int count=0;
    char prev='$';
    for(int i=0;i<str.length();i++){
        char ch=str[i];
        if(prev!=ch){
            string ros= str.substr(0,i)+str.substr(i+1);
            count+=permutation2(ros,ch+ans);
        }
        prev=ch;
    }
    return count;
}

void setsol()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80};

    int ans = equalset(arr, 1, arr[0], 0, to_string(arr[0]) + " ", " ");
    cout << ans;
}

void permutation_sol(){
 
    string str="aaab";
    
    //int ans1 = permutation(str,"");
    //int ans1 = permutation1(str, "");
    cout<<permutation2(str, "");
}

int main()
{
   // setsol();
   permutation_sol();
    return 0;
}