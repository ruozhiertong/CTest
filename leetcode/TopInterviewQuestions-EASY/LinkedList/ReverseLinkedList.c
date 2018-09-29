/*
Reverse Linked List

Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?


*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//迭代(循环)。
//递归。

//递归。
struct ListNode* reverseList(struct ListNode* head) 
{
	if(head == NULL || head->next == NULL)
		return head;

	//可以不用如此。
	// if(head->next->next == NULL)
	// {
	// 	struct ListNode * temp = head->next;
	// 	head->next = NULL;
	// 	temp->next = head;
	// 	return temp;
	// }

	struct ListNode * next, *last;
	next = reverseList(head->next); 
	last = next;
	while(last->next != NULL)
	{
		last = last->next;
	}
	
	last->next = head;
	head->next = NULL;

	return next;
}



//迭代。
struct ListNode* reverseList2(struct ListNode* head) 
{
	if(head == NULL || head->next == NULL)
		return head;

	struct ListNode * node1 = head;
	struct ListNode * node2;
	struct ListNode * preLast = NULL;
	while(node1->next != preLast)
	{
		node2 = node1;
		while(node2->next != preLast)
		{
			node2 =node2->next;
		}
		struct ListNode * temp = node1;
		node1 = node1->next;
		node2->next = temp;
		temp->next = preLast;
		preLast = temp;
	}

	return node1;
}

//更简单的迭代。O(n)
struct ListNode* reverseList3(struct ListNode* head) {
    struct ListNode *curNode = head;
    struct ListNode *prevNode = NULL;
    struct ListNode *tmpNode = NULL;
    
    if(head == NULL || head->next == NULL)
        return head;
    
    while(curNode)
    {
            tmpNode = curNode;
            curNode = curNode->next;
            tmpNode->next = prevNode;
            prevNode = tmpNode;
    }
    
    head = prevNode;
    
    return (head);
    
}