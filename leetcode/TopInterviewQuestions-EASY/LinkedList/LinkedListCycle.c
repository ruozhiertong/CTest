/*
Linked List Cycle

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

*/


//判断链表有含环。（最后接待next 不为NULL）
//方法1.愚笨的方法，就是记录节点是否重复走过。保存未重复过的节点，然后判断每次新取节点是否在保存的节点集合中如果在就有环。如果直到NULL都没有，那么就没有环。
//方法2.使用快慢指针。
//方法3.使用hashMap/hashTable ，保存访问过的对象，检测后续对象是否有相同的hash值。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//这里使用快慢指针处理。链表追逐。
bool hasCycle(struct ListNode *head) 
{
	struct ListNode * slow, *fast;

	slow = fast = head;

	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if(fast == slow)
			return 1;
	}

	return 0;
    
}

