/*

Validate Binary Search Tree
  Go to Discuss
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:

Input:
    2
   / \
  1   3
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.


*/

//二叉搜索树。

             /**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isValidBST(struct TreeNode* root) 
{
    if(root == NULL)
    	return 1;

  	if(root->left)
  	{
  		if(root->val <= root->left->val)
    		return 0;
    	TreeNode * node = root->left;
    	//同时保证比其右子树还要大。
    	while(node->right)
    	{
    		if(root->val <= node->right->val)
    			return 0;
    		node = node->right;
    	}    		
  	}

    if(root->right)
    {
    	if(root->val >= root->right->val)
    		return 0;

    	TreeNode * node = root->right;
    	while(node->left)
    	{
    		if(root->val >= node->left->val)
    			return 0;
    		node = node->left;
    	}
    }

    if(isValidBST(root->left) == 0)
    	return 0;

    if(isValidBST(root->right) == 0)
    	return 0;

    return 1;

}