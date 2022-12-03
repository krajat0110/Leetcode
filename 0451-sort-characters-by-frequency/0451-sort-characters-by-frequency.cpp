class Solution {
public:
     static bool cmp(vector<int>&a , vector<int>&b){
        if(a[0] < b[0]) return true;
        if(a[0] == b[0]){
            return a[1]>b[1];
        }
        return false;
    }
    
        string frequencySort(string nums) {
        vector<vector<int>>v;
        unordered_map<int,int>map;
        
        for(auto ele : nums) map[ele]++;
        
        for(auto a : map){
            v.push_back({a.second,a.first});
        }
        sort(v.begin(),v.end(),cmp);
           
        vector<int>ans;
        for(auto a : v){
            int x = a[0];
            while(x--){
            ans.push_back(a[1]);
            }
        }
       reverse(ans.begin(),ans.end()); 
        string res;
        for(int i = 0 ; i < ans.size();i++){
            res +=ans[i];
        }        
            
            return res;
    }
};