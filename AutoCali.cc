// AutoCali.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 4月  3 20:41:16 2019 (+0800)
// Last-Updated: 三 4月  3 21:51:34 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 7
// URL: http://wuhongyi.cn 

#include "AutoCali.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AutoCali::AutoCali(TH1D *h, int flag)
{
  spec = NULL;
  rawhist = NULL;
  bghist = NULL;
  realhist = NULL;
  
  sourceflag = flag;
  rawhist = (TH1D *)h->Clone("rawhist");
  bghist = (TH1D *)rawhist->ShowBackground(20,"");
  realhist = (TH1D *)h->Clone("realhist");
  realhist->Add(bghist,-1);


  if(sourceflag == 1)
    {
      PeaksThreshold = 0.05;
      NoPeaks = 10;
    }
  
}

AutoCali::~AutoCali()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool AutoCali::SearchPeak()
{
  for (int i = 0; i < COUNTERMAX; ++i)
    {
      fPeakFlag[i] = false;
    }
  
  spec = new TSpectrum(20);

  Int_t nfound = 100;
  Int_t nloop = 0;
  while(nloop < 50)
    {
      nfound = spec->Search(realhist,4,"",PeaksThreshold);
      if(nfound > NoPeaks) PeaksThreshold += 0.005;
      else PeaksThreshold -= 0.005;
      if(PeaksThreshold < 0 || nfound <= NoPeaks/*|| TMath::Abs(nfound-NoPeaks)<3 */) break;
      nloop++;
    }


  Double_t *xpeaks = spec->GetPositionX();
  Double_t *ypeaks = spec->GetPositionY();
  for (int i = 0; i < nfound; ++i)
    {
      std::cout<<i<<"  "<<xpeaks[i]<<"  "<<ypeaks[i]<<std::endl;
    }

  double tempcalik;
  double tempcalib;
  if(xpeaks[0] < xpeaks[1])
    {
      tempcalik = (344.28-121.78)/(xpeaks[1]-xpeaks[0]);
      tempcalib = 121.78-tempcalik*xpeaks[0];
    }
  else
    {
      tempcalik = (344.28-121.78)/(xpeaks[0]-xpeaks[1]);
      tempcalib = 121.78-tempcalik*xpeaks[1];
    }
  std::cout<<tempcalib<<"  "<<tempcalik<<std::endl;
  

  return true;
  
}





// 
// AutoCali.cc ends here









