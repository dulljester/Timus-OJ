/*
 * 1225.
 * TOPIC: dp, matrix powers
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 46
typedef long long i64;
#define oo (1LL<<60)
enum { WHITE, BLUE, RED };
#define A 6
#define enc(x,y) ((x)*3+(y))

i64 g[A][A],ax[A][A],X[A][A],tmp[A][A];
int idx[N],starts_with_blue[N],ends_with_blue[N];

int main() {
	int i,j,k,t,n,x,y,m;
	i64 ans;
	for ( i = 0; i < N; idx[i++] = -1 ) ;
	for ( m = 0, i = WHITE; i <= RED; ++i )
		for ( j = WHITE; j <= RED; ++j )
			if ( i != j ) {
				x = enc(i,j);
				if ( idx[x] == -1 )
					idx[x] = m++;
				if ( j == BLUE ) ends_with_blue[idx[x]] = 1;
				if ( i == BLUE ) starts_with_blue[idx[x]] = 1;
			}
	for ( i = WHITE; i <= RED; ++i )
		for ( j = WHITE; j <= RED; ++j )
			if ( i != j )
				for ( k = WHITE; k <= RED; ++k ) {
					t = j, x = enc(i,j), y = enc(t,k);
					if ( k == t ) continue ;
					x = idx[x], y = idx[y];
					assert( x != -1 && y != -1 && x != y );
					if ( j == BLUE && !(i == WHITE && k == RED || k == WHITE && i == RED) ) 
						continue ;
					assert( j == t && i != j && k != j );
					g[x][y] = 1;
				}

	assert( m == A );
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < A; ++i )
			for ( j = 0; j < A; ++j )
				ax[i][j] = (i==j?1:0), X[i][j] = g[i][j];
		if ( n == 1 ) {
			puts("2");
			continue ;
		}
		if ( n == 2 ) {
			puts("2");
			continue ;
		}
		assert( n >= 3 );
		for ( n -= 2; n; n >>= 1 ) {
			if ( n & 1 ) {
				for ( i = 0; i < A; ++i )
					for ( j = 0; j < A; ++j )
						for ( tmp[i][j] = 0, k = 0; k < A; ++k )
							tmp[i][j] += ax[i][k]*X[k][j];
				for ( i = 0; i < A; ++i )
					for ( j = 0; j < A; ++j )
						ax[i][j] = tmp[i][j];
			}
			for ( i = 0; i < A; ++i )
				for ( j = 0; j < A; ++j )
					for ( tmp[i][j] = 0, k = 0; k < A; ++k )
						tmp[i][j] += X[i][k]*X[k][j];
			for ( i = 0; i < A; ++i )
				for ( j = 0; j < A; ++j )
					X[i][j] = tmp[i][j];
		}
		for ( ans = 0, i = 0; i < A; ++i )
			for ( j = 0; j < A; ++j )
				if ( !starts_with_blue[i] && !ends_with_blue[j] )
					ans += ax[i][j];
		printf("%lld\n",ans);
	}
	return 0;
}

