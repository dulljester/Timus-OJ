/*
 * 1269.
 * TOPIC: AC automaton
 */
import java.util.*;
import java.io.*;

public class Main1269v2 {

	public static void main( String [] args ) { new Main1269v2().go(); }
	int n,m;

	private static class Cell {
		Map<Character,Cell> son = new HashMap<>();
		Cell slink;
		boolean flag = false;
		short len;
		Cell() {
			this.len = 0;
			slink = null;
			son.clear();
			flag = false ;
		}
		void add( char ch ) {
			Cell x;
			son.put(ch,x = new Cell());
			x.len = (short)(this.len+((short)1));
		}
		void add( char ch, Cell x ) {
			son.put(ch,x);
		}
	}

	Cell root, q0;

	void push( char []s, int len ) {
		int i = 0;
		Cell x = root;
		for ( ;i < len && !x.flag; x = x.son.get(s[i++]) ) 
			if ( !x.son.containsKey(s[i]) )
				x.add(s[i]);
		x.flag = true ;
	}

	Set<String> words = new TreeSet<>();

	void go() {
		int i,j,k;
		String str;
		Cell x,y,z;
		Queue<Cell> q = new LinkedList<>();
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in,"ISO-8859-1"));
			n = Integer.parseInt(br.readLine());
			q0 = new Cell();
			root = new Cell();
			Set<Character> symbols = new HashSet<>();
			for ( i = 0; i < n; ++i ) {
				str = br.readLine();
				words.add(str);
				for ( j = 0; j < str.length(); ++j )
					symbols.add(str.charAt(j));
			}
			for ( String t: words )
				push(t.toCharArray(),t.length());
			for ( Character ch: symbols )
				q0.add(ch,root);
			root.slink = q0;
			for ( Map.Entry<Character,Cell> entry: root.son.entrySet() ) {
				x = entry.getValue();
				x.slink = root;
				q.add(x);
			}
			while ( !q.isEmpty() ) {
				x = q.poll();
				for ( Map.Entry<Character,Cell> entry: x.son.entrySet() ) {
					y = entry.getValue();
					for ( z = x.slink; !z.son.containsKey(entry.getKey()); z = z.slink );
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


