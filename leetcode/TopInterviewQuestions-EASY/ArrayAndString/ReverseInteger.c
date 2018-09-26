/*

Reverse Integer.

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21


*/
//注意溢出值的计算。
//方式1 用long存储结果，判断是否[−2^31,  2^31 − 1]。注意数值边界情况(卡在这个上面很久)。
//方式2 用INT_MAX 判断
int reverse(int x) 
{
    printf("%d %d\n",sizeof(int), sizeof(long));
    long input = x;
	long result = 0;
	int symbol = input >= 0? 1: -1; //正负号。

	input *= symbol;

	while(input != 0)
	{
		result =  result * 10 + (input%10);
		input /= 10;
	}

	if(symbol == -1)
    {
        if(result > 0x7fffffff) //2^31
            return 0;
        
    }
	else
    {
        if(result >= 0x7fffffff) // 2^31-1
        return 0;
    }
		

	return result*symbol;
}

int main()
{
    printf("%d\n", reverse(-2147483648));
    return 0;
}

/*

//这个方法 有意思。
public class ReverseInteger {

    public int reverse(int x) {
        int input = x;
        long output = 0;

        while (input != 0) {
            output = output * 10 + input % 10;
            input = input / 10;
        }

        return (int) output == output ? (int) output : 0;
    }

}
*/