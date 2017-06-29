/*
 * 1303. Minimal/Minimum Cover
 * TOPIC: dp, binary search, greedy, O(n^2)
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
using namespace std;
#define M 5050
#define N (100100)
#define oo (1<<30)

vector<pair<int,int> > vec, out;
int m,n,L[N],R[N],s[M],len[N],z[M],l[N],r[N],way_back[M];

void dump( int k ) {
	if ( way_back[k] != -1 ) 
		dump(way_back[k]);
	out.push_back(make_pair(l[s[k]],r[s[k]]));
}

int main() {
	int i,j,k,ll,rr,good,bad,mid,t;
	for ( ;1 == scanf("%d",&m); ) {
		for ( i = 0; i <= m; s[i++] = -1 ) ;
		for ( n = 1; 2 == scanf("%d %d",&i,&j) && (i||j); ++n ) {
			L[n] = max(0,i), R[n] = min(m,j), len[n] = R[n]-L[n]+1, l[n] = i, r[n] = j;
			if ( L[n] <= R[n] ) 
				if ( s[R[n]] == -1 || len[s[R[n]]] < len[n] )
					s[R[n]] = n;
		}
		for ( vec.clear(), i = 0; i <= m; ++i )
			if ( s[i] != -1 )
				vec.push_back(make_pair(L[s[i]],R[s[i]]));
		for ( n = vec.size(), i = 0; i <= m; z[i++] = +oo ) ;
		if ( n == 0 ) {
			assert( m >= 1 );
			puts("No solution");
			continue ;
		}
		assert( n >= 1 );
		for ( j = 0, i = 0; i <= m; ++i ) {
			if ( s[i] == -1 ) continue ;
			for ( ;j < n && vec[j].second != i; ++j ) ;
			assert( j < n );
			if ( vec[j].first == 0 ) 
				z[i] = 1, way_back[i] = -1;
			else {
				assert( vec[j].first > 0 );
				if ( j == 0 ) continue ;
				assert( j >= 1 );
				if ( vec[0].second >= vec[j].first ) {
					assert( vec[j-1].second >= vec[j].first ) ;
					ll = 0, rr = j-1;
				}
				else {
					assert( vec[0].second < vec[j].first );
					if ( vec[j-1].second < vec[j].first ) 
						continue ;
					assert( vec[j-1].second >= vec[j].first ) ;
					for ( good = j-1, bad = 0; bad+1<good; vec[mid=(good+bad)/2].second>=vec[j].first?(good=mid):(bad=mid) ) ;
					ll = good, rr = j-1;
				}
				for ( t = ll; t <= rr; ++t ) {
					assert( vec[t].second >= vec[j].first ) ;
					if ( z[vec[t].second] < +oo )
						if ( z[i] > 1+z[vec[t].second] )
							z[i] = 1+z[vec[t].second], way_back[i] = vec[t].second;
				}
			}
		}
		if ( z[m] == +oo ) {
			puts("No solution");
			continue ;
		}
		printf("%d\n",z[m]), out.clear(), dump(m), sort(out.begin(),out.end());
		for ( i = 0; i < (int)out.size(); ++i )
			printf("%d %d\n",out[i].first,out[i].second);
	}
	return 0;
}

