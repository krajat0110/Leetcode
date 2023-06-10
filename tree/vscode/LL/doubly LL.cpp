#include <iosream>
using namespace std;

//insert first in ll
private:
void addFirstNode(Node *node)
{
    if (this->size == 0)
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        node->next = this->head;
        this->head->prev = node;
        this->head = node;
    }
    this->size++;
}

public:
void addFirst(int data)
{
    Node *node = new Node(data);
    addFirstNode(node);
}

//add Last  of ll
private:
void addLastNode(Node *node) {
    if(this -> size == 0){
        this -> head = this -> tail = node;
    }else{
        node -> prev = this -> tail;
        this -> tail -> next = node;
        this -> tail = node;
    }
    this -> size++;
} 
    
public : void addLast(int data)
{
    Node *node = new Node(data);
    addLastNode(node);
}

// ye wala code java me he
//remove from first
private
boolean ListIsEmptyException()
{
    if (this.size == 0)
    {
        System.out.print("ListIsEmpty: ");
        return true;
    }
    return false;
}
private
Node removeFirstNode()
{
    Node node = this.head;
    if (this.size == 1)
    {
        this.head = this.tail = null;
    }
    else
    {
        Node forw = node.next;
        node.next = null;
        forw.prev = null;

        this.head = forw;
    }
    this.size--;
    return node;
}
public
int removeFirst()
{
    if (ListIsEmptyException())
        return -1;

    return removeFirstNode().data;
}

//remove from the end of the list
private
Node removeLastNode()
{
    Node node = this.tail;
    if (size == 1)
        this.head = this.tail = null;
    else
    {
        Node end = this.tail.prev;

        end.next = null;

        this.tail = end;
    }
    this.size--;
    return node;
}

public
int removeLast()
{
    if (ListIsEmptyException())
        return -1;
    Node node2 = removeLastNode();
    return node2.data;
}

int main()
{
}