/*
 * status: Accepted
 */
import java.util.regex.*;
import java.util.*;
import java.io.*;

public class Main {
	private final static Pattern p = Pattern.compile("([A-Za-z]+)");
	private final static int N = (1<<14), oo = (1<<30);
	int []c = new int[N];
	int [][]z = new int[2][N];
	int n;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	int f( int t, int n ) {
		if ( z[t][n] > -oo )
			return z[t][n];
		if ( t == 0 && n == 0 ) 
			return z[t][n] = 0;
		if ( t == 1 && n == 0 )
			return z[t][n] = -oo;
		assert n >= 1;
		if ( t == 0 ) 
			return z[t][n] = Math.max(f(0,n-1),f(1,n-1));
		if ( f(0,n-1) > -oo )
			return z[t][n] = c[n]+f(0,n-1);
		return z[t][n];
	}
	void go() throws Exception {
		String s;
		int i,j,k,t;
		for ( n = 0; (s = br.readLine()) != null; ) {
			Matcher m = p.matcher(s);
			for ( ;m.find(); c[++n] = m.group(1).length() ) ;
		}
		for ( t = 0; t <= 1; ++t )
			for ( i = 0; i <= n; z[t][i++] = -oo ) ;
		System.out.println(Math.max(f(0,n),f(1,n)));
	}
}

