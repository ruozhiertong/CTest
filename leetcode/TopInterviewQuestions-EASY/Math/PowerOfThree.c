/*

Power of Three
  Go to Discuss
Given an integer, write a function to determine if it is a power of three.

Example 1:

Input: 27
Output: true
Example 2:

Input: 0
Output: false
Example 3:

Input: 9
Output: true
Example 4:

Input: 45
Output: false
Follow up:
Could you do it without using any loop / recursion?

*/

//https://leetcode.com/explore/interview/card/top-interview-questions-easy/102/math/745/discuss
//最愚笨的办法暴力循环。
//看到讨论区的做法，真是amazing啊。 利用log运算。

//3的x次方是n，求x。
bool isPowerOfThree(int n) 
{
	/*
	3^x = n;

	x = log3(n) = lgn /lg3;

	lgx = lgn/3 
    */

    double x = log10(n) / log10(3);

    if((int)x == x)
    	return 1;
    else
    	return 0;


}


class Solution {
public:
    int const Max3PowerInt = 1162261467; // 3^19, 3^20 = 3486784401 > MaxInt32
    int const MaxInt32 = 2147483647; // 2^31 - 1
    bool isPowerOfThree(int n) {
        if (n <= 0 || n > Max3PowerInt) return false;
        return Max3PowerInt % n == 0;
    }
};