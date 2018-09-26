/*
First Unique Character in a String.

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

*/


int firstUniqChar(char* s) 
{
	char *p1 , *p2;
	int unique = 1;
	p1 = s;
	while(*p1 != '\0')
	{
		p2 = s;
		unique = 1;
		while(*p2 != '\0')
		{
			if(p1!= p2 && *p1 == *p2)
			{
				unique = 0;
				break;
			}
			p2++;
		}
		if(unique)
			break;
		p1++;
	}
	if(*p1 == '\0')
		return -1;
	else
		return p1 - s;   
}