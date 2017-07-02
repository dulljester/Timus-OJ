/*
 * TOPIC: dp, combinatorics, recurrences
 * status: Accepted
 */
import java.math.BigInteger;
import java.io.*;
import java.util.*;

public class Main {
	BigInteger []z = new BigInteger[1<<14];
	Scanner scan = new Scanner(System.in);
	int K;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	static BigInteger []deg = new BigInteger[1<<14];
	static {
		deg[0] = BigInteger.ONE;
		for ( int k = 1; k < (1<<14); ++k )
			deg[k] = deg[k-1].add(deg[k-1]);
	}
	BigInteger calcZ( int n ) {
		if ( n <= 0 )
			return BigInteger.ONE;
		if ( z[n] != null )
			return z[n];
		if ( n <= K )
			return z[n] = deg[n];
		z[n] = calcZ(n-1).add(calcZ(n-1)).subtract(calcZ(n-2-K));
		return z[n];
	}
	void go() throws Exception {
		int n = scan.nextInt();
		K = scan.nextInt();
		System.out.println(calcZ(n));
	}
}

