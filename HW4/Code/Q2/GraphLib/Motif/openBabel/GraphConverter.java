package openBabel;
import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Vector;

import tool.FileUtils;

import joelib2.io.BasicIOType;
import joelib2.io.BasicIOTypeHolder;
import joelib2.io.BasicReader;
import joelib2.io.MoleculeIOException;
import joelib2.molecule.Atom;
import joelib2.molecule.BasicConformerMolecule;
import joelib2.molecule.Bond;
import joelib2.molecule.Molecule;
import joelib2.util.iterator.AtomIterator;
import joelib2.util.iterator.BondIterator;

public class GraphConverter {

	/**
	 * @param args
	 * @throws IOException 
	 * @throws MoleculeIOException 
	 */
	public static void main(String[] args) throws IOException, MoleculeIOException {
		// TODO Auto-generated method stub
		BasicIOType inType = BasicIOTypeHolder.instance().getIOType("SDF");
		Molecule mol = new BasicConformerMolecule(inType, inType);
		
//		BasicReader reader=new BasicReader(args[0]);
		String pathS = "/Users/panks/tmp/testBabel/C";
		String num, finalP;
		File f;
		for(int k = 00634; k<= 20898; k++){
			num = Integer.toString(k);
			int tmp = 5 - num.length();
			for(int j=0; j < tmp; j++){
				num = "0"+ num;
			}
			finalP = pathS+num+".mol";
			System.out.println(finalP);
		
		f = new File(finalP);
		if(!f.exists()) continue;
		
		
		BasicReader reader=new BasicReader(finalP);

		int i=0;
		int numMol=0;
		Vector failed=new Vector<Integer>();
		StringBuffer s=new StringBuffer("");
		boolean more=true;
		while(more)
		{
			try
			{
				if(reader.readNext(mol))
				{
					numMol++;
					HashSet<Integer> hatoms=new HashSet<Integer>();
					int numAtoms=0;
					int numEdges=0;
					StringBuffer atomsRep=new StringBuffer("");
					StringBuffer edgeRep=new StringBuffer("");
		
					AtomIterator at=mol.atomIterator();
					BondIterator bt=mol.bondIterator();
					//Vector atoms=new Vector<String>();
					
					while(at.hasNext())
					{
						Atom a=at.nextAtom();
						numAtoms++;
						//if (a.toString().equals("H"))
						//{
							//hatoms.add(numAtoms);
							//continue;
						//}
						atomsRep.append(a.toString()+"\n");
						
					}
					
					while(bt.hasNext())
					{
						Bond b=bt.nextBond();
						int bi=b.getBeginIndex()-1;
						int ei=b.getEndIndex()-1;
						int bo=b.getBondOrder();
						//if (!hatoms.contains(bi) && !hatoms.contains(ei))
						{
							edgeRep.append(ei+" "+bi+" "+bo+"\n");
							numEdges++;
						}
					}
					//for (mol.)
					//System.out.println("read");
					s.append("#"+mol.getTitle()+"\n"+(numAtoms-hatoms.size())+"\n"+atomsRep.toString()+numEdges+"\n"+edgeRep.toString()+"\n");
				}
				else
					
					more=false;
			}
			catch (Exception e) {
				failed.add(numMol);
			}
		}

		FileUtils.writeToFile(finalP.replace(".sdf", ".txt"), s.toString());
		System.out.println("Failed to decode: "+failed.size()+" : "+failed.toString());
	}
		
	}

}
