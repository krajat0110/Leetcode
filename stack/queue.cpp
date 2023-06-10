#include <iostream>
using namespace std;

class queue
{
private:
    int *arr;
    int noofElements;
    int MaxCapacity;
    int nextplace;
    int toq; // top of queue

protected:
    void initialize(int size)
    {
        this->arr = new int[size];
        this->nextplace = this->toq = 0;
        this->noofElements = 0;
        this->MaxCapacity = size;
    }

public:
    queue()
    {
        initialize(10);
    }

protected:
    int capacity()
    {
        return this->MaxCapacity;
    }

public:
    int size()
    {
        return this->noofElements;
    }

    bool isEmpty()
    {
        return this->noofElements == 0;
    }

    void display()
    {
        for (int i = 0; i < this->noofElements; i++)
        {
            int idx = (this->toq + i) % MaxCapacity;
            cout << this->arr[idx] << " ";
        }
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Queue_is_empty" << endl;
            return -1;
        }
        int rv = this->arr[this->toq];
        this->arr[this->toq] = 0;

        this->toq = (this->toq + 1) % this->MaxCapacity;

        this->noofElements--;
        return rv;
    }

    void push(int data)
    {
        if (noofElements == MaxCapacity)
        {
            cout << "queue_is_full" << endl;
        }
        else
        {
            this->arr[this->nextplace] = data;
            this->nextplace = (this->nextplace + 1) % this->MaxCapacity;
            this->noofElements++;
        }
    }

    int front()
    {
        if (isEmpty())
        {
            return -1;
        }
        else
        {
            return this->arr[toq];
        }
    }
};

int main()
{
    queue st;
    cout << st.front() << endl;
    return 0;
}