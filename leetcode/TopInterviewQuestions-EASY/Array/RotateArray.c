/*
Rotate Array.
Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
*/
#include <stdio.h>

/*
朴素简单的方法: 利用辅助数组保存。
*/
void rotate(int* nums, int numsSize, int k) 
{
	int *temp = (int*)malloc(numsSize * sizeof(int));

	for(int i = 0; i < numsSize; i++)
	{
		temp[(i + k) % numsSize] = nums[i];
	}	

	memcpy(nums, temp, numsSize*sizeof(int));
	    
}

/*
方法2: 在原数组上进行操作。O(1)的空间复杂度。不过是时间复杂度多了。时间换空间。
*/
void rotate2(int* nums, int numsSize, int k) 
{
	int temp;
	for(int i = 1; i <= k; i++)
	{
		temp = nums[numsSize - 1];
		for(int j = numsSize - 1; j >= 1; j--)
		{
			nums[j] = nums[j - 1];
		}
		nums[0] = temp;	
	}   
}

/*
方法3: 在原数组上进行操作。使用循环替换的方法。
*/
void rotate3(int* nums, int numsSize, int k) 
{
	int temp1, temp2;
	int count = 0; //终止循环条件。
	int next;
	for(int i = 0; i < numsSize; i++)
	{
		next = (i + k) % numsSize;
		temp1 = temp2 = nums[i];
		while(next != i && count != numsSize)
		{
			temp1 = nums[next];
			nums[next] = temp2;
			temp2 = temp1;
			next = (next + k)%numsSize; 
			count++;
		}
		if(next == i)
		{
			nums[i] = temp2;
			count++;
		}

		if(count == numsSize)
			break;
	}   
}

int main()
{

	int k = 3;
	int nums[7] = {1,2,3,4,5,6,7};

	rotate3(nums, 7, k);

	for(int i = 0; i< 7; i++)
	{
		printf("%d ", nums[i]);
	}
	printf("\n");

	return 0;
}