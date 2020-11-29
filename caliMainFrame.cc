// caliMainFrame.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月  9 21:18:25 2019 (+0800)
// Last-Updated: 六 11月 28 21:47:15 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 83
// URL: http://wuhongyi.cn 

#include "caliMainFrame.hh"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

ClassImp(caliMainFrame);

const char *dnd_types[] =
  {
   "MCA files",    "*.mca",
   "All files",     "*",
   0,               0
  };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

caliMainFrame::caliMainFrame()
  : TGMainFrame(gClient->GetRoot())
{
  fHist1 = NULL;
  fHist2 = NULL;
  autocali = NULL;

  // gStyle->SetOptStat(0);
  MainFrame();
}

caliMainFrame::~caliMainFrame()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void caliMainFrame::MainFrame()
{
  SetCleanup(kDeepCleanup);

  TGHorizontalFrame *h1frame = new TGHorizontalFrame(this, 1000, 400);
  AddFrame(h1frame, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY, 10, 10, 10, 10));
  
  TGVerticalFrame *v11frame = new TGVerticalFrame(h1frame, 200, 400, kFixedWidth | kFixedHeight);
  h1frame->AddFrame(v11frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
  TGVerticalFrame *v12frame = new TGVerticalFrame(h1frame, 600, 400,  kFixedWidth | kFixedHeight);
  h1frame->AddFrame(v12frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
  TGVerticalFrame *v13frame = new TGVerticalFrame(h1frame, 200, 400, kFixedWidth | kFixedHeight);
  h1frame->AddFrame(v13frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));

  // v11
  TGTextButton *bt_load = new TGTextButton(v11frame, "Load spectrum");
  v11frame->AddFrame(bt_load, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  bt_load->Connect("Clicked()", "caliMainFrame", this, "LoadSpectrum()");
  
  TGTextButton *bt_exit = new TGTextButton(v11frame, "Exit", "gApplication->Terminate(0)");
  v11frame->AddFrame(bt_exit, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  bt_exit->SetToolTipText("Terminate the application", 200);

  TGLabel *label11 = new TGLabel(v11frame, "MIN  /  MAX"); //Devided by space
  v11frame->AddFrame(label11, new TGLayoutHints(kLHintsExpandX, 4, 4, 50, 0));
  channelminmaxframe = new TGHorizontalFrame(v11frame, 100, 40);
  v11frame->AddFrame(channelminmaxframe, new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0));
  channelmin = new TGTextEntry(channelminmaxframe, "0");
  channelminmaxframe->AddFrame(channelmin, new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0));
  channelmax = new TGTextEntry(channelminmaxframe, "65536");
  channelminmaxframe->AddFrame(channelmax, new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0)); 
  
  // v12
  fEcanvas1 = new TRootEmbeddedCanvas("ECanvas1", v12frame, 200, 200);
  v12frame->AddFrame(fEcanvas1, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
  // Int_t wid1 = fEcanvas1->GetCanvasWindowId();
  // TCanvas *myc1 = new TCanvas("MyCanvas1", 10,10,wid1);
  // fEcanvas1->AdoptCanvas(myc1);
  // myc1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)","caliMainFrame",this,"EventInfo1(Int_t,Int_t,Int_t,TObject*)");
  
  // v13
  fComCaliChoose = new TGComboBox(v13frame);
  v13frame->AddFrame(fComCaliChoose, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  fComCaliChoose->AddEntry("Manual",0);
  fComCaliChoose->AddEntry("Eu152",1);
  fComCaliChoose->AddEntry("Co60",2);
  fComCaliChoose->AddEntry("Ba133",3);
  fComCaliChoose->AddEntry("Am241",4);
  fComCaliChoose->AddEntry("Pu239",5);
  fComCaliChoose->AddEntry("3 alpha",6);
  fComCaliChoose->Select(0);
  fComCaliChoose->Connect("Selected(Int_t)","caliMainFrame", this, "DoCombo(Int_t)");
  fComCaliChoose->Resize(100,20);

  // fComCaliChoose->GetSelected()==0
  
  TGLabel *label13 = new TGLabel(v13frame, "Choose  /  channel  /  energy"); //Devided by space
  v13frame->AddFrame(label13, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  
  for (int i = 0; i < CALIPOINTNUMBER; ++i)
    {
      coorxydframe[i] = new TGHorizontalFrame(v13frame, 100, 40);
      v13frame->AddFrame(coorxydframe[i], new TGLayoutHints(kLHintsExpandX| kLHintsExpandY, 0, 0, 0, 0));
      coordxycb[i] = new TGCheckButton(coorxydframe[i], TString::Format("%02d",i).Data(),0);
      coorxydframe[i]->AddFrame(coordxycb[i], new TGLayoutHints(kLHintsExpandX, 1, 2, 2, 0));
      coordx[i] = new TGTextEntry(coorxydframe[i], "0.0");
      coorxydframe[i]->AddFrame(coordx[i], new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0));
      coordy[i] = new TGTextEntry(coorxydframe[i], "0.0");
      coorxydframe[i]->AddFrame(coordy[i], new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0)); 
    }


  
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  TGHorizontalFrame *h2frame = new TGHorizontalFrame(this, 1000, 400);
  AddFrame(h2frame, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY, 10, 10, 10, 10));

  TGVerticalFrame *v21frame = new TGVerticalFrame(h2frame, 200, 400, kFixedWidth | kFixedHeight);
  h2frame->AddFrame(v21frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
  TGVerticalFrame *v22frame = new TGVerticalFrame(h2frame, 600, 400,  kFixedWidth | kFixedHeight);
  h2frame->AddFrame(v22frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
  TGVerticalFrame *v23frame = new TGVerticalFrame(h2frame, 200, 400, kFixedWidth | kFixedHeight);
  h2frame->AddFrame(v23frame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));

  // v21
  coordinate1 = new TGLabel(v21frame,"0,0");
  v21frame->AddFrame(coordinate1, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  
  coordinate2 = new TGLabel(v21frame,"0,0");
  v21frame->AddFrame(coordinate2, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  
  // v22
  fEcanvas2 = new TRootEmbeddedCanvas("ECanvas2", v22frame, 200, 200);
  v22frame->AddFrame(fEcanvas2, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
  Int_t wid2 = fEcanvas2->GetCanvasWindowId();
  TCanvas *myc2 = new TCanvas("MyCanvas2", 10,10,wid2);
  fEcanvas2->AdoptCanvas(myc2);
  myc2->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)","caliMainFrame",this,"EventInfo2(Int_t,Int_t,Int_t,TObject*)");
	
  
  
  // v23
  bt_cali = new TGTextButton(v23frame, "Cali");
  v23frame->AddFrame(bt_cali, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  bt_cali->Connect("Clicked()", "caliMainFrame", this, "CaliRun()");

  TGLabel *label23 = new TGLabel(v23frame, "p0       /       p1"); //Devided by space
  v23frame->AddFrame(label23, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));

  par01frame = new TGHorizontalFrame(v23frame, 100, 40);
  v23frame->AddFrame(par01frame, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY, 0, 0, 0, 0));
  te_par0 = new TGTextEntry(par01frame, "0.0");
  par01frame->AddFrame(te_par0, new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0));
  te_par1 = new TGTextEntry(par01frame, "0.0");
  par01frame->AddFrame(te_par1, new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 0)); 

  
  
  fComBinChoose = new TGComboBox(v23frame);
  v23frame->AddFrame(fComBinChoose, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  fComBinChoose->AddEntry("2 MeV / 0.5 keV",0);
  fComBinChoose->AddEntry("2 MeV / 1.0 keV",1);
  fComBinChoose->AddEntry("3 MeV / 0.5 keV",2);
  fComBinChoose->AddEntry("3 MeV / 1.0 keV",3);
  fComBinChoose->AddEntry("4 MeV / 0.5 keV",4);
  fComBinChoose->AddEntry("4 MeV / 1.0 keV",5);
  fComBinChoose->AddEntry("4 MeV / 2.0 keV",6);
  fComBinChoose->AddEntry("6 MeV / 1.0 keV",7);
  fComBinChoose->AddEntry("6 MeV / 2.0 keV",8);
  fComBinChoose->AddEntry("6 MeV / 5.0 keV",9);
  fComBinChoose->Select(0);
  fComBinChoose->Resize(100,20);

  bt_draw = new TGTextButton(v23frame, "Draw Spectrum");
  v23frame->AddFrame(bt_draw, new TGLayoutHints(kLHintsExpandX, 4, 4, 10, 0));
  bt_draw->Connect("Clicked()", "caliMainFrame", this, "DrawEnergySpectrum()");

  // Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  // DontCallClose();

  MapSubwindows();
  Resize(GetDefaultSize());

  SetWindowName("cali analysis");
  MapRaised();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void caliMainFrame::LoadSpectrum()
{
  static TString gFileDir(".");
  TGFileInfo fi;
  fi.fFileTypes = dnd_types;
  fi.fIniDir    = StrDup(gFileDir);

  new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
  gFileDir = fi.fIniDir;

  fFileName = fi.fFilename;

  // TODO 这里应该添加读取保护，如果没有选择合适的文件，则开启界面保护

  bool flag = ReadMCA(fFileName);
  TCanvas *fCanvas = fEcanvas1->GetCanvas();
  fCanvas->cd();
  if(flag)
    {
      fHist1->Draw();
    }
  else
    {
      fCanvas->Clear();
    }
  fCanvas->Update();
}

bool caliMainFrame::ReadMCA(TString s)
{
  std::ifstream mcafile;
  std::string onelinestring;
  std::stringstream ss;
  int Channel = -1;
  int Gain = -1;//MCA channel 1<<(8+Gain)

  mcafile.open(s.Data());
  if(mcafile.fail())
    {
      std::cout<<"Can't open the file : "<<s.Data()<<". Please check it."<<std::endl;
    }
  else
    {
      while(getline(mcafile,onelinestring))
	{
	  // cout<<onelinestring<<endl;
	  if(onelinestring[0] == 'G' && onelinestring[1] == 'A' && onelinestring[2] == 'I' && onelinestring[3] == 'N' && onelinestring[5] == '-')
	    {
	      // cout<<onelinestring<<endl;
	      ss.clear();
	      ss<<onelinestring.replace(0, 6, "");
	      ss>>Gain;
	      // cout<<Gain<<endl;
	      Channel = 1 << (8+Gain);
	      // cout<<Channel<<endl;
	    }
	  if(onelinestring[0] == '<' && onelinestring[1] == '<' && onelinestring[2] == 'D')//onelinestring.size() == 9 && 
	    break;
	}

      if(Gain < 0)
	return false;

      if(fHist1 != NULL) delete fHist1;
      int count;
      fHist1 = new TH1D("fHist1","",Channel,0,Channel);
      fHist1->GetXaxis()->SetTitle("channel");

      TString strchmin(channelmin->GetText());
      TString strchmax(channelmax->GetText());
      int chmin = strchmin.Atoi();
      int chmax = strchmax.Atoi();
      for (int i = 0; i < Channel; ++i)
	{
	  mcafile>>count;
	  // cout<<i<<"  "<<count<<endl;
	  if(i<chmin || i>chmax) continue;
	  for (int j = 0; j < count; ++j)
	    {
	      fHist1->Fill(i);
	    }
	}

      getline(mcafile,onelinestring);
      // cout<<onelinestring<<endl;
      getline(mcafile,onelinestring);
      // cout<<onelinestring<<endl;
      if(onelinestring[0] == '<' && onelinestring[1] == '<' && onelinestring[2] == 'E')
	std::cout<<"Read file :"<<s.Data()<<" done."<<std::endl;
      mcafile.close();
    }

  return true;
}

void caliMainFrame::EventInfo1(Int_t event, Int_t px, Int_t py, TObject *selected)
{
  //  Writes the event status in the status bar parts
  const char *text;
  //text0 = selected->GetTitle();
  //text1 = selected->GetName();
  //if (event == kKeyPress)
  // sprintf(text2, "%c", (char) px);
  // else
  // sprintf(text2, "%d,%d", px, py);

  text = selected->GetObjectInfo(px,py);
  coordinate1->SetText(text);
}

void caliMainFrame::EventInfo2(Int_t event, Int_t px, Int_t py, TObject *selected)
{
  //  Writes the event status in the status bar parts
  const char *text;
  //text0 = selected->GetTitle();
  //text1 = selected->GetName();
  //if (event == kKeyPress)
  // sprintf(text2, "%c", (char) px);
  // else
  // sprintf(text2, "%d,%d", px, py);

  text = selected->GetObjectInfo(px,py);
  coordinate2->SetText(text);
}

void caliMainFrame::DrawEnergySpectrum()
{
  if(fHist2 != NULL) delete fHist2;

  switch(fComBinChoose->GetSelected())
    {
    case 0:
      fHist2 = new TH1D("fHist2","",4000,0,2000);
      break;
    case 1:
      fHist2 = new TH1D("fHist2","",2000,0,2000);
      break;
    case 2:
      fHist2 = new TH1D("fHist2","",6000,0,3000);
      break;
    case 3:
      fHist2 = new TH1D("fHist2","",3000,0,3000);
      break;
    case 4:
      fHist2 = new TH1D("fHist2","",8000,0,4000);
      break;
    case 5:
      fHist2 = new TH1D("fHist2","",4000,0,4000);
      break;
    case 6:
      fHist2 = new TH1D("fHist2","",2000,0,4000);
      break;
    case 7:
      fHist2 = new TH1D("fHist2","",6000,0,6000);
      break;
    case 8:
      fHist2 = new TH1D("fHist2","",3000,0,6000);
      break;
    case 9:
      fHist2 = new TH1D("fHist2","",1200,0,6000);
      break;
    default:
      std::cout<<"undefine!!!"<<std::endl;
      break;
    }

  TString par0(te_par0->GetText());
  TString par1(te_par1->GetText());
  fFitPar0 = par0.Atof();
  fFitPar1 = par1.Atof();
  for (int i = 0; i < fHist1->GetNbinsX(); ++i)
    {
      for (int j = 0; j < fHist1->GetBinContent(i+1); ++j)
	{
	  fHist2->Fill((i+gRandom->Rndm())*fFitPar1+fFitPar0);
	}      
    }

  fHist2->GetXaxis()->SetTitle("keV");
  
  TCanvas *fCanvas = fEcanvas2->GetCanvas();
  fCanvas->cd();
  fHist2->Draw();
  fCanvas->Update();
  
}

void caliMainFrame::DoCombo(Int_t id)
{
  std::cout<<"Combo ID: "<<id<<std::endl;
  if(id>1)
    std::cout<<"This feature is currently invalid!"<<std::endl;
}

void caliMainFrame::FitData()
{
  TGraph *gg = new TGraph;
  for (int i = 0; i < CALIPOINTNUMBER; ++i)
    {
      if(coordxycb[i]->IsOn())
	{
	  TString xx(coordx[i]->GetText());
	  TString yy(coordy[i]->GetText());
	  // std::cout<<xx.Atof()<<"  "<<yy.Atof()<<std::endl;
		
	  gg->SetPoint(gg->GetN(),xx.Atof(),yy.Atof());
	}
    }
  if(gg->GetN() >= 2)
    {
      gg->Fit("pol1","Q");
      TF1 *ff = (TF1*)gg->GetFunction("pol1");
      fFitPar0 = ff->GetParameter(0);
      fFitPar1 = ff->GetParameter(1);
      te_par0->SetText(TString::Format("%0.6f",fFitPar0).Data());
      te_par1->SetText(TString::Format("%0.6f",fFitPar1).Data());
      std::cout<<"Fit result: "<<fFitPar0<<"  "<<fFitPar1<<std::endl;
    }
            
  delete gg;
}

void caliMainFrame::CaliRun()
{
  int nump = 0;
  
  switch(fComCaliChoose->GetSelected())
    {
    case 0://Manual
      FitData();
      break;
    case 1://EU152
      if(autocali != NULL) delete autocali;
      autocali = new AutoCali(fHist1,1);
      autocali->SearchPeak();

      for (int i = 0; i < CALIPOINTNUMBER; ++i)
	{
	  coordxycb[i]->SetOn(false);
	}
      // 
      for (int j = 0; j < 8; ++j)
      	{
      	  bool tempf;
      	  double tempx,tempy;
      	  autocali->GetEu152Pars(j,&tempf,&tempx,&tempy);
      	  // std::cout<<i<<"  "<<tempf<<"  "<<tempx<<"  "<<tempy<<std::endl;
      	  if(tempf)
      	    {
	      coordxycb[nump]->SetOn(true);
      	      coordx[nump]->SetText(TString::Format("%0.3f",tempx).Data());
      	      coordy[nump]->SetText(TString::Format("%0.3f",tempy).Data());
      	      nump++;
      	    }
      	}
      FitData();

      delete autocali;
      break;
    case 2://Co60
      if(autocali != NULL) delete autocali;
      autocali = new AutoCali(fHist1,2);
      autocali->SearchPeak();

      for (int i = 0; i < CALIPOINTNUMBER; ++i)
	{
	  coordxycb[i]->SetOn(false);
	}

      for (int j = 0; j < 2; ++j)
      	{
      	  bool tempf;
      	  double tempx,tempy;
      	  autocali->GetCo60Pars(j,&tempf,&tempx,&tempy);
      	  // std::cout<<i<<"  "<<tempf<<"  "<<tempx<<"  "<<tempy<<std::endl;
      	  if(tempf)
      	    {
	      coordxycb[nump]->SetOn(true);
      	      coordx[nump]->SetText(TString::Format("%0.3f",tempx).Data());
      	      coordy[nump]->SetText(TString::Format("%0.3f",tempy).Data());
      	      nump++;
      	    }
      	}
      FitData();

      delete autocali;
      break;
    case 3://Ba133
      std::cout<<"Not implemented!"<<std::endl;
      break;
    case 4://Am241
      std::cout<<"Not implemented!"<<std::endl;
      break;
    case 5://Pu239
      std::cout<<"Not implemented!"<<std::endl;
      break;
    case 6://3 alpha
      std::cout<<"Not implemented!"<<std::endl;
      break;
    default:
      std::cout<<"Not implemented!"<<std::endl;
      break;
    }
}

// 
// caliMainFrame.cc ends here
