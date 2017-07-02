/*
 * 1183. Bracket Sequence
 * TOPIC: dp
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>
#include <vector>
#define N 0x80
typedef long long i64;
#define oo (1LL<<60)
using namespace std;

int n,split[N][N],wrap[N][N],surround[N][N],yes;
i64 z[N][N];
char s[N],*ptr,out[N+N];

bool is_cbs( int i, int j ) {
	deque<char> op;
	for ( int k = i; k <= j; ++k ) {
		if ( s[k] == '(' || s[k] == '[' ) {
			op.push_front(s[k]);
			continue ;
		}
		assert( s[k] == ')' || s[k] == ']' );
		if ( op.empty() || (s[k]==')'&&op.front()!='(') || (s[k]==']'&&op.front()!='[') )
			return false ;
		op.pop_front();
	}
	return op.empty();
}

void dump( int i, int j ) {
	if ( i > j ) return ;
	if ( z[i][j] == (j-i+1) ) {
		for ( int t = i; t <= j; *ptr++ = s[t++] ) ;
		return ;
	}
	if ( i == j ) {
		if ( s[i] == '(' || s[i] == ')' )
			*ptr++ = '(', *ptr++ = ')';
		else *ptr++ = '[', *ptr++ = ']';
		return ;
	}
	assert( i < j );
	int t = split[i][j];
	if ( t == -1 ) {
		if ( surround[i][j] == yes ) {
			*ptr++ = s[i], dump(i+1,j-1), *ptr++ = s[i]=='('?')':']';
			return ;
		}
		if ( wrap[i][j] == i ) 
			*ptr++ = s[i], dump(i+1,j), *ptr++=(s[i]=='('?')':']');
		else 
			*ptr++ = (s[j]==')'?'(':'['), dump(i,j-1), *ptr++ = s[j];
	}
	else {
		assert( z[i][j] == z[i][t]+z[t+1][j] );
		dump(i,t), dump(t+1,j);
	}
}

int main() {
	int i,j,k,t;
	for ( ;1 == scanf("%s",s+1) && ++yes; ) {
		n = strlen(s+1);
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= n; ++j )
				z[i][j] = +oo, split[i][j] = wrap[i][j] = -1;
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j < i; ++j )
				z[i][j] = 0;
		for ( i = 1; i <= n; ++i ) {
			z[i][i] = 2;
			wrap[i][i] = i;
		}
		for ( k = 2; k <= n; ++k )
			for ( i = 1; (j = i+k-1) <= n; ++i ) {
				if ( is_cbs(i,j) ) {
						/*
					char tmp = s[j+1];
					s[j+1] = '\0';
					puts(s+i);
					s[j+1] = tmp;*/
					z[i][j] = (j-i+1);
					continue ;
				}
				for ( t = i; t <= j-1; ++t )
					if ( z[i][t] < +oo && z[t+1][j] < +oo ) 
						if ( z[i][t]+z[t+1][j] < z[i][j] ) {
							z[i][j] = z[i][t]+z[t+1][j];
							split[i][j] = t;
						}
				if ( s[i] == '(' || s[i] == '[' )
					if ( z[i+1][j] < +oo && z[i+1][j]+2 < z[i][j] ) {
						z[i][j] = z[i+1][j]+2;
						wrap[i][j] = i, split[i][j] = -1;
					}
				if ( s[j] == ')' || s[j] == ']' ) 
					if ( z[i][j-1] < +oo && z[i][j-1]+2 < z[i][j] ) {
						z[i][j] = z[i][j-1]+2;
						wrap[i][j] = j, split[i][j] = -1;
					}
				if ( s[i] == '(' && s[j] == ')' || s[i] == '[' && s[j] == ']' ) 
					if ( z[i+1][j-1] < +oo && 2+z[i+1][j-1] < z[i][j] ) {
						wrap[i][j] = split[i][j] = -1, surround[i][j] = yes;
						z[i][j] = 2+z[i+1][j-1];
					}
			}
		ptr = out, dump(1,n), *ptr = '\0';
		puts(out);
	}
	return 0;
}

