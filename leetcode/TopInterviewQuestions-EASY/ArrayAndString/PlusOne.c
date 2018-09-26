/*
 Plus One.
Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
 //注意进位
int* plusOne(int* digits, int digitsSize, int* returnSize) 
{

	int* result = (int *)malloc((digitsSize+1)*sizeof(int));

	int carry = 1;

	for(int i = digitsSize - 1; i >= 0; i--)
	{
		if(digits[i] + carry == 10)
		{
			digits[i] = 0;	
			carry = 1;
		}
		else
		{
			digits[i] += carry;
			carry = 0;
			break;
		}
	}
	if(carry == 1)
	{
		result[0] = 1;
		memcpy(result + 1, digits, digitsSize * sizeof(int));
		*returnSize = digitsSize + 1;	
	}
	else
	{
		memcpy(result, digits, digitsSize * sizeof(int));
		*returnSize = digitsSize;
	}

	return result;
}