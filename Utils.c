#include "include/Utils.h"

/**
 * @brief Function to find maximum int in arr[] of size n
 * 
 * @param arr array
 * @param n   number of elements in array
 * @return int largest number in array
 */
int largest(int arr[], int n)
{
    int i;
    
    // Initialize maximum element
    int max = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}

/**
 * @brief Sees if array is sorted
 * 
 * @param s array
 * @param n number os elements in array
 * @return int - tells if an array is sorted, and if so, in wich direction
 */
int isArraySorted(int s[], int n) {
    int a = 1, d = 1, i = 0;

    while ((a == 1 || d == 1) && i < n - 1) {
        if (s[i] < s[i+1])
            d = 0;
        else if (s[i] > s[i+1])
            a = 0;
        i++;
    }

    if (a == 1)
        return 1;
    else if (d == 1)
        return 2;
    else
        return 0;
}