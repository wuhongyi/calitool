// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MainDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "caliMainFrame.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_caliMainFrame(void *p = 0);
   static void *newArray_caliMainFrame(Long_t size, void *p);
   static void delete_caliMainFrame(void *p);
   static void deleteArray_caliMainFrame(void *p);
   static void destruct_caliMainFrame(void *p);
   static void streamer_caliMainFrame(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::caliMainFrame*)
   {
      ::caliMainFrame *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::caliMainFrame >(0);
      static ::ROOT::TGenericClassInfo 
         instance("caliMainFrame", ::caliMainFrame::Class_Version(), "caliMainFrame.hh", 45,
                  typeid(::caliMainFrame), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::caliMainFrame::Dictionary, isa_proxy, 16,
                  sizeof(::caliMainFrame) );
      instance.SetNew(&new_caliMainFrame);
      instance.SetNewArray(&newArray_caliMainFrame);
      instance.SetDelete(&delete_caliMainFrame);
      instance.SetDeleteArray(&deleteArray_caliMainFrame);
      instance.SetDestructor(&destruct_caliMainFrame);
      instance.SetStreamerFunc(&streamer_caliMainFrame);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::caliMainFrame*)
   {
      return GenerateInitInstanceLocal((::caliMainFrame*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::caliMainFrame*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr caliMainFrame::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *caliMainFrame::Class_Name()
{
   return "caliMainFrame";
}

//______________________________________________________________________________
const char *caliMainFrame::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::caliMainFrame*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int caliMainFrame::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::caliMainFrame*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *caliMainFrame::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::caliMainFrame*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *caliMainFrame::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::caliMainFrame*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void caliMainFrame::Streamer(TBuffer &R__b)
{
   // Stream an object of class caliMainFrame.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> coordinate1;
      R__b >> coordinate2;
      R__b >> fEcanvas1;
      R__b >> fEcanvas2;
      R__b >> fComCaliChoose;
      int R__i;
      for (R__i = 0; R__i < 10; R__i++)
         R__b >> coorxydframe[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b >> coordxycb[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b >> coordx[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b >> coordy[R__i];
      R__b >> bt_cali;
      R__b >> bt_draw;
      R__b >> fComBinChoose;
      R__b >> par01frame;
      R__b >> te_par0;
      R__b >> te_par1;
      fFileName.Streamer(R__b);
      R__b >> fHist1;
      R__b >> fHist2;
      R__b >> fFitPar0;
      R__b >> fFitPar1;
      R__b >> autocali;
      R__b.CheckByteCount(R__s, R__c, caliMainFrame::IsA());
   } else {
      R__c = R__b.WriteVersion(caliMainFrame::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << coordinate1;
      R__b << coordinate2;
      R__b << fEcanvas1;
      R__b << fEcanvas2;
      R__b << fComCaliChoose;
      int R__i;
      for (R__i = 0; R__i < 10; R__i++)
         R__b << coorxydframe[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b << coordxycb[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b << coordx[R__i];
      for (R__i = 0; R__i < 10; R__i++)
         R__b << coordy[R__i];
      R__b << bt_cali;
      R__b << bt_draw;
      R__b << fComBinChoose;
      R__b << par01frame;
      R__b << te_par0;
      R__b << te_par1;
      fFileName.Streamer(R__b);
      R__b << (TObject*)fHist1;
      R__b << (TObject*)fHist2;
      R__b << fFitPar0;
      R__b << fFitPar1;
      R__b << autocali;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_caliMainFrame(void *p) {
      return  p ? new(p) ::caliMainFrame : new ::caliMainFrame;
   }
   static void *newArray_caliMainFrame(Long_t nElements, void *p) {
      return p ? new(p) ::caliMainFrame[nElements] : new ::caliMainFrame[nElements];
   }
   // Wrapper around operator delete
   static void delete_caliMainFrame(void *p) {
      delete ((::caliMainFrame*)p);
   }
   static void deleteArray_caliMainFrame(void *p) {
      delete [] ((::caliMainFrame*)p);
   }
   static void destruct_caliMainFrame(void *p) {
      typedef ::caliMainFrame current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_caliMainFrame(TBuffer &buf, void *obj) {
      ((::caliMainFrame*)obj)->::caliMainFrame::Streamer(buf);
   }
} // end of namespace ROOT for class ::caliMainFrame

namespace {
  void TriggerDictionaryInitialization_MainDict_Impl() {
    static const char* headers[] = {
"caliMainFrame.hh",
0
    };
    static const char* includePaths[] = {
"/opt/root61206/include",
"/home/wuhongyi/workgithub/calitool/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MainDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$caliMainFrame.hh")))  caliMainFrame;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MainDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "caliMainFrame.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"caliMainFrame", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MainDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MainDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MainDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MainDict() {
  TriggerDictionaryInitialization_MainDict_Impl();
}
