//package ctree.test;

import grank.graph.GraphFile;
import grank.graph.SubgraphIsom;

import java.io.IOException;
import java.util.*;
import java.io.*;

import ctree.index.*;
import ctree.alg.Ullmann2;
import ctree.alg.Ullmann3;
import ctree.graph.*;
import ctree.lgraph.LGraphFile;

public class CountFeatures {

	/**
	 * @param args
	 * @throws IOException
	 */
	
	
/**
Graph input format : 
 * #id
 * Number of Vertices
 * label of V[0]
 * label of V[1]
 * ...
 * 
 * Number of Edges
 * v1 v2 label
 * ...
 * ...
 *..
 Note that vertex labels are strings (can be integers also) where edge labels are integers only.
 */
	public static boolean check(Graph query1, Graph query2) {
		int[][] B = Util.getBipartiteMatrix2(query1, query2);			
		int[] map =Ullmann2.subgraphIsomorphism(Ullmann2.getAdjMat(query1), Ullmann2.getAdjMat(query2), B);

		return map != null;
	}

	// Subgraph isomorphism checker
	public static void main(String[] args) throws IOException {
		Graph graph1[] = LGraphFile
				.loadLGraphs(args[0]);
		Graph graph2[] = LGraphFile
				.loadLGraphs(args[1]);

		boolean matrix[][]=new boolean[graph2.length][graph1.length];

		boolean flag;
		int cnt = 0;
		for(Graph query1 : graph1) {
			flag = false;
			int cnt1 = 0;
			System.err.println(cnt);
			for(Graph query2 : graph2) {
				if(check(query1,query2) || check(query2,query1)) {
					//System.out.println("true");
					/*flag = true;
					break;*/
					matrix[cnt1][cnt] = true;
				}
				cnt1++;
			}
//			if(!flag)
//				System.out.println(""+cnt+" is awesome");
				cnt++;
		}

		Scanner scanner = new Scanner(System.in);

		if(args.length == 3)
		scanner = new Scanner(new File(args[2]));

		for(int i=0;i<graph2.length;i++) {
			if(args.length == 3) {
				int p = scanner.nextInt();
				if(p==1)
					System.out.print("1 ");
				else
					System.out.print("0 ");
			}
			for(int j=0;j<graph1.length;j++) {
				if(matrix[i][j]==true)
					System.out.print("1 ");
				else
					System.out.print("0 ");
			}
			System.out.println();
		}

		if(args.length == 3)
		scanner.close();

	}
}
