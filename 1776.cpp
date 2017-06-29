/*
 * 1776. Fireworks!
 * TOPIC: dp, math expectation
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
#define N (0x200)
#define K (N)
#define oo (1<<30)
using namespace std;

int n,m;
double p[N][K],pref[N][K];

double calc_p( int n, int k );

double calc_pref( const int n, int k ) {
	if ( pref[n][k] < +oo )
		return pref[n][k];
	if ( k == 0 )
		return pref[n][k] = n>0?0:1;
	assert( k >= 1 );
	return pref[n][k] = calc_pref(n,k-1)+calc_p(n,k);
}

double calc_p( int n, int k ) {
	if ( p[n][k] < +oo )
		return p[n][k];
	if ( k == 0 ) 
		return p[n][k] = n==0?1:0;
	if ( k == 1 )
		return p[n][k] = n==1?1:0;
	assert( k >= 2 );
	p[n][k] = 0;
	if ( k > n ) return p[n][k] = 0;
	assert( n >= k ) ;
	for ( int t = 1; t <= n; ++t )
		p[n][k] += calc_pref(t-1,k-1)*calc_pref(n-t,k-1)-calc_pref(t-1,k-2)*calc_pref(n-t,k-2);
	return p[n][k]/=n;
}

double f( int n ) {
	double ans = 0;
	int i,j,k;
	if ( n == 1 ) return 1;
	assert( n >= 2 );
	for ( k = 1; k <= n; ++k )
		ans += k*calc_p(n,k);
	return ans;
}

int main() {
	int i,j,k,t;
	for ( n = 0; n < N; ++n )
		for ( k = 0; k < N; ++k )
			p[n][k] = pref[n][k] = +oo;
	for ( ;1 == scanf("%d",&n); printf("%lf\n",10*f(n-2)) );
	return 0;
}

