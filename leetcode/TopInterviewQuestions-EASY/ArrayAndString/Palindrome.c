/*
Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false


Last executed input:
".,"

*/


//双指针:双向指针处理
bool isPalindrome(char* s) 
{
	if(*s == '\0') //we define empty string as valid palindrome.
		return 1;

	char *p = s;
	// while(*p != '\0') //判断是否都是非字母组成。
	// {
	// 	if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
	// 		break;
	// 	p++;
	// }
	// if(*p == '\0')
	// 	return 0;

	while(*p != '\0') 
	{
		if(*p >= 'A' && *p <= 'Z') // to lowcase
			*p += 32;
		p++;
	}
    int len = strlen(s);
    int start = 0;
    int end = len - 1;
    int allNonChar = 1;

    while(start < end)
    {
    	while(start < end && !((s[start] >= '0' && s[start] <= '9') || (s[start] >= 'a' && s[start] <= 'z') || (s[start] >= 'A' && s[start] <= 'Z')))
    		start++;
		while(start < end && !((s[end] >= '0' && s[end] <= '9') || (s[end] >= 'a' && s[end] <= 'z') || (s[end] >= 'A' && s[end] <= 'Z')))
    		end--;
    	if(s[start++] != s[end--])
    		return 0;
    }

    return 1;

}