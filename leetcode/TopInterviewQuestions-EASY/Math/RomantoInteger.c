/*
Roman to Integer
  Go to Discuss
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/

int romanToInt(char* s) 
{
	int pre = 0; //表示I X C 标志。

	char *p = s;

	int sum = 0;
	while(*p != '\0')
	{
		switch(*p)
		{
			case 'I':
			sum += 1;
			pre = 1;
			break;
			case 'V':
			if(pre == 1)
				sum += 5 - 2*pre;
			else
				sum += 5;
			pre = 5;
			break;
			case 'X':
			if(pre == 1)
				sum += 10 - 2*pre;
			else
				sum += 10;
			pre = 10;
			break;
			case 'L':
			if(pre == 10)
				sum += 50 - 2*pre;
			else
				sum += 50;
			pre = 50;
			break;
			case 'C':
			if(pre == 10)
				sum += 100 - 2*pre;
			else
				sum += 100;
			pre = 100;
			break;
			case 'D':
			if(pre == 100)
				sum += 500 - 2*pre;
			else
				sum += 500;
			pre = 500;
			break;
			case 'M':
			if(pre == 100)
				sum += 1000 - 2*pre;
			else
				sum += 1000;
			pre = 1000;
			break;
		}
		p++;
	}
	return sum;
    
}


//更简洁
    
int convert(char c){
    
    switch(c){
            
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
    
    return 0;
}

int romanToInt(char* s) {
    if( !s ) return 0;
    char *p = s;
    int res = convert(*p);
    char *next = p+1;
    while( *next!='\0') {
        int val_p = convert(*p);
        int val_next = convert(*next);
          
        res += val_next;
          
        if(val_next>val_p)
          res -= 2*val_p;
                  
        next++;
        p++;
    };
          
    return res;
}
