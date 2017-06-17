/*
 * status: Accepted
 */
import java.util.*;
import java.math.BigInteger;
import java.math.BigDecimal;

public class Main1677v3 {
	private static final int N = (1<<15), MAXA = 26;
	Scanner scan = new Scanner(System.in);

	int []p = new int[N], s;
	int n,A;

	public static void main( String [] args ) {
		new Main1677v3().go();
	}

	private void go() {
		String str;
		int i,j,k,t,root = 0;
		for ( ;scan.hasNext(); ) {
			A = scan.nextInt();
			str = scan.next();
			n = str.length();
			s = new int[n+1];
			for ( i = 0; i < n; ++i ) s[i+1] = str.charAt(i)-'a';
			for ( j=p[0]=-1,i=1; i<=n; p[i++]=++j ) 
				for (;j+1>0 && s[j+1]!=s[i]; j=p[j] ) ;
			BigInteger x = BigInteger.valueOf(1), ans = BigInteger.ZERO, BA = BigInteger.valueOf(A);
			Set<Integer> set = new TreeSet<>();
			for ( i = n, set.add(i), i = p[i]; i > 0; set.add(i), i = p[i] ) ;
			k = 0;
			for ( Integer m: set ) {
				for ( i = k+1; i <= m; ++i )
					x = x.multiply(BA);
				//ans = ans.add(x.pow(m));
				ans = ans.add(x);
				k = m;
			}
			System.out.println(ans);
		}
	}
}

