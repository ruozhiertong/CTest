/*
  Remove Nth Node From End of List

Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 //方法1；比较愚笨的，two pass。先计算出总节点数m ,然后顺序遍历到第 m-n+ 1 个，删除之。
 //方法2： one pass。
 //one pass.
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) 
{
	 struct ListNode *p1 = head;
	struct ListNode *p2 = head;
	/*
	n = 3
	1 2 3 4 5 6 7 8 NULL
	*/
	// for(int i = 1; i <= n + 1; i++)
	// {
 //        if(p1 != NULL)
	// 	    p1 = p1->next;
	// }
    
 //    struct ListNode *deleteNode;
 //    if(p1 == NULL)
 //    {
 //        deleteNode = p2;
 //        head = NULL;
 //    }
 //    else
 //    {
 //        while(p1 != NULL)
 //        {
 //            p1 = p1->next;
 //            p2 = p2->next;
 //        }
 //        deleteNode = p2->next;
 //        p2->next = p2->next->next;
 //    }
	
	// free(deleteNode);
 //    return head;

	for(int i = 1; i <= n; i++)
	{
        if(p1 != NULL)
		    p1 = p1->next;
	}

	struct ListNode *pre = p2;

	while(p1 != NULL)
	{
		p1 = p1->next;
        pre = p2;
		p2 = p2->next;
	}

	//将删除转嫁给下一个
	if(p2->next == NULL)
	{
        free(p2);
        if(head == p2)
            head = NULL; //这里要注意。如果是head节点被删除，要处理head指向NULL
        else
            pre->next = NULL; //这里注意，如果不是head节点，那么pre节点的next要指向NULL
		p2 = NULL;
	}
	else
	{
		struct ListNode *deleteNode = p2->next;
		p2->val = p2->next->val;
		p2->next = p2->next->next;
		free(deleteNode);
	}
    return head;
}


//巧妙的解法。 one pass.
/*
class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode** t1 = &head, *t2 = head;
        for(int i = 1; i < n; ++i)
        {
            t2 = t2->next;
        }
        while(t2->next != NULL)
        {
            t1 = &((*t1)->next);
            t2 = t2->next;
        }
        *t1 = (*t1)->next;
        return head;
    }
};
*/