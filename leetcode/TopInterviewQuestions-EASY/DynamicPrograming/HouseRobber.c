/*
House Robber
  Go to Discuss
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

*/

//https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/576/discuss/156523/From-good-to-great.-How-to-approach-most-of-DP-problems.

//使用DP， 关键还是要找出子问题的递归形式。
//rob(i) = max(rob(i-1) , rob(i-2) + nums[i]) . rob(i) means the max value after rob i-th house。
int rob(int* nums, int numsSize) 
{
	if(numsSize == 1)
		return nums[0];

	int *dp = (int *)malloc(sizeof(int) * numsSize);

	dp[0] = nums[0];

	if(nums[1] > nums[0])
		dp[1] = nums[1];
	else
		dp[1] = nums[0];

	for(int i = 1; i< numsSize; i++)
	{
		dp[i] = dp[i-1] > dp[i-2] + nums[i] ? dp[i-1]:dp[i-2] + nums[i];
	}
	int res = dp[numsSize - 1];
	free(dp);
	return res;
    
}             