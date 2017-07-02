/*
 * 1463. 
 * TOPIC: dp on tree
 * sttus: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define N (50100)
#define MAXE (N<<1)
#define MAXN N
#define oo (1LL<<60)
typedef long long i64;
using namespace std;

int n,to[MAXE],next[MAXE],last[N],E,root,out[N],*ptr,is_leaf[N],
	seen[N],yes,p[N],_left[N],_right[N],best_son[N];
vector<int> r;
i64 weight[MAXE],w[MAXN],z[N],best_path[N];

void add_arcs( int x, int y, i64 W ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, weight[i] = W;
	to[j] = x, next[j] = last[y], last[y] = j, weight[j] = W;
}

void dfs( int x ) {
	int i,y;
	i64 L = -oo, R = -oo, first_son = -1, second_son = -1;
	assert( seen[x] != yes );
	for ( best_path[x] = w[x], best_son[x] = -1, seen[x] = yes, i = last[x]; i >= 0 && (y = to[i]) >= 0; i = next[i] )
		if ( seen[y] != yes ) {
			p[y] = i, dfs(y);
			if ( best_path[x] < w[x]+weight[i]+best_path[y] )
				best_path[x] = w[x]+weight[i]+best_path[y], best_son[x] = i;
		}
	for ( z[x] = w[x], i = last[x]; i >= 0 && (y=to[i]) >= 0; i = next[i] ) 
		if ( p[y] == i ) {
			if ( R <= weight[i]+best_path[y] )
				L = R, second_son = first_son, R = weight[i]+best_path[y], first_son = i;
			else if ( L < weight[i]+best_path[y] )
				L = weight[i]+best_path[y], second_son = i;
		}
	assert( L <= R );
	//printf("%d %lld %lld\n",x+1,L,R);
	if ( L > -oo && w[x]+L+R > z[x] ) {
		z[x] = w[x]+L+R;
		_left[x] = first_son, _right[x] = second_son;
	}
	if ( R > -oo && w[x]+R > z[x] ) {
		z[x] = w[x]+R;
		_left[x] = first_son, _right[x] = -1;
	}
	if ( z[x] == w[x] )
		is_leaf[x] = yes, _left[x] = _right[x] = -1;
}

void top_to_bottom( int x ) {
next:
	*ptr++ = (x+1);
	if ( is_leaf[x] != yes && best_son[x] != -1 ) {
		//top_to_bottom(to[_left[x]]);
		x = to[best_son[x]];
		goto next;
	}
	else return ;
}

void bottom_to_top( int x ) {
	//printf("is_leaf[%d] = %s\n",x+1,is_leaf[x]==yes?"yes":"no");
	if ( is_leaf[x] != yes && best_son[x] != -1 )
		bottom_to_top(to[best_son[x]]);
	*ptr++ = (x+1);
}

void dump( int x ) {
	if ( _left[x] != -1 )
		0&&printf("Calling for %d, %d\n",x+1,to[_left[x]]+1), bottom_to_top(to[_left[x]]);
	*ptr++ = (x+1);
	if ( _right[x] != -1 )
		0&&printf("Calling for %d, %d\n",x+1,to[_right[x]]+1), top_to_bottom(to[_right[x]]);
}

int main() {
	int i,j,k,l,m;
	i64 ans;
	for ( ;2 == scanf("%d %d",&n,&m) && ++yes; ) {
		for ( E = 0, i = 0; i < n; scanf("%lld",w+i), last[i++] = -1 ) ;
		for ( i = 0; i < n; _left[i]=_right[i]=best_son[i]=-1, z[i] = best_path[i] = -oo, ++i ) ;
		for ( l = 0; l < m && 3 == scanf("%d %d %d",&i,&j,&k); ++l, add_arcs(--i,--j,k) ) ;
		for ( r.clear(), i = 0; i < n; ++i )
			if ( seen[i] != yes )
				r.push_back(i), dfs(i);
		for ( k = -1, ans = -oo, i = 0; i < n; ++i )
			if ( ans < z[i] )
				ans = z[k=i];
		assert( k != -1 );
		ptr = out, dump(k);
		printf("%lld\n%d\n",ans,ptr-out);
		for ( i = 0; i < ptr-out-1; ++i )
			printf("%d ",out[i]);
		printf("%d\n",out[i]);
	}
	return 0;
}

