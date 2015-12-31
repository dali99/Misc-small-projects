#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Use:
// bruteforce
// n numbers to calculate (PE 1)
// number #1 to calculate (PE 4000000)
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
        long sum = 2;
        int a = 1, b = 2;
        while (1)
        {
            int c = a + b;
            a = b;
            b = c;
            if (b > arr[i])
                break;
            if (b % 2 == 0)
            {
                sum += b;
            }
        }
        printf("%li\n", sum);
    }
    
}
