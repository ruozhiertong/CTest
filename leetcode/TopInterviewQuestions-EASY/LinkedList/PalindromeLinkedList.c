/*

Palindrome Linked List
  Go to Discuss
Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 //方法1.愚笨的方法。 n! ==>O(n^2)
 //方法2.要想O(n)：a.统计list个数。 b.取中点，分两部分。 3.对后半部分反转，然后与前部分一一比较。
 //方法3.利用递归。也是O(n)。
bool isPalindrome(struct ListNode* head) 
{

	if(head == NULL)
		return 1;

	struct ListNode * cur  = head;
	struct ListNode * preLast = NULL;
	struct ListNode * last = NULL;


	//注意判断条件。
	// while(cur->next && cur->next != preLast)
	// {
	// 	last = cur;
	// 	while(last->next != preLast)
	// 	{
	// 		last = last->next;
	// 	}
	// 	if(cur->val != last->val)
	// 		return 0;
	// 	preLast = last;
	// 	cur = cur->next;
	// }
	 while(cur)
	 {
	 	last = cur;
	 	while(last->next != preLast)
	 	{
	 		last = last->next;
	 	}
	 	if(cur->val != last->val)
	 		return 0;
	 	if(cur == last || cur->next == last)
	 		break;
	 	preLast = last;
	 	cur = cur->next;
	 }

	return 1;
    
}