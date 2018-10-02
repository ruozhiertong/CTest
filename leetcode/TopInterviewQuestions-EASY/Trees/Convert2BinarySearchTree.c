/*

Convert Sorted Array to Binary Search Tree
  Go to Discuss
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5

 */


 //转换位  平衡二叉搜索树。

 /**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* helper(int* nums,int low, int high)
{
	if(low > high)
		return NULL;
	int mid = (low + high)/2;
	struct TreeNode * node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->val = nums[mid];
	node->left = helper(nums, low, mid-1);
	node->right = helper(nums, mid + 1, high);
	return node;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) 
{
 	return helper(nums,0,numsSize - 1); 
}