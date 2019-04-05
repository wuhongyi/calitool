// caliMainFrame.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月  9 21:18:05 2019 (+0800)
// Last-Updated: 五 4月  5 09:03:58 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 20
// URL: http://wuhongyi.cn 

#ifndef _CALIMAINFRAME_H_
#define _CALIMAINFRAME_H_

#include "AutoCali.hh"

#include "TGButton.h"
#include "TGButtonGroup.h"
#include "TGLabel.h"
#include "TGNumberEntry.h"
#include "TGTextViewStream.h"
#include "TApplication.h"
#include "TGFrame.h"
#include "TGFileDialog.h"
#include "TRootEmbeddedCanvas.h"
#include "TGComboBox.h"

#include "TSystem.h"
#include "TFile.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"
#include "TRandom.h"

#include <iostream> 
#include <sstream>
#include <cstring>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define CALIPOINTNUMBER 10

class caliMainFrame : public TGMainFrame
{
public:
  caliMainFrame();
  virtual ~caliMainFrame();

  void CaliRun();
  void LoadSpectrum();
  void DrawEnergySpectrum();
  void EventInfo1(Int_t event, Int_t px, Int_t py, TObject *selected);
  void EventInfo2(Int_t event, Int_t px, Int_t py, TObject *selected);
  void DoCombo(Int_t id);
  
private:
  void MainFrame();
  bool ReadMCA(TString s);

  void FitData();
protected:
  TGLabel  *coordinate1;
  TGLabel  *coordinate2;
  TRootEmbeddedCanvas *fEcanvas1;
  TRootEmbeddedCanvas *fEcanvas2;

  TGHorizontalFrame *channelminmaxframe;
  TGTextEntry *channelmin,*channelmax;
  
  TGComboBox *fComCaliChoose;
  TGHorizontalFrame *coorxydframe[CALIPOINTNUMBER];
  TGCheckButton *coordxycb[CALIPOINTNUMBER];
  TGTextEntry *coordx[CALIPOINTNUMBER], *coordy[CALIPOINTNUMBER];
  

  TGTextButton *bt_cali;
  TGTextButton *bt_draw;
  TGComboBox *fComBinChoose;
  TGHorizontalFrame *par01frame;
  TGTextEntry *te_par0, *te_par1;
  
  TString fFileName;

  TH1D *fHist1;
  TH1D *fHist2;
  Double_t fFitPar0;
  Double_t fFitPar1;

  AutoCali *autocali;
  
  ClassDef(caliMainFrame, 1);
};

#endif /* _CALIMAINFRAME_H_ */
// 
// caliMainFrame.hh ends here
