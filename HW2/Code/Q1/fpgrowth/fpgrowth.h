/*----------------------------------------------------------------------
  File    : fpgrowth.h
  Contents: fpgrowth algorithm for finding frequent sets
  Author  : Bart Goethals
  Update  : 4/4/2003
  ----------------------------------------------------------------------*/

class FPgrowth
{
 public:

  FPgrowth();
  ~FPgrowth();

  void setData(char *file, int type){data = new Data(file,type);}
  void setMinsup(unsigned ms){minsup = ms;}
  void setOutput(char *of);
  int mine();

 private:

  unsigned minsup;
  Data *data;
  FPtree *fpt;
	
  FILE *out;
};
