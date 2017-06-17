/*60805EX*/

import java.util.*;
import java.math.BigInteger;

public class Main1677 {
	Scanner scan = new Scanner(System.in);
	private static final int N = (1<<15), MAXA = 26;
	Frac[][]a = new Frac[2][N];
	Frac[]b = new Frac[N];
	Frac P;
	int []p = new int[N], s;
	int n,A;
	Map<Integer,Map<Integer,Frac>> row = new HashMap<>();
	int [][]tr = new int[N][MAXA];
	public static void main( String [] args ) {
		new Main1677().go();
	}
	private void add( Map<Integer,Frac> m, int key, Frac val ) {
		if ( m.containsKey(key) )
			m.put(key,m.get(key).add(val));
		else 
			m.put(key,val);
	}

	private static class Frac {
		static Frac ZERO = new Frac(0);
		BigInteger x,y;
		Frac( int x, int y ) {
			this.x = BigInteger.valueOf(x);
			this.y = BigInteger.valueOf(y);
		}
		Frac( BigInteger x, BigInteger y ) {
			this.x = x;
			this.y = y;
		}
		Frac add( Frac other ) {
			BigInteger a = this.x.multiply(other.y).add(this.y.multiply(other.x));
			BigInteger b = this.y.multiply(other.y);
			BigInteger d = a.gcd(b);
			a = a.divide(d);
			b = b.divide(d);
			return new Frac(a,b);
		}
		Frac sub( Frac other ) {
			BigInteger a = this.x.multiply(other.y).subtract(this.y.multiply(other.x));
			BigInteger b = this.y.multiply(other.y);
			BigInteger d = a.gcd(b);
			a = a.divide(d);
			b = b.divide(d);
			return new Frac(a,b);
		}
		Frac reciprocal() {
			return new Frac(y,x);
		}
		Frac multiply( Frac other ) {
			BigInteger a = this.x.multiply(other.x);
			BigInteger b = this.y.multiply(other.y);
			BigInteger d = a.gcd(b);
			a = a.divide(d);
			b = b.divide(d);
			return new Frac(a,b);
		}
		Frac( int x ) {
			this.x = BigInteger.valueOf(x);
			this.y = BigInteger.ONE;
		}
		public String toString() {
			return x.divide(y)+"";
		}
		String toStr() {
			if ( y.compareTo(BigInteger.ZERO) < 0 ) {
				x = x.negate();
				y = y.negate();
			}
			return x+"/"+y;
		}
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
			for ( j=p[0]=-1, i = 1; i <= n; p[i++] = ++j ) 
				for ( ;j+1 > 0 && s[j+1] != s[i]; j = p[j] ) ;
			for ( i = 0; i <= n; ++i ) 
				row.put(i,new HashMap<>());
			for ( int ch = 0; ch < A; ++ch )
				for ( i = 0; i < A; ++i )
					tr[i][ch] = root;
			for ( i = 0; i <= n-1; ++i ) 
				for ( int ch = 0; ch < A; ++ch )
					if ( ch == s[i+1] )
						tr[i][ch] = i+1;
					else if ( p[i] != -1 )
						tr[i][ch] = tr[p[i]][ch];
			row.get(0).put(0,new Frac(-1,A));
			row.get(0).put(1,P = new Frac(1,A));
			for ( b[0] = new Frac(-1), i = 1; i <= n-1; add(row.get(i),i,new Frac(-1)), b[i++] = new Frac(-1) ) 
				for ( int ch = 0; ch < A; ++ch )
					add(row.get(i),tr[i][ch],P);
			b[n] = new Frac(0); add(row.get(n),n,new Frac(-1));
			i = n; t = 0;
			for ( j = 0; j <= n; a[t][j++] = Frac.ZERO ) ;
			for ( Map.Entry<Integer,Frac> entry: row.get(i).entrySet() )
				a[t][entry.getKey()] = a[t][entry.getKey()].add(entry.getValue());
			--i; t ^= 1;
			for ( j = 0; j <= n; a[t][j++] = Frac.ZERO ) ;
			for ( Map.Entry<Integer,Frac> entry: row.get(i).entrySet() )
				a[t][entry.getKey()] = a[t][entry.getKey()].add(entry.getValue());
			for ( j = n; j >= 1; --j ) {
				/*for ( k = 0; k <= n; ++k ) 
					System.out.print(a[t][k].toStr()+" ");
				System.out.println("");
				for ( k = 0; k <= n; ++k ) 
					System.out.print(a[t^1][k].toStr()+" ");
				System.out.println("");*/
				Frac cf = a[t][j].multiply(a[t^1][j].reciprocal());
				for ( k = 0; k <= j; ++k )
					a[t][k] = a[t][k].sub(cf.multiply(a[t^1][k]));
				b[j-1] = b[j-1].sub(cf.multiply(b[j]));
				if ( j >= 2 ) {
					for ( k = 0; k <= n; a[t^1][k++] = Frac.ZERO ) ;
					for ( Map.Entry<Integer,Frac> entry: row.get(j-2).entrySet() )
						a[t^1][entry.getKey()] = a[t^1][entry.getKey()].add(entry.getValue());
					t ^= 1;
				}
			}
			System.out.println(b[0].multiply(a[t][0].reciprocal()));
		}
	}
}

