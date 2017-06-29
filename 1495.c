/*
 * 1495.
 * TOPIC: bfs...
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<20)

char move[N];
int seen[N],yes,d[N],q[N],*head,*tail,n,p[N];

void dump( int x ) {
	if ( p[x] != -1 ) dump(p[x]);
	putchar(move[x]+'0');
}

int main() {
	int i,j,k,x,y;
	for ( ;1 == scanf("%d",&n); ) {
		if ( n == 1 ) {
			puts("1");
			continue ;
		}
		if ( n == 2 ) {
			puts("2");
			continue ;
		}
		for ( p[1%n]=p[2%n]=-1,move[1%n]=1,move[2%n]=2,head=tail=q,seen[*tail++=(1%n)]=++yes,d[1%n]=0,seen[*tail++=(2%n)]=yes,d[2%n]=0; head < tail; )
			for ( x = *head++, i = 1; i <= 2; ++i )
				if ( seen[y=(10*x+i)%n] != yes )
					seen[*tail++=y]=yes,d[y] = d[x]+1,move[y]=i,p[y]=x;
		if ( seen[0] != yes ) {
			puts("Impossible");
			continue ;
		}
		dump(0), putchar('\n');
	}
	return 0;
}

