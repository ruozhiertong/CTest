/*
Intersection of Two Arrays II. 两个数组的交集。

Given two arrays, write a function to compute their intersection.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]

*/

#include <stdio.h>
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) 
{
	int max = nums1Size > nums2Size? nums1Size: nums2Size;
	int *result = (int *)malloc(max * sizeof(int));
	int resultSize = 0;
	int *used = (int *)malloc(nums2Size * sizeof(int)); //用于标记nums2是否被用过。
	memset(used, 0 , nums2Size * sizeof(int));
	for(int i = 0; i < nums1Size; i++)
	{
		for(int j = 0; j < nums2Size ; j++)
		{
			if(nums1[i] == nums2[j] && used[j] == 0)
			{
				result[resultSize++] = nums1[i];
				used[j] = 1;
				break;
			}
		}
	}
	free(used);
	*returnSize = resultSize;
	return result;    
}