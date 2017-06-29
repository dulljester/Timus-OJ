/*
 * 1900. Brainwashing Device
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
typedef long long i64;
using namespace std;
#define oo (1LL<<60)

int n,m,c[N][N],prev[N][N];
i64 pref[N][N],z[N][N];

i64 sum( const int x, int i, int j ) { return pref[x][j]-pref[x][i-1]; }

i64 calc_z( int i, int k ) {
	if ( z[i][k] < +oo )
		return z[i][k];
	if ( k==0 ) {
		return z[i][k]=0;
	}
	assert( k >= 1 );
	if ( i-1<k ) 
		return z[i][k]=+oo;
	i64 dw = 0;
	for ( int t=i-1; t>=1; --t ) 
		if ( calc_z(t,k-1)<+oo ) {
			if ( z[i][k]==+oo || z[i][k]<calc_z(t,k-1)+sum(i-1,i,n)+dw )
				z[i][k]=calc_z(t,k-1)+sum(i-1,i,n)+dw,prev[i][k]=t;
			dw+=sum(t-1,i,n);
		}
		else break ;
	return z[i][k];
}

void dump( int i, int k ) {
	if ( k ) {
		dump(prev[i][k],k-1);
		printf("%d ",i-1);
	}
}

int main() {
	int i,j,k;
	i64 ans;
	for (;2==scanf("%d %d",&n,&m);) {
		memset(pref,0,sizeof pref);
		memset(prev,-1,sizeof prev);
		for ( i = 1; i <= n-1; ++i )
			for ( j = i+1; j <= n; ++j )
				scanf("%d",&c[i][j]), pref[i][j]=pref[i][j-1]+c[i][j];
		for ( i = 0; i <= n; ++i )
			for ( k = 0; k <= m; ++k )
				z[i][k] = +oo;
		for ( ans = -oo, i = 2; i <= n; ++i )
			if ( calc_z(i,m) < +oo && ans <= calc_z(i,m) )
				ans = calc_z(j = i,m);
		printf("%lld\n",ans);
		dump(j,m), putchar('\n');
	}
	return 0;
}

