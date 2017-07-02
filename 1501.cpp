/*
 * TOPIC: bfs
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
#include <queue>
#define Q (1<<22)
#define tol (1e-13)
#define N 0x400
using namespace std;
enum { RED, BLACK };

unsigned enc( unsigned int x, unsigned int y, int t ) {
	return x|(y<<10)|((t+1)<<20);
}

int n;
char a[N],b[N],
	 pile_size[2];
bool z[Q];
unsigned int way[Q];
queue<unsigned int> q;
unsigned char move[(Q>>3)+8];

void dump( unsigned int u ) {
	if ( u == enc(n,n,0) )
		return ;
	dump(way[u]), putchar((move[u>>3]&(1<<(u&7)))?'2':'1');
}

int main() {
	int i,j,k,x,y,nx,ny,t,nt,card;
	unsigned int u,v;
	for ( ;3 == scanf("%d %s %s",&n,a+1,b+1); ) {
		for ( i = 1, j = n; i < j; ++i, --j )
			swap(a[i],a[j]), swap(b[i],b[j]);
		memset(z,0,sizeof z), memset(move,0,sizeof move);
		for ( z[u=enc(n,n,0)] = true, q.push(u); !q.empty(); ) {
			u = q.front(), q.pop(), x = (u&1023), y = ((u>>10)&1023), t = (u>>20), --t;
			if ( x ) {
				card = a[x]-'0';
				v = enc(x-1,y,nt=(card==RED?t-1:t+1));
				if ( -1 <= nt && nt <= 1 )
					if ( !z[v] ) 
						z[v] = true, way[v] = u, q.push(v);
			}
			if ( y ) {
				card = b[y]-'0';
				v = enc(x,y-1,nt=(card==RED?t-1:t+1));
				if ( -1 <= nt && nt <= 1 )
					if ( !z[v] ) 
						z[v] = true, way[v] = u, q.push(v), move[v>>3] |= (1<<(v&7));
			}
		}
		if ( z[enc(0,0,0)] ) {
			dump(enc(0,0,0));
			putchar('\n');
		}
		else puts("Impossible");
	}
	return 0;
}

