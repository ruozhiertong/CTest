/*
Count and Say

The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

 

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

*/
#include "stdio.h"

//这个用递归方式比较简单些。
//其实注意点在于动态的扩展内存。  如果用java 直接string 类型就不会那么麻烦复杂了。
char* countAndSay(int n) 
{
    int size = 200;
	char *result = (char*)malloc(sizeof(char)*size); //max len: n*2
	char *temp = (char*)malloc(sizeof(char)*size);  //保存上一个序列。
	for(int i = 1; i <= n; i++)
	{
		int index = 0;
		if(i == 1)
			result[index++] = '1';
		else
		{
			int count = 1;
			char *p = temp;
			char *next = p + 1;
			while(*next != '\0')
			{
				if(*p != *next)
				{
					if(index == size)
					{
                        size *= 2;
						result = (char*)realloc(result, size);
					}
					result[index++] = count + '0';
					count = 1;
                    if(index == size)
                    {
                        size *= 2;
                        result = (char*)realloc(result, size);
                    }
					result[index++] = *p ;
				}
				else
				{
					count++;
				}
				p = next;
				next = p + 1;
			}

            if(index == size)
            {
                size *= 2;
                result = (char*)realloc(result, size);
            }
			result[index++] = count + '0';
            if(index == size)
            {
                size *= 2;
                result = (char*)realloc(result, size);
            }
			result[index++] = *p;
		}
        if(index == size)
        {
            size *= 2;
            result = (char*)realloc(result, size);
        }
		result[index] = '\0';
        printf("%d\n", strlen(result));
		temp = (char*)realloc(temp, size);
		strcpy(temp , result);
	}
	free(temp);
	return result;
}


int main()
{
    for (int i = 1; i <= 30; i++)
    {
        printf("%s\n", countAndSay(i));
    }
    return 0;
}

