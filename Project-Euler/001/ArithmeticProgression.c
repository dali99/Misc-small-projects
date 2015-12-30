#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Use:
// bruteforce
// n numbers to calculate (PE 1)
// number #1 to calculate (PE 1000)
// number #2 to calculate
// ...
// number n to calculate

// Prototype
long sum_of_divisible(long divisible, long last);

int main() {
    int n; 
    scanf("%d",&n);
    long arr[n];
    for(int i = 0; i < n; i++){
       scanf("%li",&arr[i]);
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("%li\n", sum_of_divisible(3, arr[i] - 1) + sum_of_divisible(5, arr[i] - 1) - sum_of_divisible(15, arr[i] - 1));
    }
}


// finds the sum of all the numbers divisible by "divisible" up to and including "last" using Arithmetic Progression
long sum_of_divisible(long divisible, long last)
{
    return (long) divisible*(last/divisible)*((last/divisible)+1)/2;
}
