/*

Merge Two Sorted Lists


Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) 
{
	if(l1 == NULL)
		return l2;
	if(l2 == NULL)
		return l1;
    struct ListNode* head = l1->val < l2->val? l1 : l2;
    struct ListNode* temp;
    temp = head;
    if(temp == l1)
    	l1 = l1->next;
    else
    	l2 = l2->next;

	   
    while(l1 && l2)
    {
    	temp->next = l1->val < l2->val ? l1 : l2;
    	if(temp->next == l1)
    		l1 = l1->next;
    	else
    		l2 = l2->next;
    	temp = temp->next;
    }

    //优化，后续不要while ，直接if。
    if(l1)
    	temp->next = l1;

    if(l2)
    	temp->next = l2;

    /*
    //优化，可以将后续while都放到上面的while。
    while(l1)
    {
    	temp->next = l1;
    	temp = temp->next;
    	l1 = l1->next;
    }
    while(l2)
    {
    	temp->next = l2;
    	temp = temp->next;
    	l2 = l2->next;
    }
    temp->next = NULL;
    */

    return head;

}