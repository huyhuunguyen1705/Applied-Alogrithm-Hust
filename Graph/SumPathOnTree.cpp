/*
Given a tree T=(V,E) in which V={1,. . ., n} is the set of nodes. Each edge (u,v) of T has length w(u,v).
Denote f(v) the sum of length of paths from all other nodes to v. Write a program to compute max{f(1), .  . ., f(n)}.
Input
Line 1 contains a positive integer n (2 <= n <= 10^5)
Line i+1 (i=1, . . ., n): contains u, v and w in which w is the weight of the edge (u,v)
Output
Write the value max{f(1), . . , f(n}.
Example
Input
4
1 2 1
1 3 3
3 4 2
Output
13
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

const int MAX = 1e5 + 5;


