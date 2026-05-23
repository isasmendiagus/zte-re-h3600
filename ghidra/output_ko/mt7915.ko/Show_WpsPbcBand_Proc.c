// module: mt7915.ko
// function: Show_WpsPbcBand_Proc @ 0xd61a4
// size: 156 bytes
//

undefined4 Show_WpsPbcBand_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)((int)param_1 + *(int *)(*param_1 + 0x3c) * 0x2137b0 + 0x371895);
  if (uVar1 == 1) {
    snprintf(param_2,param_3,"\t5G",1,param_4);
    return 0;
  }
  if (uVar1 != 0) {
    if (uVar1 != 2) {
      snprintf(param_2,param_3,"\tUnknow Value(%d)",uVar1,param_4);
      return 0;
    }
    snprintf(param_2,param_3,"\tAuto",2,param_4);
    return 0;
  }
  snprintf(param_2,param_3,"\t2.4G",0,param_4);
  return 0;
}

