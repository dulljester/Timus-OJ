/*
 * 1158. Censored!
 * TOPIC: AC automata
 * status:
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#define MAXA 33
#define tol (1e-13)
#define BIT(k) (1ULL<<(k))
#define L(k) ((k) & ((~(k))+1ULL))
#define SET(u,k) ((u)|=BIT(k))
#define TST(u,k) (((u)>>(k))&1ULL)
#define MAXP 10
#define N 0x80
#define Q (1<<21)
#include <queue>
typedef unsigned long long u64;
using namespace std;

char which[1<<21];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

typedef struct cell {
	cell *slink, *son[MAXA];
	u64 u;
	int ch,id;
	unsigned int mask;
	cell() {};
} cell ;

int n,m,forbidden,A,V,
	words[MAXP][0x10],len[MAXP];
u64 g[N][N],ax[N][N],mat[N][N];
map<char,int> mp;
cell pool[Q], *ptr, *root, *q0;
queue<cell *> q;

cell *init( int ch ) {
	cell *x = ptr++;
	x->slink = NULL, x->u = x->mask = 0, x->ch = ch, x->id = V++;
	return x;
}

void push( int *s, int len, const int id ) {
	int i = 0;
	cell *x;
	for ( x = root; i < len; x = x->son[s[i++]] ) 
		if ( !TST(x->u,s[i]) ) 
			SET(x->u,s[i]), x->son[s[i]] = init(s[i]);
	SET(x->mask,id);
}

int main() {
	int i,j,k,l;
	char tmp[0x40];
	u64 u,v,ans;
	cell *x,*y,*z;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for ( ;3 == scanf("%d %d %d",&n,&m,&forbidden); ) {
		//if ( !(n||m||forbidden) ) break ;
		for ( V = 0, mp.clear(), scanf("%s",tmp), i = 0; i < n; mp[tmp[i]] = i, ++i ) ;
		for ( k = 0; k < forbidden; len[k++] = i ) 
			for ( scanf("%s",tmp), i = 0; tmp[i]; words[k][i] = mp[tmp[i]], ++i ) ;
		for ( ptr=pool, q0 = init('\0'), root = init('$'), i=0; i<forbidden; push(words[i],len[i],i), ++i ) ;
		for ( A = mp.size(), root->slink = q0, i = 0; i < A; ++i )
			SET(q0->u,i), q0->son[i] = root;
		assert( A == n ) ;
		for ( u = root->u; u; u &= ~L(u) )
			x = root->son[who(L(u))], x->slink = root, q.push(x);
		while ( !q.empty() ) 
			for(x=q.front(),q.pop(),u=x->u;u;y->slink=z->son[y->ch],y->mask|=(y->slink->mask),q.push(y),u&=~L(u)) 
				for ( y = x->son[who(L(u))], z = x->slink; !TST(z->u,y->ch); z = z->slink ) ;
		for ( i = 0; i < A; ++i )
			if ( !TST(root->u,i) )
				SET(root->u,i), root->son[i] = root;
			else
				q.push(root->son[i]);
		while ( !q.empty() )
			for ( x = q.front(), q.pop(), i = 0; i < A; ++i )
				if ( TST(x->u,i) )
					q.push(x->son[i]);
				else {
					for ( y = x->slink; !TST(y->u,i); y = y->slink ) ;
					SET(x->u,i), x->son[i] = y->son[i];
					//if ( x->id == 10 ) printf("[%c] %d --> %d\n",i+'a',x->id,y->son[i]->id);
				}
		memset(g,0,sizeof g);
		for ( k = 1; k < ptr-pool; ++k ) 
			for ( x = pool+k, i = x->id, l = 0; l < A && !x->mask; ++l )
				if ( !(x->son[l]->mask) )
					++g[i][x->son[l]->id];
		memset(ax,0,sizeof ax);
		for ( i = 0; i < V; ax[i][i] = 1, ++i ) ;
		for ( ;m; m >>= 1 ) {
			if ( m&1 ) {
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						for ( mat[i][j] = 0, k = 0; k < V; ++k )
							mat[i][j] += ax[i][k]*g[k][j];
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						ax[i][j] = mat[i][j];
			}
			for ( i = 0; i < V; ++i )
				for ( j = 0; j < V; ++j )
					for ( mat[i][j] = 0, k = 0; k < V; ++k )
						mat[i][j] += g[i][k]*g[k][j];
			for ( i = 0; i < V; ++i )
				for ( j = 0; j < V; ++j )
					g[i][j] = mat[i][j];
		}
		for ( ans = 0, i = 0; i < V; ans += ax[root->id][i++] ) ; 
		printf("%llu\n",ans);
	}
	return 0;
}

