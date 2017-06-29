/*
 * 1039. Anniversary Party
 * TOPIC: dp on tree
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
using namespace std;
#define oo (1LL<<60)
#define N 6666

vector<int> adj[N];
int n,c[N],sup[N],root,is_leaf[N],yes;
i64 z[2][N];

i64 calc_z( int t, int x ) {
	if ( z[t][x] < +oo )
		return z[t][x];
	if ( is_leaf[x] ) 
		return z[t][x] = t*c[x];
	assert( !is_leaf[x] ) ;
	z[t][x] = 0;
	for ( int y,i = 0; i < (int)adj[x].size() && (y = adj[x][i]) >= 0; ++i ) {
		if ( t == 0 ) 
			z[t][x] += max(calc_z(0,y),calc_z(1,y));
		else z[t][x] += calc_z(0,y);
	}
	return z[t][x]+t*c[x];
}

int main() {
	int i,j,k,t;
	for ( ;1 == scanf("%d",&n) && ++yes; ) {
		for ( i = 0; i < n; is_leaf[i] = 1, sup[i] = -1, adj[i++].clear() ) ;
		for ( i = 0; i < n; ++i )
			scanf("%d",&c[i]);
		for ( i = 0; i < n; ++i )
			for ( t = 0; t < 2; ++t )
				z[t][i] = +oo;
		for ( ;2 == scanf("%d %d",&i,&j) && (i||j); --i, --j, adj[j].push_back(i), is_leaf[j] = 0, sup[i] = j ) ;
		for ( root = -1, i = 0; i < n; ++i )
			if ( sup[i] == -1 ) {
				assert( root == -1 );
				root = i;
			}
		assert( root != -1 );
		printf("%lld\n",max(calc_z(0,root),calc_z(1,root)));
	}
	return 0;
}

