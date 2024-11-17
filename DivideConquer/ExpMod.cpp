/*
Description
Given two positive integers a and b. Compute a^b mod (10^9 + 7)
Input
One line contains two integers a and b (1 <= a,b <= 18446744073709551614)
Output
The value a^b mod (10^9+7)
Example
Input
2  3
Output
8
*/
/*
In some testcase a,b are very large: 18446744073709551614 18446744073709551614
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const long long MOD_EXPONENT = MOD - 1; // 10^9 + 6

// Function to compute b % MOD_EXPONENT when b is represented as a large string
long long largeModulus(const string &str, long long mod) {
    long long result = 0;
    for (char digit : str) {
        result = (result * 10 + (digit - '0')) % mod;
    }
    return result;
}

// Iterative function to perform modular exponentiation
long long expmod(long long a, long long b) {
    long long result = 1;
    a = a % MOD;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % MOD;
        }
        a = (a * a) % MOD;
        b /= 2;
    }
    return result;
}

int main() {
    string a_str,b_str;  // Read b as a string to handle large values
    cin >> a_str >> b_str;

    // Calculate b % (MOD - 1) using the largeModulus function
    long long a_mod = largeModulus(a_str, MOD);
    long long b_mod = largeModulus(b_str, MOD_EXPONENT);

    // Compute a^b_mod % MOD
    cout << expmod(a_mod, b_mod) << endl;
    return 0;
}
