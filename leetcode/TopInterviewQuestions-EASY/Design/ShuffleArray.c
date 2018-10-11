/*



Shuffle an Array
  Go to Discuss
Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();


*/

typedef struct {
  int *original;
  int *shuffle;
  int arraySize;  
} Solution;

Solution* solutionCreate(int* nums, int size) 
{
	srand((int)time(0));
    Solution * sl = (Solution*)malloc(sizeof(Solution));
    sl->original = (int*)malloc(sizeof(int) * size);
    sl->shuffle = (int*)malloc(sizeof(int) * size);
    sl->arraySize = size;
    memcpy(sl->original , nums, sizeof(int) * size);
    return sl;

}

/** Resets the array to its original configuration and return it. */
int* solutionReset(Solution* obj, int *returnSize) {
    *returnSize = obj->arraySize;
    return obj->original;
}

/** Returns a random shuffling of the array. */
int* solutionShuffle(Solution* obj, int *returnSize) 
{
	*returnSize = obj->arraySize;
	memcpy(obj->shuffle, obj->original, sizeof(int)*(obj->arraySize));
	int temp;
	int index;
	for(int i = obj->arraySize - 1; i > 0; i--)
	{
		index = rand()%(i+1); // [0,1)
		temp = obj->shuffle[i];
		obj->shuffle[i] = obj->shuffle[index];
		obj->shuffle[index] = temp;
	}

	return obj->shuffle;   
}

void solutionFree(Solution* obj) {

	free(obj->original);
	free(obj->shuffle);
	free(obj);
    
}

/**
 * Your Solution struct will be instantiated and called as such:
 * struct Solution* obj = solutionCreate(nums, size);
 * int* param_1 = solutionReset(obj);
 * int* param_2 = solutionShuffle(obj);
 * solutionFree(obj);
 */