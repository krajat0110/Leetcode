class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(),costs.end());
        int ans = 0;
        for(int i = 0 ; i < costs.size();i++){
           // cout<<costs[i]<<" ";
            if(costs[i] <= coins){
                ans++;
                coins-=costs[i];
             //   cout<<ans<<" "<<coins<<endl;
            }
        }
        return ans;
    }
};