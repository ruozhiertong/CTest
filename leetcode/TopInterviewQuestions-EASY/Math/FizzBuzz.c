/*
Fizz Buzz
  Go to Discuss
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]


*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) 
{

	char ** result =(char**)malloc(sizeof(char *)* n);
	int count = 0;

	for(int i = 1 ; i <= n ; i++)
	{
		if(i%3 == 0 && i % 5 == 0)
		{
			result[count] = malloc(sizeof(char)*9);
			strcpy(result[count],"FizzBuzz");
			count++;
		}
		else if(i % 3 == 0)
		{
			result[count] = malloc(sizeof(char)*5);
			strcpy(result[count],"Fizz");
			count++;
		}else if(i % 5 == 0)
		{
			result[count] = malloc(sizeof(char)*5);
			strcpy(result[count],"Buzz");
			count++;
		}else
		{
			sprintf(result[count] , "%d", i);
			count++;
		}
	}
	*returnSize = count;
    return result;
}




char** fizzBuzz(int n, int* returnSize) {
    char **res = (char **) malloc(n * sizeof(char *));
    memset(res, 0x00, n * sizeof(char *));
    int i;
    char *a = "Fizz";
    char *b = "Buzz";
    char *c = "FizzBuzz";

    for (register int i = 1; i != n + 1; i++) {
        if (i * 5 <= n) {
            res[i * 5 - 1] = b;
        }
        if (i * 3 <= n) {
            res[i * 3 - 1] = res[i * 3 - 1] == NULL ? a : c;
        }
        if (res[i - 1] == NULL) {
            res[i - 1] = malloc(10);
            memset(res[i - 1], 0, 10);
            register int j = i;
            
            int k; //数字位数。
            if (i < 10) k = 1;
            else if (i < 100) k = 2;
            else if (i < 1000) k = 3;
            else if (i < 10000) k = 4;
            else if (i < 100000) k = 5;
            
            k--;

            while(j > 0) {
                res[i - 1][k] = (j % 10) + '0';
                j = j / 10;
                k = k - 1;
            }
        }
    }
    *returnSize = n;
    return res;
}
