/*
 * 1260.
 * TOPIC: dp, permutations
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
#define N 64
typedef long long i64;
using namespace std;
#define oo (1LL<<60)
enum { BEFORE, AFTER };

i64 z[N];

int main() {
	int i,j,k,t,n;
	i64 ans;
	for ( z[1]=1,z[2]=1,z[3]=2,i=4;i<N; ++i )
		z[i] = z[i-1]+z[i-3]+1;
	for ( ;1 == scanf("%d",&n);  ) {
		printf("%lld\n",z[n]);
	}
	return 0;
}

