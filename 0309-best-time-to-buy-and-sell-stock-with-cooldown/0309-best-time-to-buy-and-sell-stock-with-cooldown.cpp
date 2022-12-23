class Solution {
public:
    int maxProfit(vector<int>& prices) {
          int dpik0 = 0 , dpik1 = -(int)1e9;
        //buy = 1 ,sell = 0;
        int dpi_2k_10 = 0;
        for(int price : prices){  
            int dpik_10 = dpik0;
        dpik0 = max(dpik0 , dpik1 + price);
        dpik1 = max(dpik1 , dpi_2k_10 - price); 
            dpi_2k_10 = dpik_10; 
       }
        return dpik0;
    }
};