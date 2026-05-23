// module: mt7915.ko
// function: build_twt_ie @ 0x168a2c
// size: 80 bytes
//

int build_twt_ie(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00166d4c(param_4 + 0x22e);
  if (iVar1 == 0) {
    uVar2 = 7;
  }
  else {
    uVar2 = 4;
  }
  FUN_00168130(param_1,param_2,uVar2,param_4 + 0x22e,param_3);
  return param_3 + 0x11;
}

