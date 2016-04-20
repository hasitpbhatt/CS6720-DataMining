package openBabel;

import java.io.FileNotFoundException;

import graph.Graph;
import tool.BuildGraph;
import tool.FileUtils;
import ctree.util.Opt;

public class Graph2Smiles {

	/**
	 * @param args
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//Opt opt=new Opt(args);
		Graph[] graphdb=BuildGraph.loadGraphs("/home/panks/Downloads/mol/C16218.mol");
		StringBuffer s=new StringBuffer("");
		for (Graph g:graphdb)
		{
			s.append(g.getSmiles().getSmileRep()+"\n");
		}
		System.out.println(s.toString());
	}

}
