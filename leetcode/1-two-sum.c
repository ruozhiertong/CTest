#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) 
{
	int *result = (int*)malloc(numsSize*sizeof(int));
	int resultSize = 0;
	for(int i = 0; i < numsSize; i++)
	{
		for(int j = i +1; j< numsSize; j++)
		{
			if(nums[i] + nums[j] == target)
			{
				if(checkIndex(result, resultSize, i, j) == 1)
					continue;
				result[resultSize++] = i;
				result[resultSize++] = j;
				break;
			}
		}
	}
	return result;    
}

int checkIndex(int *result , int size, int a, int b)
{
	int flag = 0;
	for(int i = 0; i < size; i++)
	{
		if(result[i] == a || result[i] == b)
		{
			flag = 1;
			break;
		}	
	}
	return flag;
}

int main()
{

	int nums[4];
	int target;
	printf("input 4 nums \n");

	for(int i = 0; i < 4; i++)
	{
		scanf("%d",&nums[i]);
	}

	printf("input target \n");

	scanf("%d", &target);

	int * result = twoSum(nums, 4, target);

	for(int i = 0; i< 4; i++)
	{
		printf("%d \n", result[i]);
	}


}