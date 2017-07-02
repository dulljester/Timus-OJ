/*
 * 1031.
 * TOPIC: dp, binary search
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
typedef long long i64;
#define N (1<<14)
#define oo (1LL<<60)
using namespace std;

i64 l1,l2,l3,c1,c2,c3,dist[N],z[N];
int n,src,sink;

i64 d( int i, int j ) { return dist[j]-dist[i]; }

int find( int x, i64 L ) {
	int good,bad,mid;
	assert( x > src );
	if ( d(src,x) <= L ) 
		return src;
	assert( d(src,x) > L );
	assert( d(x,x) <= L );
	for(good=x,bad=src;bad+1<good;d(mid=(good+bad)/2,x)<=L?(good=mid):(bad=mid));
	assert( d(bad,x) > L );
	assert( d(good,x) <= L );
	return good;
}

i64 calc_z( int i ) {
	if ( z[i] < +oo )
		return z[i];
	if ( i == src ) 
		return z[i] = 0;
	assert( i > src );
	int j;
	if ( (j = find(i,l1)) < i && calc_z(j) < +oo ) {
		//printf("l1: %d --> %d\n",j,i);
		z[i] = min(z[i],calc_z(j)+c1);
	}
	if ( (j = find(i,l2)) < i && d(j,i) > l1 && d(j,i) <= l2 && calc_z(j) < +oo ) {
		//printf("l2: %d --> %d\n",j,i);
		z[i] = min(z[i],calc_z(j)+c2);
	}
	if ( (j = find(i,l3)) < i && d(j,i) > l2 && d(j,i) <= l3 && calc_z(j) < +oo ) {
		//printf("l3: %d --> %d, %lld\n",j,i,d(j,i));
		z[i] = min(z[i],calc_z(j)+c3);
	}
	return z[i];
}

int main() {
	int i,j,k;
	for ( ;6 == scanf("%lld %lld %lld %lld %lld %lld",&l1,&l2,&l3,&c1,&c2,&c3); ) {
		scanf("%d",&n);
		scanf("%d %d",&src,&sink), --src, --sink;
		if ( src > sink ) 
			swap(src,sink);
		for ( i = 1; i < n; ++i )
			scanf("%lld",&dist[i]);
		if ( src == sink ) {
			puts("0");
			continue ;
		}
		assert( src < sink );
		for ( i = 0; i <= n; z[i++] = +oo ) ;
		printf("%lld\n",calc_z(sink));
	}
	return 0;
}

