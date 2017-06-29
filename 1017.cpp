/*
 * 1017. Stairs
 * TOPIC: dp, Young Tableaux
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
using namespace std;
typedef long long i64;
#define N 0x200
#define oo (1LL<<60)

int n;
i64 z[N][N];

i64 calc_z( int m, int k ) {
	int t;
	if ( z[m][k] < +oo )
		return z[m][k];
	if ( m == k ) 
		return z[m][k] = 1;
	assert( m >= 1 && k >= 1 && k < m );
	for ( z[m][k] = 0, t = k+1; t <= m-k; ++t )
		if ( calc_z(m-k,t) < +oo )
			z[m][k] += calc_z(m-k,t);
	return z[m][k];
}

int main() {
	int i,j,k;
	i64 ans;
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j )
			z[i][j] = +oo;
	for ( ;1 == scanf("%d",&n); ) {
		for ( ans = 0, k = 1; k <= n; ++k )
			ans += calc_z(n,k);
		printf("%lld\n",ans-1);
	}
	return 0;
}

