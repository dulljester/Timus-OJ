/*
 * 1146.
 * TOPIC: dp, classics
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define oo (1LL<<60)
typedef long long i64;

int n;
i64 c[N][N],row[N][N],col[N][N],h[N],ans;

i64 max( i64 x, i64 y ) { return x<y?y:x; }

i64 f( i64 *x, int n ) {
	int i,j,k,all_negs = 1;
	i64 ans = x[1], s = 0;
	for ( i = 1; i <= n; ++i ) {
		if ( x[i] >= 0 ) all_negs = 0;
		ans = max(ans,x[i]);
	}
	if ( all_negs ) return ans;
	for ( s = 0, i = 1; i <= n; ) {
		if ( s+x[i] <= 0 ) {
			s = 0, ++i;
			continue ;
		}
		if ( (s+=x[i++]) > ans )
			ans = s;
	}
	return ans;
}

int main() {
	int i,j,k;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%lld",&c[i][j]);
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				row[i][j] = row[i][j-1]+c[i][j];
		for ( j = 1; j <= n; ++j )
			for ( i = 1; i <= n; ++i )
				col[i][j] = col[i-1][j]+c[i][j];
		for ( ans = -oo, i = 1; i <= n; ++i )
			for ( j = i; j <= n; ++j ) {
				for ( k = 1; k <= n; ++k )
					h[k] = col[j][k]-col[i-1][k];
				ans = max(ans,f(h,n));
			}
		printf("%lld\n",ans);
	}
	return 0;
}

