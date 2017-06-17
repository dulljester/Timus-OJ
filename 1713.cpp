/*
 * 1713. Key Substrings
 * TOPIC: dp on suffix automata
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
#include <map>
#define A 26
#define tol (1e-13)
#define N (100*1000+2000)
#define is_primary(x,y) ((x)->len+1 == (y)->len)
using namespace std;

typedef struct cell {
	map<int,cell *> son;
	cell *slink;
	bool visited,ok,is_delimiter;
	int len,pos,first_delimiter;
	cell() {};
} cell;

cell pool[2*N],*ptr,*root,*sink,*q[2*N],**head,**tail;
int str[N],idx[N],dp[0x400],begin[0x400],end[0x400];

void dfs( cell *x ) {
	cell *y;
	if ( !x || x->visited ) return ;
	x->visited = true ;
	for ( map<int,cell *>::iterator it=x->son.begin(); it!=x->son.end(); ++it ) {
		dfs(y=it->second);
		assert( y->first_delimiter != -1 );
		if ( x->first_delimiter == -1 )
			x->first_delimiter = y->first_delimiter;
		if ( !x->ok ) continue ;
		if ( !y->ok )
			x->ok = false ;
		if ( x->ok && (x->first_delimiter >= 0 && x->first_delimiter != y->first_delimiter) )
			x->ok = false;
	}
	if ( x->is_delimiter ) 
		x->ok = true, x->first_delimiter = idx[x->pos];
	assert( x->first_delimiter != -1 );
}

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->is_delimiter = x->visited = false;
	x->len = len, x->slink = NULL, x->pos = pos, x->son.clear(), x->ok = true, x->first_delimiter = -1;
	return x;
}

void add_son( cell *x, int ch, cell *y ) {
	x->son[ch] = y;
}

cell *split( cell *x, int ch, int pos ) {
	cell *z = init(x->len+1,pos),*y = x->son[ch];
	for ( map<int,cell *> :: iterator it = y->son.begin(); it != y->son.end(); ++it )
		z->son[it->first] = it->second;
	z->slink=y->slink,y->slink=z;
	for ( x->son[ch]=z, x=x->slink; x && x->son.find(ch)!=x->son.end() && x->son[ch]==y; x->son[ch]=z, x=x->slink ) {
		assert( !is_primary(x,x->son[ch]) );
	}
	return z;
}

cell *update( int ch, int pos ) {
	cell *new_sink=init(sink->len+1,pos),*x,*y;
	add_son(sink,ch,new_sink);
	new_sink->is_delimiter = (ch>=A);
	for ( x = sink->slink; x && x->son.find(ch) == x->son.end(); add_son(x,ch,new_sink), x = x->slink ) ;
	if ( !x ) {
		new_sink->slink = root;
		return new_sink;
	}
	if ( is_primary(x,x->son[ch]) )
		new_sink->slink = x->son[ch];
	else
		new_sink->slink = split(x,ch,pos);
	return new_sink;
}

int main() {
	int i,j,k,m,length,t;
	char tmp[0x400];
	for ( k = 0, scanf("%d",&m), i = 0; i < m; str[k++] = A+i, ++i ) 
		for ( scanf("%s",tmp), j = 0; tmp[j]; str[k++] = tmp[j++]-'a' ) ;
	for ( j = 0, i = 0; i < k; ++i )
		if ( str[i] >= A ) {
			idx[i] = j++;
			assert( str[i] == A+(j-1) );
		}
		else idx[i] = j;
	assert( j == m ) ;
	for ( i = 0; i < m; dp[i++] = (1<<30) ) ;
	ptr = pool, root = sink = init(0,-1);
	for ( i = 0; i < k; sink = update(str[i],i), ++i ) ;
	for ( dfs(root), i = 0; i < ptr-pool; ++i )
		if ( !pool[i].is_delimiter && pool[i].ok ) {
			if ( !pool[i].slink ) continue ;
			length=pool[i].slink->len+1,t=idx[pool[i].pos];
			if ( length<dp[t] && idx[pool[i].pos-length+1]==t && pool[i].first_delimiter==t )
				dp[t]=length,begin[t]=pool[i].pos-length+1,end[t]=pool[i].pos;
		}
	for(i=0;i<m;++i,putchar('\n')) {
		assert( dp[i] < (1<<30) ) ;
		for(j=begin[i];j<=end[i];putchar(str[j++]+'a')) ;
	}
	return 0;
}

