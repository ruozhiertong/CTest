/*

Climbing Stairs
  Go to Discuss
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.

Example 1:

Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step


*/

//利用 动态规划， 分解成子问题，
//适合于用动态规划法求解的问题，经分解后得到的子问题往往不是互相独立的（即下一个子阶段的求解是建立在上一个子阶段的解的基础上，进行进一步的求解）。


// 第n步 可以由1步， 或2步前进得到。
//递归。 可能有时间限制。  还有可能有空间限制的问题。利用备忘录进行保存先前结果(还是会有问题)。
int climbStairs(int n) 
{
	int *memo = (int *)malloc(sizeof(int) * n);
	memset(memo, -1, sizeof(int) * n);
	int count = f(n , memo);
	free(memo);
	return count;
}

int f(int n, int * memo)
{
	if(memo[n -1] != -1)
		return memo[n -1];

	if(n == 1)
	{
		memo[n -1] = 1;
		return memo[n -1];
	}
    if(n == 2)
    {
    	memo[n - 1] = 2;
    	return memo[n -1];
    }
    memo[n -1] = climbStairs(n - 1) + climbStairs(n -2);
    return memo[n -1];
}

//非递归。
int climbStairs2(int n) 
{
	if (n == 1) 
	{
		return 1;
	}
	int *memo = (int *)malloc(sizeof(int) * n);
	memo[0] = 1;
	memo[1] = 2;
	for (int i = 2; i < n; i++) 
	{
		memo[i] = memo[i - 1] + memo[i - 2];
	}
	return memo[n - 1];
}

