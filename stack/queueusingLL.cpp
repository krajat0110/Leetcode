#include <iostream>
using namespace std;

class stack
{
private:
    class ListNode
    {
    public:
        int data = 0;
        ListNode *next = nullptr;

        ListNode(int data)
        {
            this->data = data;
        }
    };

private:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int NoOfElements = 0;

private:
    void addLast(ListNode *node)
    {
        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->next = node;
            this->tail = node;
        }
    }

    ListNode *removeFirst()
    {
        ListNode *rv = this->head;
        if (this->head == this->tail)
        {
            this->head = NULL;
            this->tail = NULL;
        }
        else
        {
            this->head = rv->next;
        }
        rv->next = NULL;
    }

public:
    int size()
    {
        return this->NoOfElements;
    }

    bool isEmpty()
    {
        return this->NoOfElements == 0;
    }

public:
    void push(int data)
    {
        ListNode *node = new ListNode(data);
        addLast(node);
        this->NoOfElements++;
    }

public:
    int top()
    {
        if (this->head == NULL)
        {
            return -1;
        }
        return this->head->data;
    }

public:
    void pop()
    {
        ListNode *node = removeFirst();
        NoOfElements--;
        
    }
};

int main()
{

  push(5);
  push(3);
  push(6);
  
  return 0;
}