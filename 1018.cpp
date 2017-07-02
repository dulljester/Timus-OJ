/*
 * 1018. Apple Tree
 * TOPIC: binary trees, DP
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
#define N 0x80
#define Q 0x80
#define MAXE (N<<1)
typedef long long i64;
using namespace std;
#define oo (1LL<<60)

int n,E,last[N],to[MAXE],weight[MAXE],p[N],seen[N],yes,next[MAXE],
	num_of_arcs[N],_left[N],_right[N],l[N],r[N];
i64 wgt[N],z[N][Q];

void add_arcs( int x, int y, int w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, weight[i] = w;
	to[j] = x, next[j] = last[y], last[y] = j, weight[j] = w;
}

void dfs( int x ) {
	int i,y;
	assert( seen[x] != yes );
	for ( seen[x]=yes, i=last[x]; i>=0; i=next[i] )
		if ( seen[y=to[i]] != yes ) {
			if ( _left[x]==-1 ) _left[x]=i;
			else {
				assert( _right[x]==-1 );
				_right[x]=i;
			}
			p[y]=i,dfs(y);
		}
		else assert(p[x] == (i^1));
	if ( _left[x]!=-1 ) {
		assert( _right[x] != -1 );
		l[x]=to[_left[x]],r[x]=to[_right[x]];
	}
}

i64 calc_wgt( int x ) {
	if ( wgt[x] < +oo )
		return wgt[x];
	wgt[x] = num_of_arcs[x] = 0;
	for ( int i = last[x],y; i >= 0; i = next[i] )
		if ( p[y=to[i]] == i ) 
			wgt[x] += weight[i]+calc_wgt(y), num_of_arcs[x] += (1+num_of_arcs[y]);
	return wgt[x];
}

i64 f( int x, int k ) {
	if ( z[x][k] > -oo )
		return z[x][k];
	if ( k == num_of_arcs[x] )
		return z[x][k] = calc_wgt(x);
	if ( k > num_of_arcs[x] )
		return z[x][k] = -oo;
	assert( k < num_of_arcs[x] );
	if ( k == 0 ) 
		return z[x][k] = 0;
	assert( k >= 1 );
	assert( _left[x] != -1 && _right[x] != -1 );
	for ( int t = 1; t <= num_of_arcs[l[x]]+1 && t <= k-1; ++t )
		if ( num_of_arcs[r[x]]+1 >= k-t )
			if ( f(l[x],t-1) > -oo )
				if ( f(r[x],k-t-1) > -oo )
					if ( f(l[x],t-1)+f(r[x],k-t-1)+weight[_left[x]]+weight[_right[x]] > z[x][k] )
						z[x][k] = f(l[x],t-1)+f(r[x],k-t-1)+weight[_left[x]]+weight[_right[x]];
	for ( int t = 1; t <= num_of_arcs[r[x]]+1 && t <= k-1; ++t )
		if ( num_of_arcs[l[x]]+1 >= k-t )
			if ( f(r[x],t-1) > -oo )
				if ( f(l[x],k-t-1) > -oo )
					if ( f(r[x],t-1)+f(l[x],k-t-1)+weight[_left[x]]+weight[_right[x]] > z[x][k] )
						z[x][k] = f(r[x],t-1)+f(l[x],k-t-1)+weight[_left[x]]+weight[_right[x]];
	if ( num_of_arcs[r[x]]+1 >= k )
		if ( f(r[x],k-1) > -oo )
			if ( f(r[x],k-1)+weight[_right[x]] > z[x][k] )
				z[x][k] = f(r[x],k-1)+weight[_right[x]];
	if ( num_of_arcs[l[x]]+1 >= k )
		if ( f(l[x],k-1) > -oo )
			if ( f(l[x],k-1)+weight[_left[x]] > z[x][k] )
				z[x][k] = f(l[x],k-1)+weight[_left[x]];
	return z[x][k];
}

int main() {
	int i,j,k,qr,l;
	for ( ;2 == scanf("%d %d",&n,&qr) && ++yes; ) {
		for ( E = 0, i = 0; i < n; _left[i] = _right[i] = -1, wgt[i] = +oo, last[i++] = -1 ) ;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j <= n; z[i][j++] = -oo ) ;
		for ( int m = 0; m < n-1 && 3 == scanf("%d %d %d",&i,&j,&k); ++m, add_arcs(--i,--j,k) ) ;
		p[0]=-1, dfs(0), calc_wgt(0), printf("%lld\n",f(0,qr));
	}
	return 0;
}
