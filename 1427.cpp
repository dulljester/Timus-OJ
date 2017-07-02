/*
 * 1427.
 * TOPIC: dp, prefix sums, binary search
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
#include <cctype>
#define tol (1e-13)
#define N (1<<17)
#define oo (1LL<<60)
typedef long long i64;
using namespace std;

int m,n,len,pref[N],way[N];
i64 z[N];
char s[N];

int sum( int i, int j ) { return pref[j]-pref[i-1]; }
bool is_heavy( int i, int j ) { return sum(i,j)>0; }

i64 calc_z( int k ) {
	int good,bad,mid;
	if ( k <= 0 ) return 0;
	if ( z[k] < +oo )
		return z[k];

	if ( !is_heavy(1,k) ) {
		way[k] = k-m;
		return z[k] = 1+calc_z(k-m);
	}

	if ( is_heavy(k,k) ) {
		way[k] = k-n;
		return z[k] = 1+calc_z(k-n);
	}

	assert( !is_heavy(good=k,k) );
	assert( is_heavy(bad=1,k) );
	for ( ;bad+1<good; is_heavy(mid=(good+bad)/2,k)?(bad=mid):(good=mid) ) ;
	if ( k-good+1 <= m ) {
		z[k] = min(1+calc_z(bad),1+calc_z(k-n));
		if ( z[k] == 1+calc_z(bad) )
			way[k] = bad;
		else way[k] = k-n;
	}
	else {
		z[k] = min(1+calc_z(k-m),1+calc_z(k-n));
		if ( z[k] == 1+calc_z(k-m) )
			way[k] = k-m;
		else way[k] = k-n;
	}
	return z[k];
}

void dump( int k ) {
	if ( k >= 1 ) {
		dump(way[k]);
		for ( int t = way[k]+1; t <= k; ++t )
			putchar(s[t]);
		putchar('\n');
	}
}

int main() {
	int i,j,k,low,high,mid;
	for ( ;fgets(s,sizeof s,stdin) && 2 == sscanf(s,"%d %d",&n,&m); ) {
		fgets(s+1,sizeof s,stdin);
		for ( len = 1; s[len] && s[len] != '\n'; ++len ) ;
		--len;
		for ( i = 1; i <= len; ++i ) 
			pref[i] = pref[i-1]+(isalpha(s[i])||s[i]==' '?0:1), z[i] = +oo;
		printf("%lld\n",calc_z(len));
		//dump(len);
	}
	return 0;
}

