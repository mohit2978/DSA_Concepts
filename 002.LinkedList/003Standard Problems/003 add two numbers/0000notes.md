## Add two numbers

 Note: read this ques very carefully!!

Given two non-empty linked lists l1 and l2 which represent two non-negative integers.



The digits are stored in reverse order with each node storing one digit.

Add two numbers and return the sum as a linked list.



The sum Linked List will be in reverse order as well.
The Two given Linked Lists represent numbers without any leading zeros, except when the number is zero itself.

Examples:

----
Input: l1 = head -> 5 -> 4, l2 = head -> 4

Output: head -> 9 -> 4

Explanation: l1 = 45, l2 = 4.

l1 + l2 = 45 + 4 = 49.

---
Input: l1 = head -> 4 -> 5 -> 6, l2 = head -> 1 -> 2 -> 3

Output: head -> 5 -> 7 -> 9

Explanation: l1 = 654, l2 = 321.

l1 + l2 = 654 + 321 = 975.


### Mycode


```cpp

/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            if(l1==nullptr ||l2==nullptr) return l1==nullptr?l2:l1;
            ListNode* h1=l1;
            ListNode* h2=l2;
            ListNode * res=new ListNode(-1);
            ListNode *c1=h1;
            ListNode *c2=h2;
            ListNode *c3=res;
            int carry=0;
            while( c1!=nullptr && c2!=nullptr){
                int tres=c1->val;
                tres+=c2->val;
                tres+=carry;
                int data=tres%10;
                carry=tres/10;
                ListNode * newNode=new ListNode(data);
                c3->next=newNode;
                c3=c3->next;
                c1=c1->next;
                c2=c2->next;
            }

            while(c1!=nullptr){
                int tres=c1->val;
                tres+=carry;
                int data=tres%10;
                carry=tres/10;
                ListNode * newNode=new ListNode(data);
                c3->next=newNode;
                c3=c3->next;
                c1=c1->next;
            }

            while(c2!=nullptr){
                int tres=c2->val;
                tres+=carry;
                int data=tres%10;
                carry=tres/10;
                ListNode * newNode=new ListNode(data);
                c3->next=newNode;
                c3=c3->next;
                c2=c2->next;
            }
            if(carry!=0){
                ListNode * newNode=new ListNode(carry);
                c3->next=newNode;
                c3=c3->next;
            }
            c3=res->next;
            res->next=nullptr;
            delete(res);
            return c3;


    }
};
```

#### Striver code

```cpp

#include <bits/stdc++.h>
using namespace std;

// Definition of Singly Linked List
struct ListNode {
    int val;
    ListNode *next;
    ListNode() {
        val = 0;
        next = NULL;
    }
    ListNode(int data1){
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1){
        val = data1;
        next = next1;
    }
};

class Solution {
public:
    //Function to add two numbers as linked list
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /*Dummy node to act as the 
        starting point of the result list*/
        ListNode *dummy = new ListNode(); 
        /*Temp pointer to build 
        the result list*/
        ListNode *temp = dummy; 
        //Initialize carry
        int carry = 0;                    

        /*Iterate while there are nodes in l1 or l2, 
        or there's a carry to process*/
        while ((l1 != NULL || l2 != NULL) || carry) {
            int sum = 0;

            /*Add the value from l1 
            if available*/
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }

            /*Add the value from l2 
            if available*/
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }

            //Add the carry
            sum += carry;
            //Update the carry
            carry = sum / 10;             

            /* Create a new node with the digit value 
            and attach it to the result list*/
            ListNode *node = new ListNode(sum % 10);
            temp->next = node;
            /*Move to the 
            next position in the result list*/
            temp = temp->next;             
        }
        /*Return the result list
        skipping the dummy node*/
        return dummy->next;                
    }
};

// Function to print the linked list
void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    //Manual creation of linked list
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));

    //Instance of solution class
    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);

    // Print the result
    printList(result);

    return 0;
}
```