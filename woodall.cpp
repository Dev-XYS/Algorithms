/*
Input : X = 383
Output : Yes
For n = 6, Wn = n.2n - 1 = 383.

Input : X = 200
Output : No

*/


// CPP program to check if a number is
// Woodball or not.
#include <bits/stdc++.h>
using namespace std;
 
bool isWoodall(int x)
{
    // If number is even, return false.
    if (x % 2  == 0)
        return false;
 
    // If x is 1, return true.
    if (x == 1)
        return true;
     
    x++;  // Add 1 to make x eve
 
    // While x is divisible by 2
    int p = 0;
    while (x % 2 == 0) {
 
        // Divide x by 2
        x = x/2;
 
        // Count the power
        p++;
 
        // If at any point power and 
        // x became equal, return true.
        if (p == x)
            return true;
    }
 
    return false;
}
 
// Driven Program
int main()
{
    int x = 383;
 
    (isWoodall(x)) ? (cout << "Yes" << endl) : 
                     (cout << "No" << endl);
    return 0;
}
