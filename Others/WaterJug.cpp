/*
Description
There are two jugs, a-litres jug and b-litres jug (a, b are positive integers). There is a pump with unlimited water. Given a positive integer c, how to get exactly c litres.
Input
   Line 1: contains positive integers a,   b,  c  (1 <= a, b, c <= 900)
Output
  write the number of steps or write -1 (if no solution found)
Example

Input
6  8  4
Output
4
*/

#include <bits/stdc++.h>
using namespace std;
 
//dfs
int gcd(int a, int b)
{
	if(a == 0) return b;
	return gcd(b%a, a);
}
 
int water_jug(int a, int b, int c)
{
	int from = a;
	int to = 0;
	int count = 1;
	
	// do nuoc tu a sang b cho den khi b day hoac a trong
	// den khi trong 1 trong 2 binh bang c thi dung lai
	while(from != c && to != c)
	{
		int temp = min(from, b - to);
		from = from - temp;
		to = to + temp;
		count++;
		if(from == c || to == c)
			break;
		
		if(from == 0)
		{
			from = a;
			count ++;
		}
		if(to == b)
		{
			to = 0;
			count ++;
		}
	}
	return count;
}

// tinh so buoc nho nhat khi do tu a sang b va tu b sang a 
int minStep(int a, int b, int c)
{
	if(c > max(a, b))
		return -1;
	int UCLN = gcd(a,b);
	if(c % UCLN != 0)
		return -1;
	a = a / UCLN;
	b = b / UCLN;
	c = c / UCLN;
	return min(water_jug(a, b, c), water_jug(b, a, c));
	//return water_jug(b, a, c);
}
 
int main()
{
	int a,b,c;
	cin>>a>>b>>c;
	cout<<minStep(a,b,c);
	return 0;
}
