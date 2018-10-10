/*
Maximum Subarray
  Go to Discuss
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

*/

//方法1：暴力法。 从1个元素集合 到 n个元素集合，从而判断哪个子集最大。 但是非常耗时。O(n^3)
int maxSubArray(int* nums, int numsSize) {
    
    int max = nums[0];
	int *arr = (int *)malloc(sizeof(int)* numsSize);
	int arrSize = 0;
	int sum = 0;
	for(int len = 1; len <= numsSize ; len++)
	{
		int start = 0;
		while(start < numsSize)
		{
            sum = 0;
			for(int i = start; i < start + len && i < numsSize; i++)
			{
				sum += nums[i];
			}
			if(sum > max)
			{
				max = sum;
				arrSize = len;
				for(int i = 0 ; i < len; i++)
				{
					arr[i] = nums[start+i];
				}
			}
			start++;
		}
	}
	for(int i =0 ; i < arrSize; i++)
	{
		printf("%d\n", arr[i]);
	}
	free(arr);
	return max; 
}

//方法2：使用DP思想。
//https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/566/discuss/20193/DP-solution-and-some-thoughts
//非常巧妙的想法。dp[i] 表示以 nums[i]为结尾的集合的最大值的那个集合。
//关键的 状态转移方程 dp[i] = nums[i] + (dp[i -1] > 0? dp[i -1]: 0) ， 如果知道用动归，那么关键要找出子问题的结构。
int maxSubArray(int* nums, int numsSize) 
{
	int *dp = (int *)malloc(sizeof(int)* numsSize);
	dp[0] = nums[0];
	int max = dp[0];


	for(int i = 1; i < numsSize; i++)
	{
		dp[i] = nums[i] + (dp[i -1] > 0? dp[i -1]: 0);

		if(dp[i] > max)
			max = dp[i];
	}

	free(dp);
	return max;

}
