/*

 Binary Tree Level Order Traversal
  Go to Discuss
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/

#include <stdio.h>

 // Definition for a binary tree node.
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };
 
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */



 //层次遍历
 //returnSize 实际上就是层高/数组个数。
 //返回二维数组。
int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) 
{
     if(root == NULL)
    	return NULL;

    struct TreeNode *queue [1024];
    int store[10][1024]; //不足：有限制，最多十层。
    queue[0] = root;
    int size = 1;
    int level = 0; //树的层数。
    int levelSize[10];//每层节点个数。
    store[level][0] = root->val;
    levelSize[level++] = 1;

    while(size != 0)
    {
    	struct TreeNode *temp [1024];
    	int nodeCount = 0;
    	for(int i = 0; i < size; i++)
    	{
    		if(queue[i]->left)
    		{
    			temp[nodeCount] = queue[i]->left;
    			store[level][nodeCount] = queue[i]->left->val;
    			nodeCount++;
    		}
    		if(queue[i]->right)
    		{
    			temp[nodeCount] = queue[i]->right;
    			store[level][nodeCount] = queue[i]->right->val;
    			nodeCount++;
    		}
    	}
    	levelSize[level++] = nodeCount;
    	size = nodeCount;
    	memcpy(queue , temp, 1024 * sizeof(struct TreeNode*));
    }
    level -=1; // 最后一次nodeCount 为0，不应该算一层。

    int **arr = (int **)malloc(sizeof(int *) * level);
    *columnSizes = (int *)malloc(sizeof(int)* level);

    for(int i = 0; i < level; i++)
    {
    	(*columnSizes)[i] = levelSize[i]; //注意这里* 和[]，加了括号
    }

    for(int i = 0; i < level; i++)
    {
    	arr[i] = (int *)malloc(sizeof(int) * (*columnSizes)[i] );
    }

    for(int row = 0 ; row < level; row++)
    {
    	for(int col = 0; col < (*columnSizes)[row]; col++)
    	{
            arr[row][col] = store[row][col];
    		//printf("%d \n",arr[row][col]);
    	}
    	//printf("\n");
    }
    
    *returnSize = level;
    
    return arr;
}

int initTree(struct TreeNode **root, char *arr, int size)
{
    struct TreeNode *nodes[1024];
	for(int i = 0; i < size; i++)
	{
		if(arr[i] == '\0')
        {
            nodes[i] = NULL;
            continue;
        }
		else
		{
			nodes[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
			nodes[i]->val  = arr[i] - '0';
            nodes[i]->left = NULL;
            nodes[i]->right = NULL;
		}
	}
    for(int i = 0; i< size/2; i++) //2^n -1  ==> (2^n-1)/2
    {
        if(nodes[i] == NULL)
            continue;
        nodes[i]->left = nodes[2*(i+1) - 1]; // index
        nodes[i]->right = nodes[2*(i+1) + 1 - 1];
    }
    //printTreeNode(nodes[0]);
    *root = nodes[0];
	return 0;
}

int main()
{

	struct TreeNode *root;
	char arr1[7] = {'3','9','0' + 20,'\0','\0','0'+ 15,'7'};
	initTree(&root,arr1, 7);

	int *columnSizes;
	int returnSize = 0;
	int **arr = levelOrder(root, &columnSizes, &returnSize);
	for(int row = 0 ; row < returnSize; row++)
    {
    	for(int col = 0; col < columnSizes[row]; col++)
    	{
    		printf("%d \n",arr[row][col]);
    	}
    	printf("\n");
    }
	return 0;
}




//动态的增长内存。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 
 * print node:
 * push children on to fifo
 */

// struct arr {
//     struct TreeNode **arr;
//     int count;
//     int ind;
// };


// void push(struct arr *a, struct TreeNode *t)
// {
//    a->arr = realloc(a->arr, (a->count+1) * sizeof *a->arr);
//     a->arr[a->count++] = t;
// }

// struct TreeNode *pop(struct arr *a)
// {
//     if (a->ind >= a->count)
//         return NULL;
//     return a->arr[a->ind++];
// }

// int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
//     struct arr a;
//     struct arr b;
//     int **ret = NULL;
//     int  *sizes = NULL;
//     int nret = 0;
//     int s;
//     if (root == NULL)
//         return NULL;
    
//     memset(&a, 0, sizeof a);
//     memset(&b, 0, sizeof b);
    
//     push(&a, root);
//     while (a.count) {
//         ret = realloc(ret, (nret+1) * sizeof *ret);
//         sizes = realloc(sizes, (nret+1) * sizeof *sizes);
//         ret[nret] = malloc((nret == 0 ? 1 : sizes[nret-1]) * 2 * sizeof(int));
//         s = 0;
//         while((root = pop(&a)) != NULL) {
//             ret[nret][s++] = root->val;
//             if (root->left)
//                 push(&b, root->left);
//             if (root->right)
//                 push(&b, root->right);
//         }
//         sizes[nret] = s;
//         nret++;
//         free(a.arr);
//         a = b;
//         memset(&b, 0, sizeof(b));
//     }
//     *columnSizes = sizes;
//     *returnSize = nret;
//     return ret;
// }
