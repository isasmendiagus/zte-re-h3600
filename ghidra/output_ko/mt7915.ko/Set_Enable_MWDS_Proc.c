// module: mt7915.ko
// function: Set_Enable_MWDS_Proc @ 0x9ec20
// size: 156 bytes
//

undefined4 Set_Enable_MWDS_Proc(int *param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_1;
  if (param_3 == 0) {
    if (*(int *)(iVar1 + 0x38) != 0x400) {
      return 0;
    }
    uVar2 = (uint)*(byte *)(iVar1 + 0x3c);
    *(bool *)(param_1 + uVar2 * 0x84dec + 0xdc6ac) = param_2 != 0;
  }
  else {
    uVar2 = (uint)*(byte *)(iVar1 + 0x3c);
    *(bool *)(param_1 + uVar2 * 0x160d + 0xaec68) = param_2 != 0;
  }
  if (param_2 == 0) {
    MWDSDisable();
    return 1;
  }
  MWDSEnable(param_1,uVar2,param_3,0);
  return 1;
}

