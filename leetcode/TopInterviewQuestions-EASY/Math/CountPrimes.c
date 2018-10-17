/*

Count Primes
  Go to Discuss
Count the number of prime numbers less than a non-negative number, n.

Example:

Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

*/

int isPrime(int n)
{
	for(int i= 2; i*i <= n; i++)
	{
		if(n % i == 0)
			return 0;
	}
	return 1;
}

int countPrimes(int n) 
{
	int count = 0;
	for(int i = 2; i < n; i++)
	{
		if(isPrime(i) == 1)
			count++;
	}
	return count;
}


//效率高的做法。
int countPrimes(int n){
    if(n<=2)
        return 0;
    
    bool *isPrime=malloc(sizeof(bool)*n);
    memset(isPrime, true, n);
    
    int primeCount = 1;
    
    for(int i=3; i<n; i+=2){
        if(isPrime[i]){
            primeCount++;
            for(int j=i;j<n;j+=i){
                isPrime[j]=false;
            }
        }
    }
     return primeCount;
}