#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        next = NULL;
    }
};


// pepcoding portal
ListNode *reverse(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *pre = NULL, *curr = head;
    while (curr != NULL)
    {
        ListNode *frow = curr->next; // backup
        //changes saare address me honge list ki values me nahi
        curr->next = pre; //link 
        pre = curr;       //move
        curr = frow;
    }
    return pre;
}

ListNode *midnode(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
bool isPalindrome(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return true;

    ListNode *mid = midnode(head);
    ListNode *nhead = mid->next;
    mid->next = NULL;
    nhead = reverse(nhead);
    ListNode *c1 = head, *c2 = nhead;
    while (c1 != NULL && c2 != NULL)
    {
        if (c1->val != c2->val)
            return false;
        c1 = c1->next;
        c2 = c2->next;
    }
    return true;
}

void fold(ListNode *head)
{
    if (head == NULL || head->next == NULL)
      return;
    ListNode *mid = midnode(head);
    ListNode *nhead = mid->next;
    mid->next = NULL;
    nhead = reverse(nhead);

    ListNode *c1 = head, *c2 = nhead;
    while (c2 != NULL)
    {
        ListNode *f1 = c1->next, *f2 = c2->next;
        c1->next = c2;
        c2->next = f1;

        c1 = f1;
        c2 = f2;
    }
}

void unfold(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return;
    ListNode *c1 = head, *c2 = head->next, *nhead = c2;
    while (c2 != NULL && c2->next != NULL)
    {
        ListNode *f1 = c2->next;
        c1->next = f1;
        c2->next = f1->next;

        c1 = c1->next;
        c2 = c2->next;
    }
    c1->next = NULL;
    nhead = reverse(nhead);
    c1->next = nhead;
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (l1 == NULL | l2 == NULL)
        return l1 != NULL ? l1 : l2;

    ListNode *Dummy = new ListNode(-1);
    ListNode *small = Dummy, *c1 = l1, *c2 = l2;

    while (c1 != NULL && c2 != NULL)
    {
        if (c1->val <= c2->val)
        {
            small->next = c1;
            c1 = c1->next;
        }
        else
        {
            small->next = c2;
            c2 = c2->next;
        }
        small = small->next;
    }
    small->next = c1 != NULL ? c1 : c2;
    ListNode *head = Dummy->next;
    Dummy->next = NULL;
    delete Dummy;
    return head;
}

ListNode *mergeSort(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    ListNode *mid = midnode(head);
    ListNode *nhead = mid->next;
    mid->next = NULL;

    return mergeTwoLists(mergeSort(head), mergeSort(nhead));
}

//leetcode 23

//// merge sort without tail
ListNode *mergeksorted(vector<ListNode *> &arr)
{
    ListNode *res = NULL;
    for (ListNode *List : arr)
    {
        res = mergeTwoLists(res, List);
    }
    return res;
}

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    return mergeksorted(lists);
}

//// merge sort with tail
ListNode *gettail(ListNode *Head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ListNode *curr = Head;
    while (curr != NULL)
        curr = curr->next;
    return curr;
}

ListNode *mergeksorted_02(vector<ListNode *> &arr)
{
    if (arr.length() == 0)
        return NULL;
    ListNode *dummy = new ListNode(-1);
    ListNode small = dummy;
    for (int i = 0; i < arr.length(); i++)
    {
        ListNode *tail = gettail(arr[i]);
        if (tail != NULL)
        {
            small->next = arr[i];
            small = tail;
        }
    }
    return merge(dummy.next);
}

//segregateEvenOdd
ListNode *segregateEvenOdd(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ListNode *even = new ListNode(-1), *odd = new ListNode(-1);
    ListNode *ev = even, *op = odd, *curr = head;
    while (curr != NULL)
    {
        if (curr->val % 2 != 0)
        {
            op->next = curr;
            op = op->next;
        }
        else
        {
            ev->next = curr;
            ev = ev->next;
        }
        curr = curr->next;
    }
    op->next = NULL, ev->next = NULL;
    ev->next = odd->next;

    return even->next;
}

//reverse in k grp
ListNode *th = NULL, *tt = NULL;

void addfirstnode(ListNode *node)
{
    if (th == NULL)
        th = tt = node;
    else
    {
        node->next = th;
        th = node;
    }
}

ListNode *reverseInKGroup(ListNode *head, int k)
{
    if (head == NULL || head->next == NULL || k <= 1)
    {
        return head;
    }
    int len = lengthLL(head);
    ListNode *curr = head, *oh = NULL, *ot = NULL;
    while (curr != NULL && len >= k)
    {
        int tempk = k;
        while (tempk-- > 0)
        {
            ListNode *greater = curr->next;
            curr->next = NULL;
            addfirstnode(curr);
            curr = greater;
        }
        if (oh == NULL)
        {
            oh = th;
            ot = tt;
        }
        else
        {
            ot->next = th;
            ot = tt;
        }
        th = tt = NULL;
        len -= k;
    }
    ot->next = curr;
    return oh;
}

