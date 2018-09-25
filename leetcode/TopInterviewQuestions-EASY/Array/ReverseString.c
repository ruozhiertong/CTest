/*

Reverse String.

Write a function that takes a string as input and returns the string reversed.

Example 1:

Input: "hello"
Output: "olleh"
Example 2:

Input: "A man, a plan, a canal: Panama"
Output: "amanaP :lanac a ,nalp a ,nam A"

"Delia sailed
Eva waved
Elias ailed."

*/

//方法1：双向指针处理(知道首尾指针)。首尾交换。
char* reverseString(char* s) 
{
	int len = strlen(s) - 1;
	char temp; 
	for(int i = 0; i < len; i++)
	{
		temp = s[i];
		s[i] = s[len];
		s[len] = temp;
		len--;
	}
    printf("%s\n",s);
	return s;
}

//方法2：从尾部循环到首部。
char* reverseString2(char* s) 
{
	int len = strlen(s);
    printf("%d\n", len);
 	char *result = (char*)malloc(sizeof(char)*(len + 1));
 	int i = 0;
	while(len >= 0)
	{
        printf("%c\n",s[len]);
		result[i++] = s[--len];
	}
	result[i] = '\0';
    printf("%s\n",result);
	return result;
}