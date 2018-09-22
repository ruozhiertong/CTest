#include <stdio.h>
#include <math.h>


struct ListNode {
      int val;
      struct ListNode *next;
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//使用total值，会有问题，如果值爆了，就出错了。
//int 改 long long。 不过这不是解决办法，如果无限大的数，也会爆。
struct ListNode* addTwoNumbers_1(struct ListNode* l1, struct ListNode* l2) {

	struct ListNode * resultList = NULL;
	struct ListNode * last = NULL;

	long long numA = 0;
	long long numB = 0;
	long long total = 0;
	int len = 0;

	struct ListNode * tmp = l1;

	while(tmp)
	{
		numA = numA + pow(10, len) * tmp->val;
		tmp = tmp->next;
		len++;
	}

	tmp = l2;
	len = 0;

	while(tmp)
	{
		numB = numB + pow(10, len) * tmp->val;
		tmp = tmp->next;
		len++;
	}

	total = numA + numB;
	long long left = total;
	if(left == 0)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->val = left;
		node->next = NULL;
		resultList = node;
	}

	while(left != 0)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->val = left % 10;
		node->next = NULL;
		if(resultList == NULL)
		{
			resultList = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}
		left = left/10;
	}

	return resultList;
	

}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{

	struct ListNode * resultList = NULL;
	struct ListNode * last = NULL;

	struct ListNode * tmpL1 = l1;
	struct ListNode * tmpL2 = l2;

	int a, b;
	int carry = 0; //进 1.

	while(tmpL1 && tmpL2)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->next = NULL;

		a = tmpL1->val;
		b = tmpL2->val;
		
		if(a + b  + carry >= 10)
		{
			node->val = a + b  + carry  - 10;
			carry = 1;
		}
		else
		{
			node->val = a + b  + carry;
			carry = 0;
		}

		if(resultList == NULL)
		{
			resultList = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}

		tmpL1 = tmpL1->next;
		tmpL2 = tmpL2->next;
	}

	while(tmpL1)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->next = NULL;
		if(tmpL1->val +  carry >= 10)
		{
			node->val = tmpL1->val  + carry  - 10;
			carry = 1;
		}
		else
		{
			node->val = tmpL1->val + carry;
			carry = 0;
		}

		if(resultList == NULL)
		{
			resultList = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}

		tmpL1 = tmpL1->next;

	}

	while(tmpL2)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->next = NULL;
		if(tmpL2->val +  carry >= 10)
		{
			node->val = tmpL2->val  + carry  - 10;
			carry = 1;
		}
		else
		{
			node->val = tmpL2->val + carry;
			carry = 0;
		}

		if(resultList == NULL)
		{
			resultList = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}
		tmpL2 = tmpL2->next;
	}
    
    if(carry == 1)
    {
        struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->next = NULL;
        node->val = carry;
        if(resultList == NULL)
        {
            resultList = node;
            last = node;
        }
        else
        {
            last->next = node;
            last = node;
        }
    }
        

	return resultList;
}

void inputList(struct ListNode * list,int nums[], int size)
{
    struct ListNode * start = NULL;
	struct ListNode * last = NULL;

	for(int i = 0; i < size; i++)
	{
		struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->val = nums[i];
		node->next = NULL;
		if(i == 0)
		{
			start = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}	
	}
    *list = *start;

}



void inputList2(struct ListNode ** list,int nums[], int size)
{
    struct ListNode * start = NULL;
    struct ListNode * last = NULL;
    
    for(int i = 0; i < size; i++)
    {
        struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = nums[i];
        node->next = NULL;
        if(i == 0)
        {
            start = node;
            last = node;
        }
        else
        {
            last->next = node;
            last = node;
        }	
    }
    *list = start;
}



void printListNode(struct ListNode * list)
{	
	struct ListNode * node = list;
	while(node != NULL)
	{
		printf("%d ", node->val);
		node = node->next;
	}
    printf("\n");

}

int main()
{
	struct ListNode *l1 , l2;
    int numsA[1] = {9};
    int numsB[14] = {1,9,9,9,9,9,9,9,9,9,9,9,9,9};
	inputList2(&l1,numsA, 1);
	inputList(&l2,numsB, 14);

	printListNode(l1);
	printListNode(&l2);
    
    struct ListNode * l3 = addTwoNumbers(l1, &l2);
    printListNode(l3);
    return 0;

}