//reverse in range
ListNode *reverseBetween(ListNode *head, int m, int n)
{
    if (head == NULL || head->next == NULL || m == n)
        return head;
    ListNode *curr = head;
    ListNode *small = NULL;
    int i = 1;
    while (curr != NULL)
    {
        while (i >= m && i <= n)
        {
            ListNode *greater = curr->next;
            curr->next = NULL;
            addfirstnode(curr);
            curr = greater;
            i++;
        }
        if (i > n)
        {
            if (small != NULL)
            {
                small->next = th; //(m-1) jaha se reverse kari he uss se just ek peeche wali
                tt->next = curr;  // tt hamari reversed node ke end ko store kar rahi he
                return head;
            }
            else
            {
                tt->next = curr;
                return th;
            }
        }
        i++;
        small = curr;
        curr = curr->next;
    }
    return head;
}

//segerate 0 and 1
ListNode *segregate01(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *zero = new ListNode(-1);
    ListNode *prevz = zero;
    ListNode *one = new ListNode(-1);
    ListNode *prevo = one;

    ListNode *curr = head;

    while (curr != NULL)
    {
        if (curr->val == 0)
        {
            prevz->next = curr;
            prevz = prevz->next;
        }
        else
        {
            prevo->next = curr;
            prevo = prevo->next;
        }
        curr = curr->next;
    }
    prevz->next = one->next;
    prevo->next = NULL;

    return zero->next;
}

//segregate 0 1 2

ListNode *segregate012(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *zero = new ListNode(-1);
    ListNode *prevz = zero;
    ListNode *one = new ListNode(-1);
    ListNode *prevo = one;
    ListNode *two = new ListNode(-1);
    ListNode *prevt = two;

    ListNode *curr = head;
    while (curr != NULL)
    {
        if (curr->val == 0)
        {
            prevz->next = curr;
            prevz = prevz->next;
        }
        else if (curr->val == 1)
        {
            prevo->next = curr;
            prevo = prevo->next;
        }
        else
        {
            prevt->next = curr;
            prevt = prevt->next;
        }
        curr = curr->next;
    }
    prevo->next = two->next;
    prevz->next = one->next;

    prevt->next = NULL;
    return zero->next;
}

//segregateOnLastIndex pepcoding portal

ListNode *segregateOnLastIndex(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    ListNode *tail = head;
    while (tail->next != nullptr)
        tail = tail->next;

    ListNode *prev = new ListNode(-1);
    ListNode *prevs = prev;

    ListNode *forw = new ListNode(-1);
    ListNode *forwl = forw;

    ListNode *curr = head;

    while (curr != NULL)
    {

        if (curr->val <= tail->val)
        {
            prevs->next = curr;
            prevs = prevs->next;
        }
        else
        {

            forwl->next = curr;
            forwl = forwl->next;
        }
        curr = curr->next;
    }

    forwl->next = NULL;
    prevs->next = forw->next;

    prev->next = NULL;
    forw->next = NULL;

    return prevs;
}

//segmentaion over pivot index
ListNode *segregate(ListNode *head, int pivotIdx)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *pivotnode = head;

    while (pivotIdx-- > 0)
    {
        pivotnode = pivotnode->next;
    }

    ListNode *sprev = new ListNode(-1);
    ListNode *sp = sprev;

    ListNode *prevl = new ListNode(-1);
    ListNode *gp = prevl;
    ListNode *curr = head;

    while (curr != NULL)
    {
        if (curr != pivotnode && curr->val <= pivotnode->val)
        {
            sp->next = curr;
            sp = sp->next;
        }
        else if (curr != pivotnode)
        {
            gp->next = curr;
            gp = gp->next;
        }
        curr = curr->next;
    }

    sp->next = pivotnode;
    pivotnode->next = prevl->next;
    gp->next = NULL;

    return sprev->next;
}

// quick sort
vector<ListNode *> seg(ListNode *head, int pivotIdx)
{
    if (head == NULL || head->next == NULL)
        return {head, head, head};
    ListNode *pivotnode1 = head;
    while (pivotIdx-- > 0)
    {
        pivotnode1 = pivotnode1->next;
    }

    ListNode *sprev = new ListNode(-1), *sp = sprev, *lprev = new ListNode(-1), *lp = lprev, *curr = head;
    while (curr != NULL)
    {
        if (curr != pivotnode1 && curr->val <= pivotnode1->val)
        {
            sp->next = curr;
            sp = sp->next;
        }
        else if (curr != pivotnode1)
        {
            lp->next = curr;
            lp = lp->next;
        }
        curr = curr->next;
    }
    sp->next = lp->next = pivotnode1->next = NULL;

    ListNode *lefthead = sprev->next;
    ListNode *righthead = lprev->next;
    return {lefthead, pivotnode1, righthead};
}

