/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    
    void copyNodes(Node *head){
    Node *curr = head;
    while(curr != NULL ){
        Node *forw = curr -> next;
        Node *node = new Node(curr -> val);
        
        node -> next = forw;
        curr -> next = node;
     
      curr = forw;   
    }
}

void SetRandoms(Node *head){
    Node *curr = head;
    while(curr != NULL){
        if(curr -> random != NULL)
          curr -> next -> random = curr -> random -> next;
          
        curr = curr -> next -> next;
    }
}

Node *extractList(Node *head){
    Node *Dummy = new Node(-1);
    Node *copyCurr = Dummy;
    
    Node *curr = head; 
    while(curr != NULL){
        
        copyCurr -> next = curr -> next;
        copyCurr = copyCurr -> next;
        
        curr -> next = curr -> next -> next;    
        curr = curr -> next;
    }
    return Dummy -> next;
}

    Node* copyRandomList(Node* head) {
    if(head == NULL)
    return NULL;
     
    copyNodes(head);
    SetRandoms(head);
    
    return extractList(head);
  }
};