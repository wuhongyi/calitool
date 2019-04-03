// AutoCali.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 4月  3 20:41:16 2019 (+0800)
// Last-Updated: 三 4月  3 22:57:57 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
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
      if(PeaksThreshold < 0 || nfound <= NoPeaks) break;
      nloop++;
    }

  xpeaks = spec->GetPositionX();
  ypeaks = spec->GetPositionY();
  // for (int i = 0; i < nfound; ++i)
  //   {
  //     std::cout<<i<<"  "<<xpeaks[i]<<"  "<<ypeaks[i]<<std::endl;
  //   }

  if(sourceflag == 1)
    {
      FlagEu152(nfound);

      // for (int i = 0; i < COUNTERMAX; ++i)
      // 	{
      // 	  if(fPeakFlag[i])
      // 	    std::cout<<"result: "<<fPeak[i]<<"  "<<Eu152[i]<<std::endl;
      // 	}
    }
  

  return true;
  
}

void AutoCali::FlagEu152(int n)
{
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
  // std::cout<<tempcalib<<"  "<<tempcalik<<std::endl;

  for (int i = 0; i < n; ++i)
    {
      double tempenergy = tempcalik*xpeaks[i]+tempcalib;
     for (int j = 0; j < 8; ++j)
       {
	 if(tempenergy > Eu152[j]-5 && tempenergy < Eu152[j]+5)
	   {
	     Double_t fitleft,fitright;
	     for (int k = xpeaks[i]; k > 0; --k)
	       {
		 if(realhist->GetBinContent(k) < 0.5*ypeaks[i])
		   {
		     fitleft = k;
		     break;
		   }
	       }
	     for (int k = xpeaks[i]; k < realhist->GetNbinsX(); ++k)
	       {
		 if(realhist->GetBinContent(k) < 0.3*ypeaks[i])
		   {
		     fitright = k;
		     break;
		   }
	       }

	     realhist->Fit("gaus","Q0","",fitleft,fitright);
	     TF1 *ff = (TF1*)realhist->GetFunction("gaus");
	     fPeak[j] = ff->GetParameter(1);;
	     fPeakFlag[j] = true;
	   }
       }
      
    }
  
}

void AutoCali::GetEu152Pars(int n,bool *f,double *x,double *y)
{
  *f = fPeakFlag[n];
  *x = fPeak[n];
  *y = Eu152[n];
}

// 
// AutoCali.cc ends here
