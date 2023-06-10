#include<iostream>
using namespace std;

 int doorleft(int n){

    int door[101];
    for(int i=1;i<=100;i++){
         door[i]=0;
    }

   for (int i=2; i<=n; i++){
       for(int j =i; j<=n; j=j+i){

       if(door[j] == 0){
          door[j]=1;
      }
      else{
          door[j]=0;
         }
     }
   }

   int count=0;

   for(int i=1;i<=n;i++){
       if(door[i]  == 0){
           count=count +1;
           cout<<i<<"  ";
       }
       else{
           continue;
       }
   }
   cout<<endl;
  return count ;
}

int main(){

/*
int n;
cout<<"enter the no round ";
cin>>n;
*/

  cout<<doorleft(100);

}
