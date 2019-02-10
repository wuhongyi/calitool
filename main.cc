// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 4月 19 09:14:41 2014 (+0800)
// Last-Updated: 日 2月 10 15:04:21 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 166
// URL: http://wuhongyi.cn 

#include "TRint.h"
#include "TObject.h"

#include "caliMainFrame.hh"
using namespace std;

int main(int argc, char *argv[])
{
   // Create an interactive ROOT application
   TRint *theApp = new TRint("Rint", &argc, argv);

   //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   new caliMainFrame();

   //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
   // and enter the event loop...
   theApp->Run();
   delete theApp;

  return 0;
}

// 
// main.cc ends here
