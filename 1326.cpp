/*
 * 1326.
 * TOPIC: dp, bitmasks
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
#define N 21
#define M 0x100
#define BIT(k) (1UL<<(k))
#define L(k) ((k)&((~(k))+1UL))
#define oo (1LL<<60)
typedef long long i64;

int c[N],n,m,h[M],s[M],len,which[1<<N],seen[1<<N],yes;
unsigned int u[M],mask;
i64 z[1<<N];
vector<int> lst[N];

i64 calc_z( unsigned int v ) {
	if ( z[v] < +oo || seen[v] == yes )
		return z[v];
	int i = which[L(v)],j;
	seen[v] = yes;
	for ( int l = 0; l < (int)lst[i].size(); ++l ) 
		if ( calc_z(v&~u[j=lst[i][l]]) < +oo )
			if ( calc_z(v&~u[j])+h[j] < z[v] )
				z[v] = calc_z(v&~u[j])+h[j];
	return z[v];
}

int main() {
	int i,j,k;
	unsigned int uu,vv;
	i64 best;
	for ( i = 0; i < N; which[BIT(i)] = i, ++i ) ;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; scanf("%d",&c[i++]) ) ;
		for ( scanf("%d",&m), i = 0; i < m; ++i ) 
			for ( u[i] = 0, scanf("%d %d",&h[i],&k); k-- && 1 == scanf("%d",&j); --j, u[i] |= BIT(j) ) ;
		for ( i = m; i < m+n; ++i )
			u[i] = BIT(i-m), h[i] = c[i-m];
		for ( mask = 0, scanf("%d",&len), i = 0; i < len; scanf("%d",&s[i++]), --s[i-1], mask |= BIT(s[i-1]) ) ;
		for ( i = 0; i < n; lst[i++].clear() ) ;
		for ( m += n, i = 0; i < m; ++i )
			for ( uu = u[i]; uu && (j = which[L(uu)]) >= 0; uu &= ~L(uu) )
				lst[j].push_back(i);
		for ( z[0] = 0, i = 1; i < BIT(n); z[i++] = +oo ) ;
		for ( ++yes, best = +oo, uu = 0; uu < BIT(n); ++uu )
			if ( (uu&mask) == mask && calc_z(uu) < best )
				best = calc_z(uu);
		printf("%lld\n",best);
	}
	return 0;
}

