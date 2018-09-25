/*
Rotate Image.

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
*/


//思路。
//矩阵的转置。 B的第i行第j列元素是A的第j行第i列元素
//这个题目不是转置，而是整体顺时针旋转90度。
//因此这个题目可以转换为坐标旋转。
/*
[x′
 y′]=[cosθ sinθ     [x
     −sinθ cosθ] ∗   y]

x′=xcosθ−ysinθ
y′=xsinθ+ycosθ

先顺时针90度，再平移。

*/

void rotate0(int** matrix, int matrixRowSize, int *matrixColSizes) 
{
	//二维数组 动态的malloc。
	int **result = (int**)malloc(matrixRowSize * sizeof(int*));
	int x , y;
	for(int i = 0; i < matrixRowSize; i++)
	{
		result[i] =(int *)malloc(matrixColSizes * sizeof(int));
	}

    //当然直接使用辅助空间就简单。
	//就地解决的。 不用辅助空间。 从外圈到内圈转换。
	for(int i = 0; i < matrixRowSize; i++)
	{
		for(int j =0 ; j< matrixColSizes; j++)
		{
			x = (i+1) * 0 - (j+1) * (-1);
			y = (i+1) * (-1) + (j+1) * 0 + 1 + matrixRowSize;
			result[x -1][y-1] = matrix[i][j];

		}
	}

	for(int i = 0; i < matrixRowSize; i++)
	{
		for(int j =0 ; j< matrixRowSize; j++)
		{
			printf("%d ", result[i][j]);
			matrix[i][j] = result[i][j];
		}
		printf("\n");
	}
	//memcpy(matrix, result, sizeof(int) * matrixRowSize * matrixColSizes);
}
void rotate(int** matrix, int matrixRowSize, int *matrixColSizes) 
{
	int startX;
	int startY;
	int nextX, nextY , currentX, currentY;
	int temp1, temp2;
	//就地解决的。 不用辅助空间。 从外圈到内圈转换。 圈数 matrixRowSize /2. 每圈循环替换。
	for(int i = 0; i < matrixRowSize /2; i++)
	{

		for(int j = i; j < matrixRowSize - i -1; j++)
		{
            printf("%d %d\n", i, j);
			startX = i;
			startY = j;
			currentX  = i;
			currentY = j;
			temp1 = matrix[currentX][currentY];
			do
			{
                //printf("currentX:%d,currentY:%d,startx:%d,starty:%d\n",currentX, currentY,startX, startY);
				nextX = (currentX+1) * 0 - (currentY+1) * (-1) - 1;
				nextY = (currentX+1) * (-1) + (currentY+1) * 0 + 1 + matrixRowSize - 1;
				temp2 = matrix[nextX][nextY];
				matrix[nextX][nextY] = temp1;
				currentX = nextX;
				currentY = nextY;
				temp1 = temp2;
			}while( !(currentX == startX && currentY == startY));
		}
	}
		

	for(int i = 0; i < matrixRowSize; i++)
	{
		for(int j =0 ; j< matrixRowSize; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void rotate2(int** matrix, int matrixRowSize, int *matrixColSizes) {
    int i, j;
    int n = matrixRowSize;
    int d = n/2;
    for(i=0; i<d; i++) {    //ring
        for(j=i; j<n-1-i; j++) {  //row
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n-1-j][i];
            matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
            matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
            matrix[j][n-1-i] = temp;
        }
    }
}

//相关性质可用三角形全等证明
void rotate3(int** matrix, int matrixRowSize, int *matrixColSizes) {
    int h,l,temp,i,j;
    h=matrixRowSize;
    l=matrixColSizes[0];
    printf("h,l:%d,%d\n",h,l);
    if(l!=h)
        printf("error");
    for(i=0;i<h-1;i++)  //关于次对角线对阵，对角线上元素不用管
    {
        for(j=0;j<l-i-1;j++)
        {
            temp=matrix[i][j];
            matrix[i][j]=matrix[l-1-j][l-1-i];
            matrix[l-1-j][l-1-i]=temp;
        }
    }
    for(i=0;i<=(h-1)/2;i++)  //关于横中位线对称
    {
        for(j=0;j<l;j++)
        {
            temp=matrix[i][j];
            matrix[i][j]=matrix[h-1-i][j];
            matrix[h-1-i][j]=temp;
        }
    }
    return;
}


