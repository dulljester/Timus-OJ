/*
 * TOPIC: dp
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
#define N (100100)
#define oo (1<<30)
using namespace std;

int n,c[N],
	z[2][N];

int main() {
	int i,j,k,ii,jj;
	for ( ;2 == scanf("%d %d",&ii,&jj); ) {
		n = jj-ii+1;
		for ( i = 1; i <= n; ++i )
			scanf("%d",&c[i]), z[0][i] = z[1][i] = +oo;
		for ( z[0][1] = z[1][1] = 1, i = 2; i <= n; ++i ) {
			if ( z[0][i-1] < +oo && c[i-1] <= c[i] )
				z[0][i] = min(z[0][i],z[0][i-1]);
			if ( z[1][i-1] < +oo && c[i-1] >= c[i] )
				z[1][i] = min(z[1][i],z[1][i-1]);
			if ( z[0][i-1] < +oo )
				z[1][i] = min(z[1][i],1+z[0][i-1]);
			if ( z[1][i-1] < +oo )
				z[0][i] = min(z[0][i],1+z[1][i-1]);
			if ( z[0][i-1] < +oo )
				z[0][i] = min(z[0][i],1+z[0][i-1]);
			if ( z[1][i-1] < +oo )
				z[1][i] = min(z[1][i],1+z[1][i-1]);

		}
		printf("%d\n",min(z[0][n],z[1][n]));
	}
	return 0;
}

