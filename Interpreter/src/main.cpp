#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

using namespace std;


int main()
{
//--------
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

///------
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



  Interp4Command *pCmd_move = pCreateCmd_Move();
  Interp4Command *pCmd_set = pCreateCmd_Set();

  cout << endl;
  cout << pCmd_move->GetCmdName() << endl;
  cout << endl;
  pCmd_move->PrintSyntax();
  cout << endl;
  pCmd_move->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmd_set->GetCmdName() << endl;
  cout << endl;
  pCmd_set->PrintSyntax();
  cout << endl;
  pCmd_set->PrintCmd();
  cout << endl;

  delete pCmd_move;
  delete pCmd_set;

  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Set);
}
