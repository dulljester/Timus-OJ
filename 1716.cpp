/*
 * 1716. 
 * TOPIC: dp, expectation
 * status: WA #3, loss of precision, constant-time formula
 * NOTES: reportedly it can be done in O(n^2); mine is O(n)
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#define tol (1e-13)
#define S (1<<14)
using namespace std;

long double z[S];
int n,s;

long double C( int n, int k ) {
	assert( n >= k );
	return z[n]-z[k]-z[n-k];
}

int main() {
	int i,j,k;
	long double ans;
	for ( z[1] = 0, i = 2; i < S; z[i] = z[i-1]+log(i), ++i ) ;
	for ( ;2 == scanf("%d %d",&n,&s) && (n||s); ) {
		assert( 2*n <= s && s <= 3*n );
		if ( s == 3*n ) {
			puts("0.00000");
			continue ;
		}
		long double B = C(n,3*n-s);
		for ( ans = 0, k = 1; k <= 3*n-s; ++k ) {
			assert( k <= n );
			if ( 3*n-s-1 < k-1 ) continue ;
			long double A = C(3*n-s-1,k-1);
			if ( s-2*n-1 >= k )
				ans += 2*k*expl(C(s-2*n-1,k)+A-B);
			if ( s-2*n-1 >= k-1 )
				ans += 2*k*expl(C(s-2*n-1,k-1)+A-B);
			if ( s-2*n-1 >= k-1 )
				ans += (2*k-1)*expl(C(s-2*n-1,k-1)+A-B);
			if ( s-2*n-1 >= k-2 && k-2 >= 0 )
				ans += (2*k-1)*expl(C(s-2*n-1,k-2)+A-B);
		}
		//printf("%Lf\n",ans*exp(z[3*n-s-1]+z[3*n-s]+z[s-2*n]-z[n]));
		printf("%Lf\n",ans);
	}
	return 0;
}

