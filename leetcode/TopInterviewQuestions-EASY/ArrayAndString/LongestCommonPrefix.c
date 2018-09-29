/*

Longest Common Prefix


Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
Note:

All given inputs are in lowercase letters a-z.

*/

//这题注意点也主要是在动态增长内存上。
char* longestCommonPrefix(char** strs, int strsSize) 
{
	int size = 100;
	char * result = (char*)malloc(size);
    
    int minLen = strlen(strs[0]);
    int minLenIndex = 0;
    //优化，选取最短的字符串进行遍历。
    for(int i = 1; i < strsSize; i++)
    {
        if(strlen(strs[i]) < minLen)
        {
            minLen = strlen(strs[i]);
            minLenIndex = i;
        }
    }

	char *p = strs[minLenIndex];
	int index = 0;
	while(*p != '\0')
	{
		int flag = 1;
		for(int i = 0; i < strsSize; i++)
		{
            if(i == minLenIndex)
                continue;
			if(*p != strs[i][index])
			{
				flag = 0;
				break;
			}
		}
		if(flag == 0)
			break;
		if(index == size)
		{
			size *= 2;
			result = (char*)realloc(result , size);
		}
		result[index] = *p;
		p++;
		index++;
	}
	result[index] = '\0';
	return result;
    
}

int  main()
{
	return 0;
}