vector<ListNode *> mergell(vector<ListNode *> left, ListNode *pivotnode, vector<ListNode *> right)
{
    vector<ListNode *> myres(2, NULL);
    if (left[0] != NULL && right[0] != NULL)
    {
        myres[0] = left[0];
        myres[1] = right[1];

        left[1]->next = pivotnode;
        pivotnode->next = right[0];
    }
    else if (right[0] != NULL)
    {
        myres[0] = pivotnode;
        myres[1] = right[1];

        pivotnode->next = right[0];
    }
    else
    {
        myres[0] = left[0];
        myres[1] = pivotnode;

        left[1]->next = pivotnode;
    }
    return myres;
}

vector<ListNode *> quickSort2(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return {head, head};

    int len = lengthll(head);
    int pivotIdx = len / 2;

    vector<ListNode *> partation = seg(head, pivotIdx);
    vector<ListNode *> left = quickSort2(partation[0]);
    vector<ListNode *> right = quickSort2(partation[2]);

    return mergell(left, partation[1], right);
}
ListNode *quickSort(ListNode *head)
{
    return quickSort2(head)[0];
}

//delete nth node form end
 ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL) return head;
        
        ListNode *curr = head , *forw = head;
        while(n-->0){
            forw = forw -> next;
        }
        
        if(forw == NULL){
            head = head -> next;
            return head;
        }
        
        while(forw -> next != NULL){
            curr = curr -> next;
            forw = forw -> next;
        }
        
        curr -> next = curr -> next -> next;
        return head;
    }

//add two list
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    if (l1 == NULL || l2 == NULL)
        return l1 != NULL ? l1 : l2;

    l1 = reverse(l1);
    l2 = reverse(l2);

    ListNode *Dummy = new ListNode(-1);
    ListNode *prev = Dummy, *c1 = l1, *c2 = l2;
    int carry = 0;
    while (c1 != NULL || c2 != NULL || carry != 0)
    {
        int sum = carry + (c1 != NULL ? c1->val : 0) + (c2 != NULL ? c2->val : 0);
        carry = sum / 10;

        prev->next = new ListNode(sum % 10);
        prev = prev->next;

        if (c1 != NULL)
            c1 = c1->next;
        if (c2 != NULL)
            c2 = c2->next;
    }
    return reverse(Dummy->next);
}

//subtract two lists
ListNode *subtractTwoNumbers(ListNode *l1, ListNode *l2)
{
    if (l2 == NULL)
        return l1;

    l1 = reverse(l1);
    l2 = reverse(l2);

    ListNode *Dummy = new ListNode(-1);
    ListNode *ans = Dummy, *c1 = l1, *c2 = l2;
    int borrow = 0;
    while (c1 != NULL)
    {
        int sub = borrow + c1->val - (c2 != NULL ? c2->val : 0);

        if (sub < 0)
        {
            borrow = -1;
            sub += 10;
        }
        else
            borrow = 0;

        ans->next = new ListNode(sub);
        ans = ans->next;

        c1 = c1->next;
        if (c2 != NULL)
            c2 = c2->next;
    }
    ListNode *head = reverse(Dummy->next), *curr = head;

    while (curr != NULL && curr->val == 0)
    {
        ListNode *forw = curr->next;
        curr->next = NULL;
        curr = forw;
    }

    return curr != NULL ? curr : new ListNode(0);
}

//multiply two ll

ListNode *multiplyTwoDigit(ListNode *list, int digit)
{
    ListNode *Dummy = new ListNode(-1), *prev = Dummy, *c = list;
    int carry = 0;

    while (c != NULL || carry != 0)
    {
        int pord = carry + (c != NULL ? c->val : 0) * digit;
        carry = pord / 10;
        int num = pord % 10;

        prev->next = new ListNode(num);
        prev = prev->next;

        if (c != NULL)
            c = c->next;
    }
    return Dummy->next;
}

void addTwoNo(ListNode *curr, ListNode *prev)
{

    int carry = 0;
    while (curr != NULL || carry != 0)
    {
        int sum = (curr != NULL ? curr->val : 0) + (prev->next != NULL ? prev->next->val : 0) + carry;
        carry = sum / 10;

        if (prev->next == NULL)
            prev->next = new ListNode(0);
        prev = prev->next;
        prev->val = sum % 10;

        if (curr != NULL)
            curr = curr->next;
    }
}

