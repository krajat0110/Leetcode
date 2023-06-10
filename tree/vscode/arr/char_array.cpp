#include<iostream>
#include<cstring>
using namespace std;


 int length(char a[]){
     int count=0;
     for(int i=0 ;a[i]!='\0';i++){
         count++;
     }
     return count;
 }
/*
bool palindrome(char a[]){
    int len=strlen(a);
    int i=0,j=len-1;
    while(i<j){
    if(a[i]!=a[j]){
    return false;
    }  
    i++, j--;
   }
    return true;
}
*/
/*
int reverse(char a[ ]){
   int temp,len= length(a);
     int i=0,j=len-1;
      while(i<j){
       temp= a[i];
       a[i]= a[j];
       a[j]=temp;
       i++;
       j--;
       }
  }
  */
 /*
 int replace(char a[], char c1, char c2){
     char len = length
(a);
     for (int i=0;i<len;i++){
         if(c1==a[i]){
            a[i]=c2;
         }
     }
     return 0;
 }            
*/
/*
void cutter(char a[]){
    char len = length(a);
    int i=0,j=0;
    while (a[i]){
        if(a[i] != ' '){
            a[j++] = a[i];    
        }
        i++;
    }
    a[j+1]='\0';
}
*/
/*
void reversestring(char a[],int start,int end){
    int temp=0,len=length(a);
    int i=start,j=end;
    while(i<=j){
        temp=a[i];
        a[i]=a[j];
        a[j]=temp;
        i++;
        j--;
    }
}

void reverseword(char a[]){
    int i=0,len=length(a);
    int start=0,end=0;
    reversestring(a, 0, len - 1);
    while(a[i]!= '\0'){
        if(a[i]== ' '){
            end = i-1;
            reversestring(a,start,end);
            start = end+2;
        }
        i++;
    }
    reversestring(a, start,len-1);
}
*/
void substring(char a[]){
int len=length(a);
for(int i=1;i<=len;i++){
   for(int j=0;j<=len-i;j++){
       int x=j+i-1;
       for(int z=j;z<=x;z++){
           cout<<a[z]; 
       }     
        cout<<endl;
    }
  }
}
/*
 int error(char a[]){
    int l=strlen(a);
    if(l==0 or l==1){
        return 1 ;
    }
    int prev = 0;
    for(int current=1;current<l;current++){
        if(a[current]  != a[prev]){
            prev++;
            a[prev] = a[current];
        }
    }
        a[prev+1]=  '\0';
        return 0;
 }
 */

int main(){

    char a[100];
    cin.getline(a,100);
    //char c2,c1;
   //cin>>c1>>c2;
    cout<<endl;
    substring(a);
    
}

#include <cstring>
class Solution
{
public:
    string largestMerge(string word1, string word2)
    {
        //  string=merge;

        int j = 0;
        int i = 0;
        while (i <= word1 && j <= word2)
        {
            if (word1[i] < word[j])
            {
                merge = word[i];
                i++;
            }
            if (word1[j] < word[i])
            {
                merge = word[j];
                j++;
            }
            if (word1[i] == word[j])
            {
                merge = word[i];
                i++;
            }
        }
        return merge;
    }
};