/*
Valid Anagram.
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?


*/
//方法1：s t排序，排序后如果相同，return true。
//方法2：计数判断。https://www.cnblogs.com/ganganloveu/p/4694703.html
//方法3：使用hashtable。
//方法4：相同的置为\0 . 就是效率不高。

//方法4. 
bool isAnagram(char* s, char* t) 
{
	  int len1 = strlen(s);
	  int len2 = strlen(t);
	  if (len1 != len2)
	  	return 0;

	  for(int i = 0; i < len1; i++)
	  {
	  	for(int j = 0; j < len2 ; j++)
	  	{
	  		if(s[i] == t[j])
	  		{
	  			t[j] = '\0';
	  			break;
	  		}
	  	}
	  }

	  for(int i =0; i < len2; i++)
	  {
	  	if(t[i] != '\0')
	  		return 0;
	  }
	  return 1;
}