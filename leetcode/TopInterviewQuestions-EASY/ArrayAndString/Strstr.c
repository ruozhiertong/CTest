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

// sample 0 ms submission
int strStr(char* pHaystack, char* pNeedle)
{
  char *pHaystackIter = pHaystack, *pNeedleIter = pNeedle;
  char *pOrigin = pHaystack, *pReset = NULL;

  /* If both strings have their first character as NULL
   * then return 0.
   */
  if ( ('\0' == *pHaystack) && ('\0' == *pNeedle) )
    return 0;

  /* Iterate through the "haystack" until there are no
   * more characters to process.
   */
  while ('\0' != *pHaystackIter)
  {
    /* The pointer pNeedleIter represents the current character of
     * needle that is being processed. If the current needle string
     * being processed (pNeedleIter) is at the beginning of the
     * needle string and the head of the needle matches the current
     * character in the haystack then store the address that the
     * haystack is at and increment pNeedleIter to the next character.
     */
    if ( (pNeedleIter == pNeedle) && (*pHaystackIter == *pNeedleIter) )
    {
      pOrigin = pHaystackIter;
      pNeedleIter++;
    }
    else
    {
      /* Store a reset pointer in case we find another starting point
       * for the needle string as pNeedleIter is being processed.
       */
      if (NULL == pReset)
        if (*pHaystackIter == *pNeedle)
          pReset = pHaystackIter;
      
      /* If pNeedleIter matches the haystack then increment pNeedleIter
       * to the next character.
       *
       * If pNeedleIter does not match the current haystack value, then
       * check if there was a reset point found while pNeedleIter was
       * being processed. If there was then reset the haystack to that
       * value - 1. This is because the haystack pointer will be incremented
       * forward at the end of this while loop. At this point we also
       * want to NULL out the reset value. The needle iterator also has
       * to be reset to the start so the new origin point can be calculated
       * once the while loop starts over.
       *
       * If neither of those cases are met then the needle iterator will be
       * reset to the starting point and the haystack iterator does not need
       * to be adjusted.
       */
      if (*pHaystackIter == *pNeedleIter)
      {
        pNeedleIter++;
      }
      else if (NULL != pReset)
      {
        pHaystackIter = pReset - 1;
        pNeedleIter = pNeedle;
        pReset = NULL;
      }
      else
      {
        pNeedleIter = pNeedle;
      }
          
    }
    
    /* Once the end of the needle has been reached return the origin of the needle
     * in the haystack minus the starting point of the haystack to retrieve the
     * starting index of the needle in the haystack.
     */
    if ('\0' == *pNeedleIter)
      return pOrigin - pHaystack;
    
    pHaystackIter++;
  }
  
  /* If the while loop did not find the needle string
   * in the haystack string then return -1.
   */
  return -1;
}

