// module: tm.ko
// function: tmOnuGlbRegValidation @ 0x45b30
// size: 124 bytes
//

undefined4 tmOnuGlbRegValidation(uint param_1,int *param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = param_5 + param_1 * 0x1c;
  *param_2 = iVar1;
  if (*(ushort *)(param_5 + param_1 * 0x1c) == param_1) {
    if (param_4 == 1) {
      if (*(int *)(iVar1 + 4) == 2) {
        return 1;
      }
    }
    else if ((param_4 == 2) && (*(int *)(iVar1 + 4) == 1)) {
      return 1;
    }
    if (param_3 <= *(ushort *)(iVar1 + 0x12)) {
      *(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + 1;
      return 0;
    }
  }
  return 1;
}

