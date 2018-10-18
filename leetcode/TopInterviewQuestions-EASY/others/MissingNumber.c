/*

Missing Number
  Go to Discuss
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?


*/

//第一想到的就是：排序。 排完序后，如果第一次 相应位置上不是对应相应的数字，那么该位置就是missing。 不过时间复杂度不是O(n)。
//第二想法： 使用和nums一样的额外数组。遍历nums，将数字放到额外数组的相应位置。 不过空间复杂度是O(n)。
//第三： 因为放置的是互不相同的数字，而且是0...n 的， 全部相加 减去.
int missingNumber(int* nums, int numsSize) 
{
	int sumMiss = 0;
	int sumRight = 0;
    for(int i = 0; i < numsSize;i++)
    {
    	sumRight += i;
    	sumMiss += nums[i];
    }

    return numsSize - (sumMiss - sumRight);
}

//第四： 使用xor操作。
/*

Approach #3 Bit Manipulation [Accepted]
Intuition

We can harness the fact that XOR is its own inverse to find the missing element in linear time.

Algorithm

Because we know that nums contains nn numbers and that it is missing exactly one number on the range [0..n-1][0..n−1], we know that nn definitely replaces the missing number in nums. Therefore, if we initialize an integer to nn and XOR it with every index and value, we will be left with the missing number. Consider the following example (the values have been sorted for intuitive convenience, but need not be):

Index	0	1	2	3
Value	0	1	3	4
\begin{aligned} missing &= 4 \wedge (0 \wedge 0) \wedge (1 \wedge 1) \wedge (2 \wedge 3) \wedge (3 \wedge 4) \\ &= (4 \wedge 4) \wedge (0 \wedge 0) \wedge (1 \wedge 1) \wedge (3 \wedge 3) \wedge 2 \\ &= 0 \wedge 0 \wedge 0 \wedge 0 \wedge 2 \\ &= 2 \end{aligned} 
missing
​	
  
=4∧(0∧0)∧(1∧1)∧(2∧3)∧(3∧4)
=(4∧4)∧(0∧0)∧(1∧1)∧(3∧3)∧2
=0∧0∧0∧0∧2
=2
​	


*/

