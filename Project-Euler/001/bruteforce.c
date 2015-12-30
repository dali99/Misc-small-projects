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

int main() {
    int n; 
    scanf("%d",&n);
    long arr[n];
    for(int i = 0; i < n; i++){
       scanf("%li",&arr[i]);
    }
    
    for (int i = 0; i < n; i++)
    {
        long sum = 0;
        for (long j = 1; j < arr[i]; j++)
        {
            if (j % 3 == 0 || j % 5 == 0)
                sum += j;
        }
        printf("%li\n", sum);
    }
}
