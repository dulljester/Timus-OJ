/*
 * 1069.
 * TOPIC: Prüfer Code
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
#include <set>
#define tol (1e-13)
#define N 7600
using namespace std;

priority_queue<int,vector<int>,std::greater<int> > pq;
set<int> adj[N];
int n,m[N],a[N];

int main() {
	int i,j,k;
	for ( n = 0; 1 == scanf("%d",a+n); ++m[a[n++]] ) ;
	for ( ++n, i = 1; i <= n; ++i )
		if ( !m[i] ) 
			pq.push(i);
	for ( i = 0; i < n-1; ++i ) {
		int x = a[i], y = pq.top();
		pq.pop();
		adj[x].insert(y);
		adj[y].insert(x);
		if ( !--m[x] )
			pq.push(x);
	}
	for ( i = 1; i <= n; ++i ) {
		printf("%d:",i);
		for ( set<int> :: iterator it = adj[i].begin(); it != adj[i].end(); printf(" %d",*it++) ) ;
		puts("");
	}
	return 0;
}

