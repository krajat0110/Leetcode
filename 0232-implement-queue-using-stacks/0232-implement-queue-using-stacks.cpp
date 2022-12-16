class MyQueue {
    stack<int>s,q;
public:    
    void push(int x) {
        s.push(x);    
    }   
    int pop() {
        
       while(s.size() != 1){
            q.push(s.top());
            s.pop();
        }
        
        int rv = s.top();
        s.pop();
        while(q.size() != 0){
            s.push(q.top());
            q.pop();
        }
        return rv;
    }
    
    int peek() {
        while(s.size() != 1){
            q.push(s.top());
            s.pop();
        }
        int rv = s.top();
        while(q.size() != 0){
            s.push(q.top());
            q.pop();
        }
        return rv;
    }
    
    bool empty() {
        return s.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */