// AutoCali.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 4月  3 20:40:58 2019 (+0800)
// Last-Updated: 四 4月 18 18:26:39 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 8
// URL: http://wuhongyi.cn 

#ifndef _AUTOCALI_H_
#define _AUTOCALI_H_

#include "TGraph.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TSpectrum.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// flag 1 == Eu152
// flag 2 == Co60
// flag 3 == Ba133
// flag 4 == Am241
// flag 5 == Pu239
#define COUNTERMAX 20

class AutoCali
{
public:
  AutoCali(TH1D *h, int flag);
  virtual ~AutoCali();

  bool SearchPeak();

  void GetEu152Pars(int n,bool *f,double *x,double *y);
  void GetCo60Pars(int n,bool *f,double *x,double *y);
  
private:
  void FlagEu152(int n);
  void FlagCo60(int n);

  
protected:
  TH1D *rawhist;
  TH1D *bghist;
  TH1D *realhist;

  TSpectrum *spec;
  Double_t *xpeaks;
  Double_t *ypeaks;
  
  int sourceflag;

  double PeaksThreshold;
  Int_t NoPeaks;

  bool fPeakFlag[COUNTERMAX];
  double fPeak[COUNTERMAX];
  // Eu152
  // 0->121.78  1->244.70  2->344.28  3->778.90  4->964.08  5->1085.9  6->1112.1  7->1408.0 
  double Eu152[8] = {121.78,244.70,344.28,778.90,964.08,1085.9,1112.1,1408.0};
  // Co60
  // 0->1173.2  1->1332.5
  double Co60[2] = {1173.2,1332.5};
  
};

#endif /* _AUTOCALI_H_ */
// 
// AutoCali.hh ends here















