/**
mplement strStr()
Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().


*/

#include "stdio.h"

int strStr(char* haystack, char* needle) 
{
	if(needle == NULL)
		return -1;
	if(strlen(haystack) < strlen(needle))
		return -1;
//	if(strcmp(needle, "") == 0) //字符串为空。 （与字符串含一个空格字符 是不一样的）。
//		return 0;
    //或者直接判断为空串
    if(*needle == '\0')
        return 0;

	char * p1 = haystack;
	char * p2 = needle;
	char * start;
	while(*p1 != '\0')
	{
		start = p1;
		p2 = needle;
		while(*p2 != '\0' && *start != '\0')
		{
			if(*p2 == *start)
			{
				p2++;
				start++;
			}
			else
			{
				break;
			}
		}
		if(*p2 == '\0')
			break;
		p1++;
	}

	if(*p2 == '\0')
		return p1 - haystack;
	else
		return -1;
}


int main()
{
    strStr("","");
    return 0;
}

