/*
 * 1167. Bicolored Horses
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
#define N 0x200
using namespace std;
enum { W, B };
#define oo (1LL<<60)
typedef long long i64;

i64 z[N][N],pref[2][N];
int n,m,c[N];

i64 f( int i, int j ) {
	return (pref[W][j]-pref[W][i-1])*(pref[B][j]-pref[B][i-1]);
}

i64 calc_z( int n, int m ) {
	int k;
	if ( z[n][m] < +oo )
		return z[n][m];
	if ( m > n ) return +oo;
	if ( m == 1 )
		return z[n][m] = f(1,n);
	if ( n == m )
		return z[n][m] = 0;
	assert( n > m );
	for ( k = 1; k <= n-m+1; ++k )
		if ( calc_z(n-k,m-1) < +oo )
			z[n][m] = min(z[n][m],z[n-k][m-1]+f(n-k+1,n));
	return z[n][m];
}

int main() {
	int i,j,k;
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 1; i <= n; ++i )
			scanf("%d",&c[i]), pref[W][i] = pref[W][i-1]+(c[i]==0?1:0), pref[B][i] = pref[B][i-1]+(c[i]==0?0:1);
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= m; ++j )
				z[i][j] = +oo;
		printf("%lld\n",calc_z(n,m));
	}
	return 0;
}

