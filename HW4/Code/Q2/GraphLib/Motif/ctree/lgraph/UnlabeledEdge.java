package ctree.lgraph;

import ctree.graph.*;

/**
 * <p>
 * Closure-tree
 * </p>
 * 
 * @author Huahai He
 * @version 1.0
 */
public class UnlabeledEdge implements Edge {
	protected boolean containsNull;
	protected int v1, v2, w;

	public UnlabeledEdge() {
	}

	public UnlabeledEdge(int _v1, int _v2, boolean _containsNull) {
		v1 = _v1;
		v2 = _v2;
		w = 0;
		containsNull = _containsNull;
	}

	public UnlabeledEdge(int _v1, int _v2, int _w, boolean _containsNull) {
		v1 = _v1;
		v2 = _v2;
		w = _w;
		containsNull = _containsNull;
	}

	public int v1() {
		return v1;
	}

	public int v2() {
		return v2;
	}

	/**
	 * compatible
	 * 
	 * @return boolean
	 */
	public boolean mappable(Edge e) {
		return e instanceof UnlabeledEdge;
	}

	public String toString() {
		String s = v1 + " " + v2+ " "+w;
		if (containsNull) {
			s += "|null";
		}
		return s;

	}

	@Override
	public int w() {
		// TODO Auto-generated method stub
		return w;
	}

}
