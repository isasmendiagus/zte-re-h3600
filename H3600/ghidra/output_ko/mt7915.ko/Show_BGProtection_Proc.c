// module: mt7915.ko
// function: Show_BGProtection_Proc @ 0xd5b60
// size: 124 bytes
//

undefined4 Show_BGProtection_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x79506c);
  if (iVar1 == 1) {
    snprintf(param_2,param_3,"\tON",1,param_4);
    return 0;
  }
  if (iVar1 != 0) {
    if (iVar1 != 2) {
      snprintf(param_2,param_3,"\tUnknow Value(%lu)",iVar1,param_4);
      return 0;
    }
    snprintf(param_2,param_3,"\tOFF",2,param_4);
    return 0;
  }
  snprintf(param_2,param_3,"\tAuto",0,param_4);
  return 0;
}

