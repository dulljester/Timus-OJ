/*
 * 1586.
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
#define MOD (1000000000LL+9LL)
typedef long long i64;
#define N (1<<14)
#define A 10
using namespace std;

int n;
bool is_prime[1000],seen[N][A][A];
i64 z[N][A][A];

i64 calc_z( int n, int a, int b  ) {
	assert( n >= 3 );
	if ( n == 3 || seen[n][a][b] )
		return z[n][a][b];
	seen[n][a][b] = true ;
	for ( int t = 1; t <= 9; ++t ) 
		if ( is_prime[100*t+10*a+b] )
			z[n][a][b] += calc_z(n-1,t,a), z[n][a][b] %= MOD;
	return z[n][a][b];
}

int main() {
	int i,j,k,l = 0;
	i64 ans;
	for ( i = 3; i < 1000; i += 2 ) is_prime[i] = true ;
	for ( is_prime[2] = true, i = 3; i < 1000; i += 2 )
		for ( j = i+i; j < 1000 && is_prime[i]; is_prime[j] = false, j += i ) ;
	for ( k = 0, i = 100; i <= 999; ++i )
		if ( is_prime[i] && ++l ) 
			++z[3][j=((i-(i%10))/10)%10][k=i%10], seen[3][j][k] = true ;
	for ( ;1 == scanf("%d",&n); ) {
		if ( n == 3 ) {
			printf("%d\n",l);
			continue ;
		}
		for ( ans = 0, i = 1; i <= 9; ++i )
			for ( j = 1; j <= 9; j += 2 )
				if ( j != 5 )
					ans += calc_z(n,i,j), ans %= MOD;
		printf("%lld\n",ans);
	}
	return 0;
}

