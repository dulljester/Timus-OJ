/*
 * TOPIC: dp, binary search
 */
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;
#define M (30100)
#define N (100100)

int n,x[N],y[N],len[N],
	s[M],z[N];
vector<pair<int,int> > vec;

int main() {
	int i,j,k,left,right,good,bad,mid;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < M; s[i++] = -1 ) ;
		for ( i = 1; i <= n; ++i ) {
			scanf("%d %d",&x[i],&y[i]), len[i] = y[i]-x[i]+1;
			if ( s[y[i]] == -1 || len[s[y[i]]] > len[i] )
				s[y[i]] = i;
		}
		for ( vec.clear(), i = 1; i < M; ++i )
			if ( s[i] != -1 )
				vec.push_back(make_pair(x[s[i]],y[s[i]]));
		n = vec.size();
		for ( i = 0; i < n-1; ++i )
			assert( vec[i].second < vec[i+1].second ) ;
		for ( i = 1; i <= n; ++i ) {
			left = vec[i-1].first, right = vec[i-1].second;
			if ( i == 1 ) {
				z[i] = 1;
				continue ;
			}
			z[i] = max(1,z[i-1]);
			if ( vec[0].second+1 > left ) 
				continue ;
			assert( vec[0].second+1 <= left );
			if ( vec[i-2].second+1 <= left ) {
				z[i] = max(z[i],1+z[i-1]);
				continue ;
			}
			assert( vec[i-2].second+1 > left ) ;
			for ( good = 0, bad = i-2; good+1<bad; vec[mid=(good+bad)/2].second+1 <= left?(good=mid):(bad=mid) ) ;
			assert( vec[good].second+1 <= left );
			assert( vec[bad].second+1 > left );
			z[i] = max(z[i],1+z[good+1]);
		}
		printf("%d\n",z[n]);
	}
	return 0;
}

