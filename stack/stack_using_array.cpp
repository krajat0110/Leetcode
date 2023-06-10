#include <iostream>
using namespace std;

class stack
{
private:
    int *arr;
    int tos;          // top of stack
    int noelements; // no of elements
    int MaxCapacity;  // size

public:
    stack(int size)
    {
        initialize(size);
    }

    stack()
    {
        initialize(10); // 10 is the default size and we have used chainning of constructor
    }

protected:
    void initialize(int size)
    {
        this->noelements = 0;
        this->MaxCapacity = size;
        this->arr = new int[this->MaxCapacity];
        this->tos = -1;
    }

public:
    int size()
    {
        return this->noelements;
    }
    bool isEmpty()
    {
        return (this->noelements == 0);
    }
    int pop()
    {
        if (this->noelements == 0)
        {
            return -1;
        }
        int rv = this->arr[this->tos];
        this->arr[this->tos] = 0;
        this->noelements--;
        this->tos--;

        return rv;
    }

    void push(int data)
    {
        if (this->noelements == this->MaxCapacity)
        {
            return;
        }
        this->arr[++this->tos] = data;
        this->noelements++;
    }
    int top()
    {
        if (this->noelements == 0)
        {
            return -1;
        }
        return this->arr[this->tos];
    }
};

int main()
{
    stack st;
    cout << st.top() << endl;
    return 0;
}