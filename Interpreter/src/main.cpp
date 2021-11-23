#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"

using namespace std;

#define LINE_SIZE 500

bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{
    string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    ostringstream OTmpStrm;

    Cmd4Preproc += NazwaPliku;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
    if (!pProc) return false;
    while (fgets(Line,LINE_SIZE,pProc)) 
    {
    OTmpStrm << Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

int main(int argc, char* argv[])
{
///----------------------------------------------------------------------------
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun_move;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun_move = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun_move) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_move);

///----------------------------------------------------------------------------
void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
Interp4Command *(*pCreateCmd_Set)(void);
void *pFun_set;
if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }
pFun_set = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun_set) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_set);
///----------------------------------------------------------------------------
void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
Interp4Command *(*pCreateCmd_Pause)(void);
void *pFun_pause;
if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
    return 1;
  }
pFun_pause = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFun_pause) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_pause);
///----------------------------------------------------------------------------
void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
Interp4Command *(*pCreateCmd_Rotate)(void);
void *pFun_rotate;
if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }
pFun_rotate = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun_rotate) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun_rotate);
///---------------------------------------------------------------------------
 Interp4Command* pCmd[4];
  pCmd[0] =  pCreateCmd_Move();
  pCmd[1] = pCreateCmd_Set();
  pCmd[2] = pCreateCmd_Pause();
  pCmd[3] = pCreateCmd_Rotate();


   for (int i = 3;i>=0;i--)
   {
  cout << endl;
  cout << pCmd[i]->GetCmdName() << endl;
  cout << endl;
  pCmd[i]->PrintSyntax();
  cout << endl;
  pCmd[i]->PrintCmd();
  cout << endl;

   }
/*
  cout << endl;
  cout << pCmd_set->GetCmdName() << endl;
  cout << endl;
  pCmd_set->PrintSyntax();
  cout << endl;
  pCmd_set->PrintCmd();
  cout << endl;
*/
for (int i = 3;i>=0;i--)
   {
  delete pCmd[i];
}
  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Set);
  dlclose(pLibHnd_Pause);
  dlclose(pLibHnd_Rotate);
  
  istringstream streamls;
  ExecPreprocesor("program.cmd", streamls);
  
  cout<<streamls.str()<<endl;
  
}
