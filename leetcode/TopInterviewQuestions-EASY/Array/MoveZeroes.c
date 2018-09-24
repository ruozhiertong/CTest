/*

Move Zeroes.
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.

*/

//这个使用双指针最方便。在元素上处理。 在元素上去除某值，使用双指针是很好的选择。 当然使用辅助空间这种比较简单的，更能实现。
void moveZeroes(int* nums, int numsSize) 
{
	int fast = 0, slow = 0;

	for(fast = 0 ; fast < numsSize; fast++)
	{
		if(nums[fast] != 0)
		{
			nums[slow++] = nums[fast];
		}
	}

	for(int i = slow; i < numsSize; i++)
	{
		nums[i] = 0;
	}

}