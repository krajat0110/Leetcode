class Solution {
public:
  int evalRPN(vector<string>& tokens) {
    vector <long long> st;
    int k = -2, j = -1;
    
    for(auto i : tokens)
      if(i.size() > 1 || i[0] > '/') {st.push_back(stoi(i));k++,j++;}
      else 
        switch(i[0]){
          case '+':
            st[k--] += st[j--]; st.pop_back();break;
          case '-': 
            st[k--] -= st[j--]; st.pop_back();break;
          case '*': 
            st[k--] *= st[j--]; st.pop_back();break;
          case '/': 
            st[k--] /= st[j--]; st.pop_back();break;
        }
      
    
    return st[0];
  }
};