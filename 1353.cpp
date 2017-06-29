/*
 * 1353. 
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
#define S 0x80
#define N 11
typedef long long i64;
using namespace std;

int n,m;
i64 z[N][S];

int main() {
	int i,j,k,t;
	i64 ans;
	for ( i = 1; i <= 9; ++i )
		z[1][i] = 1;
	for ( m = 2; m < N; ++m )
		for ( k = 1; k <= 9*m; ++k )
			for ( t = 0; t <= 9 && k-t >= 0; ++t )
				z[m][k] += z[m-1][k-t];
	for ( ;1 == scanf("%d",&n); ) {
		for ( ans = 0, m = 1; m <= 9; ++m )
			ans += z[m][n];
		if ( n == 1 ) ++ans;
		printf("%lld\n",ans);
	}
	return 0;
}

