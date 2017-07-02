/*
 * 1280. 
 * TOPIC: topological sorting
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
#define N 0x800
#define MAXE (1<<18)
#define tol (1e-13)
using namespace std;
enum { WHITE, GREY, BLACK };

int to[MAXE],_next[MAXE],last[N],E,n,seen[N],yes,
	st[N],*top,color[N],h[N],c[N],p[N],pos[N],npos[N],
	u[MAXE],v[MAXE];
bool ok;

void add_arcs( int x, int y ) {
	int i = E++;
	to[i] = y, _next[i] = last[x], last[x] = i;
}

void dfs( int x ) {
	int i,y;
	assert( color[x] == WHITE ) ;
	for ( color[x] = GREY, i = last[x]; i >= 0; i = _next[i] )
		if ( color[y=to[i]] == WHITE ) {
			p[y] = i, dfs(y);
			if ( !ok ) return ;
		}
		else if ( color[y] == GREY ) {
			ok = false ;
			return ;
		}
	color[*++top = x] = BLACK;
}


int main() {
	int i,j,k,m,l;
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( E = 0, i = 0; i < n; ok = true, color[i] = WHITE, last[i++] = -1 ) ;
		for ( l = 0; l < m && 2 == scanf("%d %d",&i,&j); add_arcs(u[l]=--i,v[l]=--j), ++l ) ;
		for ( top = st, i = 0; i < n && ok; ++i )
			if ( color[i] == WHITE )
				dfs(i);
		if ( ok ) {
			for ( i = 0; top > st; c[i++] = *top--, pos[c[i-1]] = i-1 ) ;
		}
		for ( i = 0; i < n; ++i ) 
			scanf("%d",&h[i]), npos[--h[i]] = i;
		for ( i = 0; i < m && ok; ++i )
			if ( npos[u[i]] > npos[v[i]] ) 
				ok = false ;
		puts(ok?"YES":"NO");
	}
	return 0;
}

