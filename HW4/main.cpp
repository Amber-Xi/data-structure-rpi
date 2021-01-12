#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint; 


// FUNCTION PROTOTYPES
int dambeq();
int nw_jtj();
bool igbm(double pexjk, double clnx);
void ceppe(int* gyixwq, int qafk);
bool vgzj(int ljdsq[4], char* aapnu, int vumsyq, const char* iwzc);
bool uus_yg(int ntvi, char** rfbow, char*& eddnul, int& p_nuq_);
unsigned int wmlnaf(unsigned int tnejp);
int wlid();
float brko(int tx_d, int clnx, int rcogu, int xygg, int wvakpt);
int panjm(int jhkg, int ozns);
bool gersa(const std::vector<int> toxx_, const std::vector<int> lu_bu);
int acgjz();
int ntns(std::vector<int>& eujjll);



/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If iwzc is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool vgzj(int ljdsq[4], char* aapnu, int vumsyq, const char* iwzc) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int wmbuey = 0;
  int rhlrab = 0;
  int ghpkgf[4];
  bool wgyir = true;
  char fvrsg[1024];
  int hbzs = 0;

  for(; wmbuey < vumsyq; wmbuey += 16) {
    ceppe(ghpkgf, ljdsq[rhlrab]);
    rhlrab++;
    if(rhlrab > 3) rhlrab = 0;
    unsigned char* gfwriv = (unsigned char*) &aapnu[wmbuey];
    unsigned char* nuacmx = (unsigned char*) ghpkgf;
    for(int heisl=0; heisl<16; ++heisl, ++gfwriv, ++nuacmx) {
      if(wmbuey+heisl >= vumsyq) break;
      char brw_r = *gfwriv ^ *nuacmx;
      if((brw_r < 32 || brw_r > 126) && brw_r != '\n' && brw_r != '\t') {
	wgyir = false;
      }
      fvrsg[hbzs] = brw_r;
      hbzs++;
      // putc(brw_r, stdout);
    }
  }
  fvrsg[hbzs] = '\0';
  if(iwzc[0] != '\0') {
    std::ofstream izwupw(iwzc, std::ofstream::binary);
    if(!izwupw.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    izwupw.write(fvrsg,vumsyq);
  }
  for(int jfsq=0; jfsq<vumsyq; ++jfsq) {
    putc(fvrsg[jfsq], stdout);
  }
  std::cout << std::endl << std::endl;
  return wgyir;
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   panjm(3,4) should be 5
   panjm(3,5) should be 4
*/
int panjm(int jhkg, int ozns) {
  double wvdst; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // jhkg and y are both legs
  float tnxq = jhkg*jhkg + ozns*ozns;
  float rspic = modf(sqrt(tnxq), &wvdst);
  if(rspic == 0)// AMBER
  {
    return (int) wvdst;
  }
  // jhkg is the hypotenuse, need to subtract instead of add
  float aiwwyc = abs(ozns*ozns - jhkg*jhkg);
  rspic = modf(sqrt(aiwwyc), &wvdst);
  if(rspic == 0)// AMBER
  {
    return (int) wvdst;
  }
    return -1;
}


int wlid() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> idjwy;
 for(char lggvlu = 'a'; lggvlu <= 'z'; lggvlu++) {//AMBER
    idjwy.push_back(lggvlu);
  }
  for(char lggvlu = 'Z'; lggvlu >= 'A'; lggvlu--) {//AMBER
    idjwy.push_front(lggvlu);
  }
  assert(idjwy.back() == 'z');
  assert(idjwy.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> ckgdyc;
  for(int vfpdky=1; vfpdky<=500; ++vfpdky) {
    ckgdyc.push_back(vfpdky);
  }
  assert(*ckgdyc.begin() == 1);

  const int tbox = 7;
  const int ncnp = 11;
  // remove every number from the list that is a multiple of at least one of
  // these ssmxiz
  for(std::list<int>::iterator btimc = ckgdyc.begin(); btimc != ckgdyc.end(); ++btimc) {
    if(*btimc % tbox == 0 || *btimc % ncnp == 0) {//AMBER
      btimc=ckgdyc.erase(btimc);
        btimc--;//Amber
    }
  }

  // make a list
  std::list<std::string> flbfdw;
  flbfdw.push_front("banana");
  flbfdw.push_back("fig");
  flbfdw.push_back("iodine");
  flbfdw.push_front("yellow squash");
  flbfdw.push_front("grape");
  flbfdw.push_front("durian");
  flbfdw.push_front("pomegranate");
  flbfdw.push_back("huckleberry");
  flbfdw.push_front("zwetschge");
  flbfdw.push_back("strawberry");
  flbfdw.push_back("tangerine");
  flbfdw.push_back("jujube");
  flbfdw.push_back("lemon");
  flbfdw.push_back("mango");
  flbfdw.push_front("orange");
  flbfdw.push_back("cherry");
  flbfdw.push_front("nectarine");
  flbfdw.push_back("uglyfruit");
  flbfdw.push_front("vapor");
  flbfdw.push_front("quart");
  flbfdw.push_back("apple");
  flbfdw.push_front("elderberry");
  flbfdw.push_front("raspberry");
  flbfdw.push_back("watermelon");
  flbfdw.push_back("kiwi");
  flbfdw.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> qangui;
  qangui.push_back("iodine");
  qangui.push_back("yellow squash");
  qangui.push_back("vapor");
  qangui.push_back("quart");
  qangui.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator yfxeo;
  for(std::list<std::string>::reverse_iterator qjdob = qangui.rbegin();
      qjdob != qangui.rend(); qjdob++) {
    yfxeo = std::find(flbfdw.begin(), flbfdw.end(), *qjdob);
    flbfdw.erase(yfxeo);//AMBER
  }

  // verify fruits list
  for(std::list<std::string>::iterator wjwci = flbfdw.begin(); wjwci != flbfdw.end(); ++wjwci) {
    std::cout << *wjwci << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from idjwy.
  for(std::list<std::string>::iterator wjwci = flbfdw.begin(); wjwci != flbfdw.end(); ++wjwci) {
    for(uint r_igv=0; r_igv<wjwci->size(); ++r_igv) {
      idjwy.remove((*wjwci)[r_igv]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int wdper = 0;
  for(std::list<char>::iterator wjwci = idjwy.end(); wjwci != idjwy.begin(); wjwci--) {
    if(*wjwci < 'a' || *wjwci > 'z') {
      continue;//AMBER
    }
    wdper++;
  }

  std::cout << wdper << " letters did not ever appear in the fruit names." << std::endl;

  assert(*idjwy.begin() == 'A');
  assert(*(--idjwy.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int xucb = flbfdw.size();
  std::list<char>::iterator lgsa = idjwy.begin();
  std::advance(lgsa, 20);
  for(; lgsa != idjwy.end(); ++lgsa) {
    xucb += *lgsa;
    if (xucb % 3) {
      xucb *= wdper;
      xucb -= *lgsa;
    }
  }
  for(std::list<std::string>::iterator aawmm_ = flbfdw.begin(); aawmm_ != flbfdw.end(); ++aawmm_){
    xucb -= (*aawmm_)[2];
  }
  for(std::list<int>::iterator lhvyn = ckgdyc.begin(); lhvyn != ckgdyc.end(); ++lhvyn) {
    xucb += *lhvyn;
  }
  return xucb;
  //********************************************************************************
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool uus_yg(int argc, char** argv, char*& eddnul,
		     int& p_nuq_) {

  // Error checking on command line arguments
  if(argc != 4) {//AMBER
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream ypu_(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!ypu_) {//AMBER
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int wyom;

  // make an array of bytes to hold this information
  

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  ypu_.seekg(0, ypu_.end);
  wyom = ypu_.tellg();
  ypu_.seekg(0, ypu_.beg);
    char* y_mxbf = new char[wyom];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  ypu_.read(y_mxbf, wyom);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << ypu_.gcount() << " bytes of data."
	    << std::endl;
  assert(ypu_.gcount() == wyom);//AMBER

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  p_nuq_ = wyom;
  eddnul = y_mxbf;
  return true;
  //********************************************************************************
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float brko(int tx_d, int clnx, int rcogu, int xygg, int wvakpt) {
  float wzhuae = ((((tx_d / float(clnx)) / rcogu) / xygg) / wvakpt);
  return wzhuae;
}


int dambeq() {

  // set up some variables
  int iglzqy = 10;
  int pdltbf = 46;
  int ixgn = 4;
  int vgxcd = ixgn - pdltbf; // -42
  int uinb = pdltbf - 3*iglzqy + 4*ixgn; //  32
  int ancy = 2*pdltbf + 2*ixgn; //  100
  int einv_ = uinb - (pdltbf / ixgn) + vgxcd + 20; // -1 
  int qdcgba = (ancy / ixgn) / iglzqy+1; //  3 //AMBER
  int l_fhjf = (vgxcd / qdcgba) / 7; // -2 
  int ewakqh = einv_ + l_fhjf; // -3 
  int btnfyw = (ancy / uinb) - qdcgba-1; // -1//AMBER
  int rclhlj = ancy + 2*vgxcd; // 16
  int gldg = einv_ + l_fhjf + btnfyw + ewakqh -1; // -8 //AMBER
  float djher = iglzqy /float(ancy); // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << brko(ancy, einv_, ixgn, 5, einv_)
	    << " (expected 5)." << std::endl;

  assert(brko(ancy,einv_,ixgn,5,einv_) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << brko(840, vgxcd, l_fhjf, btnfyw, 1)
	    << " (expected -10)." << std::endl;

  assert(brko(840, vgxcd, l_fhjf, btnfyw, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << brko(320, gldg, btnfyw, iglzqy, l_fhjf)
	    << " (expected -2)." << std::endl;

  assert(brko(320, gldg, btnfyw, iglzqy, l_fhjf) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << brko((uinb*ancy*-1), btnfyw, rclhlj, gldg, (iglzqy/2))
	    << " (expected -5)." << std::endl;

  assert(brko(uinb*ancy*-1, btnfyw, rclhlj, gldg, (iglzqy/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float jd_vg = brko(ancy*10, iglzqy, iglzqy, iglzqy, iglzqy);
  std::cout << "Multidivide: " << jd_vg
	    << " (expected 0.1)." << std:: endl;

  assert(igbm(jd_vg, djher));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (l_fhjf+gldg) ^ rclhlj ^ ((int) jd_vg) ^ (vgxcd*uinb*ancy*einv_*qdcgba);
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void ceppe(int* gyixwq, int qafk) {
  *(gyixwq+((qafk+1962) & 3)) = qafk ^ 3735928559u; 
  *(gyixwq+((qafk+1492) & 3)) = qafk ^ 3056505882u; 
  *(gyixwq+((qafk+'G') & 3)) = qafk ^ 01353340336u; 
  *(gyixwq+((qafk+1) & 3)) = qafk ^ 3405691582u; 
  int qjpny = 1;
  char ymhzm = 0;
  char* ofkpz = (char*) gyixwq;
  for(qjpny = 32767; qjpny<32783; qjpny++) {
    for(ymhzm=7; ymhzm >= 0; --ymhzm) {
      if(((*ofkpz)>>ymhzm) & 1) (*ofkpz) ^= (qafk >> (ymhzm/2)*8) & 255;
      else (*ofkpz) = (((*ofkpz)<<5) & 224) | (((*ofkpz)>>3) & 31);
      if(*ofkpz & 4) (*ofkpz = ~(*ofkpz));
    }
    ++ofkpz;
  }
}


int nw_jtj() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int hmgo = 25;
  int** ljdsq = new int*[hmgo];
  for(int gwcnpy=0; gwcnpy<hmgo; ++gwcnpy)
  {

    ljdsq[gwcnpy] = new int[hmgo];

    for(int wvp_u=0; wvp_u<hmgo; ++wvp_u)//AMBER
    {
        ljdsq[gwcnpy][wvp_u] = 0;
    }
  }
  // sanity check: corners of array
  assert(ljdsq[1][1] == 0);
  assert(ljdsq[1][24] == 0);//AMBER
  assert(ljdsq[24][1] == 0);//AMBER
  assert(ljdsq[24][24] == 0);//AMBER

  // store pythagorean numbers in ljdsq
  for(int gwcnpy=0; gwcnpy<hmgo; ++gwcnpy) {//AMBER
    for(int wvp_u=0; wvp_u<hmgo; ++wvp_u) {//AMBER
      ljdsq[gwcnpy][wvp_u] = panjm(gwcnpy, wvp_u);

    }
  }
    
  // do some checks
  assert(ljdsq[1][2] == -1); // no triple exists
  assert(ljdsq[3][4] == 5);
  assert(ljdsq[5][4] == 3);
  assert(ljdsq[13][12] == 5);
  assert(ljdsq[8][15] == 17);
  assert(ljdsq[8][16] != 17);
  assert(ljdsq[17][8] == 15);
  assert(ljdsq[5][3] == ljdsq[3][5]);
  assert(ljdsq[7][24] == 25);
  assert(ljdsq[12][16] == 20); // 3-4-5 triple times 4
  assert(ljdsq[5][15] == -1);
  assert(ljdsq[24][7] != -1);

  /* Now iterate over and print ljdsq, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** fawbg = ljdsq;
  for(int gwcnpy = 1; gwcnpy <= hmgo; ++gwcnpy, ++fawbg) {//AMBER
    int* kvctc = *fawbg;
    for(int wvp_u = 1; wvp_u <= hmgo; ++wvp_u, ++kvctc) {//AMBER
      int vhnuig = *kvctc;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string edrrn = ((vhnuig < 10 && vhnuig != -1) ? " " : "");//Amber
      std::cout << edrrn << *kvctc << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int sguefu = 0;
  for(int gwcnpy=5; gwcnpy<18; ++gwcnpy) {
    for(int wvp_u=3; wvp_u<10; ++wvp_u) {
      sguefu += ljdsq[gwcnpy][wvp_u];
    }
  }
  for(int gwcnpy=0; gwcnpy<hmgo; ++gwcnpy) {
    delete [] ljdsq[gwcnpy];
  }
  delete [] ljdsq;
  return sguefu;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in togp is strictly greater than the corresponding number in
   twobsk, return true; otherwise return false. */
bool gersa(const std::vector<int> togp, const std::vector<int> twobsk) {
  bool tgzbpv = true;
  for(uint gfprfg=0; gfprfg<togp.size(); ++gfprfg) {
    if(togp[gfprfg] <= twobsk[gfprfg]) {//AMBER
      tgzbpv = false;
    }
  }
  return tgzbpv;
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int wmlnaf(unsigned int tnejp) {
  union __sys_rcu_tdb_ {
    unsigned int wkzvy;
    float upcvh;
  } wngmq;
  wngmq.wkzvy = (tnejp * 27828) + 1456694363;
  wngmq.upcvh /= 1024;
  wngmq.wkzvy ^= 1672983815;
  wngmq.wkzvy += (tnejp * tnejp ^ (tnejp + wngmq.wkzvy));
  unsigned int wfbme = (wngmq.wkzvy >> 21) & 2047;
  unsigned int ejnk = (wngmq.wkzvy << 11) & 037777774000;
  wngmq.upcvh -= 10;
  wngmq.wkzvy ^= (wfbme | ejnk);
  return wngmq.wkzvy;
}

int acgjz() {

  // create a vector toxx_ with 7 entries of 25
  std::vector<int> toxx_(7, 25);
  // create another vector with entries 1-10
  std::vector<int> lu_bu;
  for(uint hxzpt=1; hxzpt<=10; ++hxzpt) {//AMBER
    lu_bu.push_back(hxzpt);
  }
  // and one with entries -5 to 5
  std::vector<int> u_qg;
  for(int ardzpo=-5; ardzpo<=5; ++ardzpo) {
    u_qg.push_back(ardzpo);
  }
  assert(u_qg[5] == 0);

  int xtae = ntns(toxx_);
  int gegxun = ntns(lu_bu);
  int vors = ntns(u_qg);
  assert(xtae == 175);
  assert(toxx_[2] == 75);
  assert(toxx_[5] == 150);
  assert(gegxun == 55);
  assert(lu_bu[2] == 6);
  assert(vors == 0);
  assert(u_qg[10] == 0);
  for(uint yadsy=0; yadsy<u_qg.size(); ++yadsy) { assert(u_qg[yadsy] <= 0); }
  int ybordy = ntns(toxx_);
  int hsak = ntns(lu_bu);
  assert(ybordy == 700);
  assert(toxx_[2] == 150);
  for(uint zknktq=0; zknktq<toxx_.size(); ++zknktq) { assert(toxx_[zknktq] != 225); }
  assert(toxx_[5] == 525);

  int lkfe =0;
  for(uint tccz=0; tccz<lu_bu.size(); ++tccz)
  {
    // count the number of multiples of 10 in lu_bu
    if(lu_bu[tccz] % 10 == 0)
    {
      lkfe++;
    }
  }
    
  // there should be 4 of them
  assert(lkfe == 4);


  // more vectors
  std::vector<int> mwwpvp;
  mwwpvp.push_back(4);
  mwwpvp.push_back(23);
  mwwpvp.push_back(18);
  mwwpvp.push_back(31);
  mwwpvp.push_back(167);
  mwwpvp.push_back(213);
  mwwpvp.push_back(86);
  std::vector<int> xywtpw;
  xywtpw.push_back(-7);
  xywtpw.push_back(10);
  xywtpw.push_back(806);
  xywtpw.push_back(211);
  // create owdfgo by concatenating mwwpvp and xywtpw
  std::vector<int> owdfgo(mwwpvp);
  for(uint zknktq=0; zknktq<xywtpw.size(); ++zknktq) { owdfgo.push_back(xywtpw[zknktq]); }

  assert(owdfgo.size() == 11);
  assert(owdfgo[6] == 86);
  assert(owdfgo[7] == -7);
  assert(owdfgo[10] == 211);

  // compare some vectors
  assert(gersa(toxx_, mwwpvp));   
  assert(! gersa(xywtpw, toxx_)); 
  assert(gersa(owdfgo, u_qg));   
  assert(! gersa(u_qg, owdfgo)); 
  assert(! gersa(lu_bu, xywtpw)); 
  assert(! gersa(owdfgo, toxx_)); 

  // now concatenate everything into a big vector
  std::vector<int> njtt(toxx_);
  njtt.insert(njtt.end(), lu_bu.begin(), lu_bu.end());
  njtt.insert(njtt.end(), u_qg.begin(), u_qg.end());
  // mwwpvp and xywtpw are already concatenated into owdfgo
  // so just concatenate that
  njtt.insert(njtt.end(), owdfgo.begin(), owdfgo.end());
  assert(njtt.size() == 39);

  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> mxbgxq;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
    
    lkfe = 0;
  for(uint ujie = 0; ujie < njtt.size(); ujie++)//AMBER
  {
    if(njtt[ujie] % 3 == 0)
    {
      //std::cout << njtt[ujie] << " is divisible by 3" << std::endl;
      lkfe++;
      mxbgxq.push_back(njtt[ujie]);//AMBER
    }
  }
    
  std::cout << "There are " << lkfe << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int vsqn=lkfe-1; vsqn >= 0; --vsqn) {//AMBER
    std::cout << "mxbgxq[" << vsqn << "] = " << mxbgxq[vsqn] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  lkfe += ybordy + hsak;
  lkfe += (njtt.size() == 40);
  for(uint tccz=13;tccz<24;++tccz) { lkfe += (int) njtt[tccz]; }
  lkfe *= ntns(mxbgxq)/2;
  return lkfe;
  //********************************************************************************
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool igbm(double pexjk, double clnx) {
  return (std::abs(pexjk-clnx) < 0.01);
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function PROBABLY contains NO bugs.
 * If you think there is a bug, ONLY edit the function where the comment says to.
 * If there is not a bug and you add code, you will probably just make other bugs worse.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = dambeq();

    // test if all bugs were fixed - passing the correct value to wmlnaf
    // will return this number
    if(wmlnaf(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! uus_yg(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = nw_jtj();
    if(wmlnaf(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = acgjz();
    if(wmlnaf(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = wlid();
    if(wmlnaf(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(vgzj(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
    //No code should be added past this point.
  }

}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. eujjll will be modified by this function.
   Used in vector operations. */
int ntns(std::vector<int>& eujjll) {
  for(uint vfpdky=1; vfpdky<eujjll.size(); ++vfpdky) {//AMBER
    eujjll[vfpdky] = eujjll[vfpdky] + eujjll[vfpdky-1];//AMBER
  }
  return eujjll[eujjll.size()-1];
}

