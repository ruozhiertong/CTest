/*
Hamming Distance
  Go to Discuss
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.

*/


int hammingDistance(int x, int y) 
{
	int count = 0;
	int mask = 1;

	while((mask <= x) || (mask <= y))
	{
		if((x & mask) != (y & mask)) //注意运算优先级。
			count++;
		mask <<= 1;
        if(mask == (1<<31)) //注意这里1<<31 显示时-1，所以要注意不是大于 小于。
            break;
	}
    return count;
    
}

int main()
{
    hammingDistance(1577962638,
                    1727613287);
    return 0;
}



//使用异或运算。
int hammingDistance(int x, int y) {    
    int dist = 0;
    
    x ^= y;
    while(x)
    {
        dist += x & 1;
        x >>= 1;
    }
    
    return dist;
}