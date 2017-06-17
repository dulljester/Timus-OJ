/*
 * 1269.
 * TOPIC: AC automaton
 */
import java.util.*;
import java.io.*;

public class Main1269 {
	
	public static void main( String [] args ) { new Main1269().go(); }
	int n,m;

	private class Cell {
		Cell slink,sibling = null,son = null;
		boolean flag = false;
		short len;
		byte ch;
		Cell( byte ch ) {
			this.ch = ch;
			this.len = 0;
		}
		void add( byte ch ) {
			Cell x = new Cell(ch);
			x.len = (short)(this.len+((short)1));
			x.sibling = this.son;
			this.son = x;
		}
	}

	Cell root;

	void push( byte []s, int len ) {
		int i = 0;
		Cell x = root,y = null;
		for ( ;i < len; ++i, x = y ) {
			for ( y = x.son; y != null && y.ch != s[i]; y = y.sibling ) ;
			if ( y == null ) {
				y = new Cell(ch);
				y.sibling = x.son;
				x.son = y;
			}
		}
		x.flag = true ;
	}

	void go() {
		int i,j,k;
		String str;
		Cell x,y,z;
		Queue<Cell> q = new LinkedList<>();
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in,"ISO-8859-1"));
			n = Integer.parseInt(br.readLine());
			root = new Cell(); root.slink = null;
			Set<Character> symbols = new HashSet<>();
			for ( i = 0; i < n; ++i ) {
				str = br.readLine();
				for ( j = 0; j < str.length(); ++j )
					symbols.add(str.charAt(j));
				push(str.toCharArray(),str.length());
			}
			for ( x = root.son; x != null; x = x.sibling ) {
				x.slink = root;
				q.add(x);
			}
			while ( !q.isEmpty() ) {
				x = q.poll();
				for ( y = x.son; y != null; y = y.sibling ) {
					for ( z = x.slink; z != null && !z.son.containsKey(entry.getKey()); z = z.slink );
					y.slink = z.son.get(entry.getKey());
					y.flag |= y.slink.flag;
					q.add(y);
				}
			}
			m = Integer.parseInt(br.readLine());
			boolean ok = true ;
			for ( k = 0; k < m && ok; ++k ) {
				str = br.readLine();
				int len = str.length();
				for ( x = root, i = 0; i < len && ok; ++i ) {
					char ch = str.charAt(i);
					if ( x.flag ) {
						System.out.println((k+1)+" "+(i+1-x.len));
						ok = false ;
						break ;
					}
					if ( x.son.containsKey(ch) ) 
						x = x.son.get(ch);
					else {
						if ( !symbols.contains(ch) ) {
							x = root;
							continue ;
						}
						for ( y = x.slink; y != null && !y.son.containsKey(ch); y = y.slink ) ;
						if ( y == null )
							x = root;
						else x = y.son.get(ch);
					}
				}
				if ( ok && x.flag ) {
					System.out.println((k+1)+" "+(i+1-x.len));
					ok = false ;
				}
			}
			if ( ok ) System.out.println("Passed");
		} catch ( Exception e ) {
			throw new RuntimeException(e);
		}
	}
};

