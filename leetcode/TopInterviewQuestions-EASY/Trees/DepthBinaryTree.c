/*
Maximum Depth of Binary Tree
  Go to Discuss
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.

*/

//方法1：深度优先遍历(前中后序) 求高度。 （可递归，可非递归）
//方法2：广度优先遍历（层次遍历）求高度。 （非递归）

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 //深度优先（先序），递归方式。 递归方式更简单。
int maxDepth(struct TreeNode* root) 
{
	if(root == NULL)
		return 0;

	int height;
	int leftH = maxDepth(root->left);
	int rightH = maxDepth(root->right);
	height = leftH > rightH ? leftH + 1: rightH + 1;
	return height;
}