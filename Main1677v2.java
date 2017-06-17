/*60805EX*/

import java.util.*;
import java.math.BigInteger;
import java.math.BigDecimal;

public class Main1677v2 {
	private static final int N = (1<<15), MAXA = 26;
	Scanner scan = new Scanner(System.in);

	double[][]a = new double[2][N];
	double[]b = new double[N];
	double P;
	int []p = new int[N], s;
	int n,A;

	Map<Integer,Map<Integer,Double>> row = new HashMap<>();
	int [][]tr = new int[N][MAXA];

	public static void main( String [] args ) {
		new Main1677v2().go();
	}

	private void add( Map<Integer,Double> m, int key, double val ) {
		if ( m.containsKey(key) )
			m.put(key,m.get(key)+val);
		else 
			m.put(key,val);
	}

	private void go() {
		String str;
		int i,j,k,t,root = 0;
		for ( ;scan.hasNext(); ) {
			A = scan.nextInt();
			str = scan.next();
			n = str.length();
			s = new int[n+1];
			for ( i = 0; i < n; ++i )
				s[i+1] = str.charAt(i)-'a';
			for ( j=p[0]=-1,i=1; i<=n; p[i++]=++j ) 
				for (;j+1>0 && s[j+1]!=s[i]; j=p[j] ) ;
			/*
			for ( i = 1; i <= n; ++i )
				System.out.println(p[i]);
			*/
			for ( i = 0; i <= n; ++i ) 
				row.put(i,new HashMap<>());
			for ( int ch = 0; ch < A; ++ch )
				for ( i = 0; i <= n; ++i )
					tr[i][ch] = root;
			for ( i = 0; i <= n-1; ++i ) 
				for ( int ch = 0; ch < A; ++ch )
					if ( ch == s[i+1] )
						tr[i][ch] = i+1;
					else {
						if ( p[i] != -1 )
							tr[i][ch] = tr[p[i]][ch];
						//for ( j = p[i]; j+1 > 0 && s[j+1] != ch; j = p[j] ) ;
						//tr[i][ch] = j+1;
					}
			row.get(0).put(0,-1.00/A);
			row.get(0).put(1,P=1.00/A);
			for ( b[0] = -1, i = 1; i <= n-1; add(row.get(i),i,-1), b[i++] = -1 ) 
				for ( int ch = 0; ch < A; ++ch )
					add(row.get(i),tr[i][ch],P);
			b[n] = 0; add(row.get(n),n,-1);
			i = n; t = 0;
			for ( j = 0; j <= n; a[t][j++] = 0 ) ;
			for ( Map.Entry<Integer,Double> entry: row.get(i).entrySet() )
				a[t][entry.getKey()] += entry.getValue();
			--i; t ^= 1;
			for ( j = 0; j <= n; a[t][j++] = 0 ) ;
			for ( Map.Entry<Integer,Double> entry: row.get(i).entrySet() )
				a[t][entry.getKey()] += entry.getValue();
			for ( j = n; j >= 1; --j ) {
				/*for ( k = 0; k <= n; ++k ) 
					System.out.print(a[t][k].toStr()+" ");
				System.out.println("");
				for ( k = 0; k <= n; ++k ) 
					System.out.print(a[t^1][k].toStr()+" ");
				System.out.println("");*/
				double cf = a[t][j]/a[t^1][j];
				for ( k = 0; k <= n; ++k )
					a[t][k] -= cf*a[t^1][k];
				b[j-1] -= cf*b[j];
				if ( j >= 2 ) {
					for ( k = 0; k <= n; a[t^1][k++] = 0 ) ;
					for ( Map.Entry<Integer,Double> entry: row.get(j-2).entrySet() )
						a[t^1][entry.getKey()] += entry.getValue();
					t ^= 1;
				}
			}
			double ans = Math.log10(b[0]/a[t][0]);
			System.out.println(String.format("%d",(long)(Math.pow(10.00,ans))));
		}
	}
}

