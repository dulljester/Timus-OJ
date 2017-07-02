/*
 * 1029. Ministry
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
#define MAXM (0x80)
#define MAXN (0x200)
typedef long long i64;
#define oo (1LL<<60)
using namespace std;

i64 g[MAXM][MAXN],z[MAXM][MAXN],
	pref[MAXM][MAXN];
int m,n,prev[MAXM][MAXN],out[MAXM*MAXN],*ptr;

i64 sum( int row, int j1, int j2 ) {
	if ( j1 > j2 ) return 0;
	return pref[row][j2]-pref[row][j1-1]; 
}

void dump( int i, int j ) {
	if ( i >= 2 ) {
		dump(i-1,prev[i][j]);
		if ( prev[i][j] != j ) {
			if ( prev[i][j] < j ) 
				for ( int t = prev[i][j]+1; t <= j; ++t )
					*ptr++ = t;
			else for ( int t = prev[i][j]-1; t >= j; --t )
				*ptr++ = t;
		}
	}
	*ptr++ = j;
}

i64 calc_z( int i, int j ) {
	if ( z[i][j] < +oo )
		return z[i][j];
	if ( i == 1 )
		return z[i][j] = g[i][j];
	assert( i >= 2 );
	for ( int t = 1; t <= j-1; ++t ) {
		i64 w = calc_z(i-1,t)+sum(i-1,t+1,j)+g[i][j];
		if ( w < z[i][j] )
			z[i][j] = w, prev[i][j] = t;
	}
	for ( int t = n; t >= j+1; --t ) {
		i64 w = calc_z(i-1,t)+sum(i-1,j,t-1)+g[i][j];
		if ( w < z[i][j] )
			z[i][j] = w, prev[i][j] = t;
	}
	if ( calc_z(i-1,j)+g[i][j] < z[i][j] ) 
		z[i][j] = calc_z(i-1,j)+g[i][j], prev[i][j] = j;
	return z[i][j];
}

int main() {
	int i,j,k;
	for ( ;2 == scanf("%d %d",&m,&n); ) {
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%lld",&g[i][j]);
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				pref[i][j] = pref[i][j-1]+g[i][j];
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; ++j )
				z[i][j] = +oo;
		i64 ans = +oo;
		for ( j = 1; j <= n; ++j )
			if ( calc_z(m,j) < ans )
				ans = calc_z(m,j), k = j;
		ptr = out, dump(m,k);
		for ( i = 0; i < ptr-out-1; ++i )
			printf("%d ",out[i]);
		printf("%d\n",out[i]);
	}
	return 0;
}

