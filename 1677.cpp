/*
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
#define tol (1e-13)
#define N (1<<15)
using namespace std;

int n,A,p[N];
double a[2][N],b[N],P;
char s[N];
map<int,double> row[N];

void add( map<int,double> &m, int i, double t ) {
	if ( m.find(i) == m.end() )
		m[i] = t;
	else m[i] += t;
}

int main() {
	int i,j,k,t,ch;
	while ( 2 == scanf("%d %s",&A,s+1) ) {
		for(n=strlen(s+1),j=p[0]=-1,i=1;i<=n;p[i++]=++j) 
			for(;j+1&&s[j+1]!=s[i];j=p[j]) ;
		for ( i = 0; i <= n; ++i ) row[i].clear();
		for ( add(row[0],0,-1.00/A), add(row[0],1,P=1.00/A), b[0] = -1, i = -1; i <= n-1; b[i++] = -1 ) 
			for ( add(row[i],i,-1), ch = 0; ch < A; ++ch ) {
				if ( ch == s[i+1]-'a' )
					add(row[i+1],i,P);
				else {
					for ( j = p[i]; j+1 && s[j+1]-'a' != ch; j = p[j] ) ;
					add(row[j+1],i,P);
				}
			}
		add(row[n],n,-1), b[n] = 0;
		t = 0, i = n;
		memset(a,0,sizeof a);
		for ( map<int,double> :: iterator it = row[i].begin(); it != row[i].end(); ++it )
			a[i][it->first] = it->second;
		t ^= 1, --i;
		for ( map<int,double> :: iterator it = row[i].begin(); it != row[i].end(); ++it )
			a[i][it->first] = it->second;
		for ( j = n; j; --j ) {
			for ( cf = a[t][j]/a[t^1][j], k = 0; k <= n; ++k )
				a[t][k] -= cf*a[t^1][k];
			b[j-1] -= cf*b[j];
			if ( j >= 2 ) {
				memset(a[t^1],0,sizeof a[t^1]);
				for ( map<int,double> :: iterator it = row[j-2].begin(); it != row[j-2].end(); ++it )
					a[t^1][it->first] = it->second;
				t ^= 1;
			}
		}
		double ans = b[0]/a[t][0];
		printf("%lld\n",
	}
	return 0;
}

