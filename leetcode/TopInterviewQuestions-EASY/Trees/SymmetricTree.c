/*
Symmetric Tree
  Go to Discuss
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

*/

#include <stdio.h>

struct TreeNode {
         int val;
         struct TreeNode *left;
         struct TreeNode *right;
     };

//镜像树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 //方法1：如果是镜像树，其中序遍历是回文形式的。
 //所以判断其中序遍历是否是回文，如果是就是镜像树，如果不是就不是镜像树。
 //不过就是需要额外的空间，动态增长空间。空间上不是很友好的。
 
 //方法2：将每个节点的左右节点互换，互换后的树如果和原树一样，就是镜像树。

 //方法3：层次遍历，每层从左到右遍历是回文形式的。

 //方法4：最简单，判断两个孩子node，左node的左孩子和右node的右孩子， 左node的右孩子和右node的左孩子，


 //方法3. //这里的处理方式，较真起来只能处理10层高的树，1024个。要想无限制的，可以使用动态增长的空间去存储。
int isSymmetric(struct TreeNode* root)
{
    if(root == NULL)
    	return 1;

    struct TreeNode *queue [1024];
    char store[1024];
    queue[0] = root;
    int size = 1;
    while(size != 0)
    {
    	struct TreeNode *temp [1024];
    	int storeCount = 0;
    	int nodeCount = 0;
    	for(int i = 0; i < size; i++)
    	{
    		if(queue[i]->left)
    		{
    			temp[nodeCount++] = queue[i]->left;
    			store[storeCount++] = '0' + queue[i]->left->val;
    		}
    		else
    		{
    			store[storeCount++] = '\0'; //为空用'\0'表示。
    		}

    		if(queue[i]->right)
    		{
    			temp[nodeCount++] = queue[i]->right;
    			store[storeCount++] = '0' + queue[i]->right->val;
    		}
    		else
    		{
    			store[storeCount++] = '\0'; //为空用'\0'表示。
    		}
    	}
    	for(int i = 0; i < storeCount; i++)
    	{
    		printf("%c ", store[i]);
    	}
    	//判断每层stroe存储的是否是回文形式。
    	int i = 0;
    	int j = storeCount - 1;
    	while(i < j)
    	{
    		if(store[i] != store[j])
    			return 0;
    		i++;
    		j--;
    	}

    	size = nodeCount;
    	memcpy(queue , temp, 1024 * sizeof(struct TreeNode*));
    }

    return 1;
}

//方法4.
int isMirror(struct TreeNode *t1, struct TreeNode *t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    return (t1->val == t2->val)
        && isMirror(t1->right, t2->left)
        && isMirror(t1->left, t2->right);
}
int isSymmetric2(struct TreeNode* root)
{
	if(root == NULL)
		return 1;

	return isMirror(root, root);

}



void printTreeNode(struct TreeNode * root)
{
    if(root == NULL)
        return;
    
    if(root->left)
        printTreeNode(root->left);
    
    printf("%d\n", root->val);
    
    if(root->right)
        printTreeNode(root->right);
    
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
	char arr[7] = {'1','2','2','\0','3','\0','3'};
	initTree(&root,arr, 7);
	printTreeNode(root);
    isSymmetric(root);

	return 0;
}