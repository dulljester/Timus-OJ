/*
 * 1073.
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define tol (1e-13)
#define N (1<<16)
#define oo (1<<30)
using namespace std;

int z[N];

int calc_z( int n ) {
	if ( z[n] < +oo )
		return z[n];
	for ( int k = 1; k*k <= n; ++k )
		if ( calc_z(n-k*k) < +oo && calc_z(n-k*k)+1 < z[n] )
			z[n] = 1+calc_z(n-k*k);
	return z[n];
}

int main() {
	int i,j,k,n;
	for ( z[0] = 0, i = 1; i < N; z[i++] = +oo ) ;
	for  (;1 == scanf("%d",&n); printf("%d\n",calc_z(n)));
	return 0;
}

