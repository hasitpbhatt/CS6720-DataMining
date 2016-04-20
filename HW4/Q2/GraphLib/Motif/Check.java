//package ctree.test;

import grank.graph.GraphFile;
import grank.graph.SubgraphIsom;

import java.io.IOException;

import ctree.index.*;
import ctree.alg.Ullmann2;
import ctree.alg.Ullmann3;
import ctree.graph.*;
import ctree.lgraph.LGraphFile;

public class Check {

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

		boolean flag;
		int cnt = 0;
		for(Graph query1 : graph1) {
			flag = false;
			for(Graph query2 : graph2) {
				if(check(query1,query2)) {
					//System.out.println("true");
					flag = true;
					break;
				}
			}
			if(!flag)
				System.out.println(cnt);
				cnt++;
		}				
	}
}
