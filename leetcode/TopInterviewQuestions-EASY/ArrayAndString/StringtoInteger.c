/*
String to Integer (atoi)

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
Example 1:

Input: "42"
Output: 42
Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.


*/
#include <stdio.h>

int myAtoi(char* str) 
{
    //santy check
	if(str == NULL)
		return 0;
    char * p = str;
    //skip whitespace.
    while(*p ==' ' && *p != '\0')
    {
    	p++;
    }
    if(*p == '\0')
    	return 0;

    if(*p != '+' &&  *p != '-' && !(*p >= '0' && *p <= '9') ) //first char
    	return 0;
    
    //end santy check

    int symbol = 1;
    long result = 0;
    if(*p == '+')
    {
    	symbol = 1;
    	p++;
    }else if(*p == '-')
    {
    	symbol = -1;
    	p++;
    }

    while(*p >= '0' && *p <= '9')
    {
    	result = result *10  + (*p - '0');
        
        if(result > 0x80000000) //2^31 避免数值也超过了long的长度，因此只要超过Int的长度时就可以break了。
            break;
        p++;
    }
    //result 此时是绝对值。
    //INT_MAX (2^31 − 1) or INT_MIN (−2^31)
    if(symbol == 1)
    {
        if(result > 0x7fffffff) //MAX 2^31 -1
            result = 0x7fffffff;
    }
    else
    {
        if(result > 0x80000000) //2^31
            result = 0x80000000;
    }
    
    return result*symbol;
}

int main()
{
    //测试 补码+1后的值。 int 溢出。
    
    printf("%d\n", myAtoi("9223372036854775808"));
    
    int i = 0;
    
    printf("%d\n", i); //0
    
    i = 0x7fffffff;
    
    printf("%d\n", i); //2147483647 补码 0x7fffffff.
    
    i++;            //补码 0x7fffffff + 1 ==> 补码 0x80000000.
    
    printf("%d \n", i); //-2147483648.  补码中：0x80000000 不是-0，是-2^n(n为int的位数),-2147483648。 因为补码0x80000000 的原码是 先-1再取反 为 100000000 本来这个原码是表示-0（原码和反码对0有两种表示，+0 ，-0）， 在补码系统中规定-0 表示为-2^n.(所以补码中，0 只有一个一个表示，而且补码表示的数的个数比原码，反码多1个，即数-2^n。)
    
    //原码 反码表示范围 [-2^n -1, 2^n -1] , 0有两种表示 +0， -0。
    //补码表示的范围 [-2^n, 2^n -1] , 0 只有一种表示。
    //当然上面都是对于有符号类型的。 对于无符号性，由于都是正数，因此都是原码 反码 补码都是一样的。
    i++;
    
    printf("%d \n", i); //-2147483647
    
    i = 0xffffffff;
    
    printf("%d\n",i);
    
    i++;
    
    printf("%d\n",i);
    
    
    
    
    return 0;
}
