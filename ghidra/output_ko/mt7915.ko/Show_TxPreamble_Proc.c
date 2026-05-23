// module: mt7915.ko
// function: Show_TxPreamble_Proc @ 0xd59c0
// size: 124 bytes
//

undefined4 Show_TxPreamble_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x795064);
  if (iVar1 == 1) {
    snprintf(param_2,param_3,"\tShort",1,param_4);
    return 0;
  }
  if (iVar1 != 0) {
    if (iVar1 != 2) {
      snprintf(param_2,param_3,"\tUnknown Value(%lu)",iVar1,param_4);
      return 0;
    }
    snprintf(param_2,param_3,"\tAuto",2,param_4);
    return 0;
  }
  snprintf(param_2,param_3,"\tLong",0,param_4);
  return 0;
}

