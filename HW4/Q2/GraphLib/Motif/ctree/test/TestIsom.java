package ctree.test;

import grank.graph.GraphFile;
import grank.graph.SubgraphIsom;

import java.io.IOException;

import ctree.index.*;
import ctree.alg.Ullmann2;
import ctree.alg.Ullmann3;
import ctree.graph.*;
import ctree.lgraph.LGraphFile;

public class TestIsom {

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
	
	// Subgraph isomorphism checker
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		/// Note that the edge labels in the graphs are not taken into account in 2 of the 3 available algos. 
		
		
		Graph query1 = LGraphFile
				.loadLGraphs(args[0])[0];
		Graph query2 = LGraphFile
				.loadLGraphs(args[1])[0];
		
		
		// This uses Ullman algo. guaranteed correctness. includes edge labels. Slowest.
		int[][] B = Util.getBipartiteMatrix2(query1, query2);			
		int[] map =Ullmann2.subgraphIsomorphism(Ullmann2.getAdjMat(query1), Ullmann2.getAdjMat(query2), B);
		System.out.println("Ullmann algo (including edge labels)");
		if(map  == null)
			System.out.println("false");
		else
			System.out.println("true");
		
		
		/*long time0 = System.currentTimeMillis();
		// This uses neighborbiased mapper - not always accurate but works well. Doesn't consider edge labels.
		boolean flag1 = Util.pseudoSubIsomorphic(query1, query2, 1);
		long time1 = System.currentTimeMillis() - time0;

		System.out.println("Neighborbiased mapper (ignoring edge labels)");
		System.out.println(flag1);
		
		// This uses ullmann algo. - guaranteed correctness.. Obviously slower. Doesn't consider edge labels.
		time0 = System.currentTimeMillis();
		boolean flag2 = Util.subIsomorphic(query1, query2);
		long time2 = System.currentTimeMillis() - time0;
		
		
		System.out.println("Ullmann algo (ignoring edge labels)");
		System.out.println(flag2);*/
	}
}
