/*
Pascal's Triangle
  Go to Discuss
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

//杨辉三角

/**
 * Return an array of arrays.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int** columnSizes) 
{
	int **result = (int**)malloc(sizeof(int*) * numRows);
	*columnSizes = (int*)malloc(sizeof(int) * numRows);
	for(int i = 0; i < numRows; i++)
	{
		result[i] = (int *)malloc(sizeof(int) * (i+1));
		(*columnSizes)[i] = (i+1);
		for(int j =0 ; j <= i; j++)
		{
			if(j == 0 || j == i)
				result[i][j] = 1;
			else
				result[i][j] = result[i - 1][j - 1] + result[i -1][j];
		}
	} 

	return result;
    
}


int main()
{
	int ** result;
	int *columnSizes; //数组,存放每行个数的数组。
	generate(3,&columnSizes);
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0 ; j < columnSizes[i]; j++)
		{
			printf("%d ", result[i][j]);
		}
	}
}