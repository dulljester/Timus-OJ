/*
 * 1158. Censored!
 * TOPIC: Aho-Corasick, DP
 * status: Accepted
 */
import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class Main1158 {
	private static final int MAXP = 10, MAXLEN = 0x10, MAXA = 0x80;
	public static void main( String [] args ) {
		new Main1158().go();
	}
	int n,m,P,V,A;
	int [][]words = new int[MAXP][MAXLEN];
	int []len = new int[MAXP];
	Map<Character,Integer> mp = new HashMap<>();
	Set<Cell> set = new HashSet<>();

	class Cell {
		Cell []son = new Cell[MAXA];
		Cell slink;
		int ch,id;
		Set<Integer> s = new HashSet<>();
		boolean flag = false ;
		Cell( int ch ) {
			this.ch = ch;
			s.clear();
			id = V++;
			set.add(this);
		}
		void add( int ch ) {
			this.s.add(ch);
			this.son[ch] = new Cell(ch);
		}
	}

	Cell root, q0;
	Queue<Cell> q = new LinkedList<>();

	void push( int []s, int len ) {
		Cell x = root;
		int i = 0;
		for ( ;i < len; x = x.son[s[i++]] )
			if ( !x.s.contains(s[i]) ) 
				x.add(s[i]);
		x.flag = true ;
	} 

	void go() {
		String str;
		int i,j,k;
		Cell x,y,z;
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in,"ISO-8859-1"));
			while ( null != (str = br.readLine()) ) {
				Scanner scan = new Scanner(str);
				n = scan.nextInt();
				m = scan.nextInt();
				P = scan.nextInt();
				mp.clear(); V = 0; set.clear();
				str = br.readLine();
				for ( i = 0; i < n; ++i ) 
					mp.put(str.charAt(i),i);
				for ( A = mp.size(), k = 0; k < P; len[k++] = i ) 
					for ( str = br.readLine(), i = 0; i < str.length(); ++i )
						words[k][i] = mp.get(str.charAt(i));
				q0 = new Cell(0); root = new Cell(1);
				for ( root.slink = q0, i = 0; i < A; ++i ) {
					q0.s.add(i);
					q0.son[i] = root;
				}
				for ( i = 0; i < P; push(words[i],len[i]), ++i ) ;
				for ( i = 0; i < A; ++i ) 
					if ( root.s.contains(i) ) {
						x = root.son[i];
						x.slink = root;
						q.add(x);
					}
				while ( !q.isEmpty() ) {
					x = q.poll();
					for ( Integer ch: x.s ) {
						y = x.son[ch];
						for ( z = x.slink; !z.s.contains(ch); z = z.slink ) ;
						y.slink = z.son[ch]; y.flag |= y.slink.flag;
						q.add(y);
					}
				}
				for ( i = 0; i < A; ++i )
					if ( root.s.contains(i) )
						q.add(root.son[i]);
					else {
						root.son[i] = root;
						root.s.add(i);
					}
				while ( !q.isEmpty() ) 
					for ( x = q.poll(), i = 0; i < A; ++i )
						if ( x.s.contains(i) )
							q.add(x.son[i]);
						else {
							for ( y = x.slink; !y.s.contains(i); y = y.slink ) ;
							x.son[i] = y.son[i];
							x.s.add(i);
						}
				BigInteger [][]tmp = new BigInteger[V][V], ax = new BigInteger[V][V], g = new BigInteger[V][V];
				int [][]G = new int[V][V];
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						ax[i][j] = (i==j?BigInteger.ONE:BigInteger.ZERO);
				for ( Cell e: set )
					if ( !e.flag )
						for ( x = e, i = 0; i < A; ++i )
							if ( !((y = x.son[i]).flag) ) 
								++G[x.id][y.id];
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						g[i][j] = BigInteger.valueOf(G[i][j]);
				for ( ;m > 0; m >>= 1 ) {
					if ( 1 == (m&1) ) {
						for ( i = 0; i < V; ++i )
							for ( j = 0; j < V; ++j )
								for ( tmp[i][j] = BigInteger.ZERO, k = 0; k < V; ++k )
									tmp[i][j] = tmp[i][j].add(ax[i][k].multiply(g[k][j]));
						for ( i = 0; i < V; ++i )
							for ( j = 0; j < V; ++j )
								ax[i][j] = tmp[i][j];
					}
					for ( i = 0; i < V; ++i )
						for ( j = 0; j < V; ++j )
							for ( tmp[i][j] = BigInteger.ZERO, k = 0; k < V; ++k )
								tmp[i][j] = tmp[i][j].add(g[i][k].multiply(g[k][j]));
					for ( i = 0; i < V; ++i )
						for ( j = 0; j < V; ++j )
							g[i][j] = tmp[i][j];
				}
				BigInteger ans = BigInteger.ZERO;
				for ( i = 0; i < V; ans = ans.add(ax[root.id][i++]) ) ;
				System.out.println(ans);
			}
		} catch ( Exception io ) {
		}
	}
}