ListNode *multiplyTwoLL(ListNode *l1, ListNode *l2)
{
    l1 = reverse(l1);
    l2 = reverse(l2);

    ListNode *Dummy = new ListNode(-1), *prev = Dummy, *itr_c2 = l2;

    while (itr_c2 != NULL)
    {
        ListNode *smallans = multiplyTwoDigit(l1, itr_c2->val);
        addTwoNo(smallans, prev);

        prev = prev->next;
        itr_c2 = itr_c2->next;
    }
    return reverse(Dummy->next);
}

void print(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
}


//is cycle present in ll list
bool isCyclePresentInLL(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return false;

    ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

//node of a cycle node in ll list
ListNode *isCyclePresent01(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return NULL;

    ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            break;
    }
    return fast;
}

ListNode *CycleNode(ListNode *head)
{
    ListNode *meetingPoint = isCyclePresent01(head);
    if(meetingPoint == NULL || meetingPoint->next == NULL) return NULL;

    ListNode *slow = head , *fast = meetingPoint;
    while(slow != fast){
        slow = slow -> next;
        fast = fast -> next; 
    }
    return slow;
}

/// value of cycle and length pf cycle
// mdash is no of rotation before meetion point 

ListNode *allVariableOfCycle(ListNode *head){
    ListNode *meetingPoint = isCyclePresent01(head);
    if(meetingPoint == NULL || meetingPoint->next == NULL) return  NULL;

    ListNode *slow = head , *fast = meetingPoint;
    int A = 0, mDash = 0;
    while(slow != fast) {
        slow = slow -> next;
        fast = fast -> next; 

        if(fast == meetingPoint)
          mDash++; 
        A++;
    }
    
    slow = meetingPoint;
    slow = slow -> next;
    int cycleLen = 1;
    while(slow != meetingPoint) {
        slow = slow -> next;
        cycleLen++;
    }

    int C = A - mDash * cycleLen;
    int B = cycleLen - C ;
    int m = (A != 0 && C == 0 ) ? 0 : mDash + 1 ; // A > C 
    
}

    int main()
    {

        Node *head = takeInput_Better();
        print(head);
        cout << endl;
        // cout << length(head) << endl;
        int i, data;
        cin >> i >> data;
        // head = insertNode(head, i, data);
        // print(head);
        // head = deleteNode(head, i);
        head = insertNoderec(head, i, data);
        // print (head);
        // head = deleteNoderec(head , i );
        print(head);
    }


    //coding ninja 


    Node *takeInput_Better()
    {
        int data;
        cin >> data;
        Node *head = NULL;
        Node *tail = NULL;
        while (data != -1)
        {
            Node *newNode = new Node(data);
            if (head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = tail->next;
                // OR
                // tail = newNode;
            }

            cin >> data;
        }
        return head;
    }

    Node *insertNode(Node *head, int i, int data)
    {
        Node *newNode = new Node(data);
        int count = 0;
        Node *temp = head;

        if (i == 0)
        {
            newNode->next = head;
            head = newNode;
            return head;
        }

        while (temp != NULL && count < i - 1)
        {
            temp = temp->next;
            count++;
        }
        // cout<<count;
        if (temp != NULL)
        {
            Node *a = temp->next;
            temp->next = newNode;
            newNode->next = a;
        }
        return head;
    }

    int length(Node *head)
    {
        if (head->next == NULL)
        {
            return 1;
        }
        int len = length(head->next);
        return (len + 1);
    }

    // ll of linkedlist iterative

    int lengthll(ListNode *head)
    {

        if (head == NULL)
            return 0;
        ListNode *nextt = head;
        int len = 0;
        while (nextt != NULL)
        {
            nextt = nextt->next;
            len++;
        }
        return len;
    }

    Node *deleteNode(Node *head, int i)
    {
        if (head == NULL)
        {
            return head;
        }
        if (i == 0)
        {
            return head->next;
        }
        Node *curr = head;
        int currPos = 0;
        while (curr != NULL && currPos < i - 1)
        {
            ++currPos;
            curr = curr->next;
        }

        if (curr == NULL || curr->next == NULL)
        {
            return head;
        }
        curr->next = curr->next->next;
        return head;
    }

    Node *insertNoderec(Node *head, int i, int data)
    {
        if (head == NULL)
        {
            if (i == 0)
            {
                Node *newnode = new Node(data);
                return newnode;
            }
            return head;
        }
        Node *newnode = new Node(data);

        if (i == 0)
        {
            newnode->next = head;
            head = newnode;
            return head;
        }

        head->next = insertNoderec(head->next, i - 1, data);
        return head;
    }

    Node *deleteNoderec(Node *head, int i)
    {
        if (head == NULL)
        {
            return head;
        }
        if (i == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return head;
        }
        Node *smallans = deleteNoderec(head->next, i - 1);
        head->next = smallans;
        return head;
}