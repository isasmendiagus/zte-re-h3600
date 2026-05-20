// module: mt7915.ko
// function: find_oui_oitype @ 0x145abc
// size: 132 bytes
//

undefined4 find_oui_oitype(undefined4 param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_18;
  undefined4 local_14 [2];
  
  local_18 = 0;
  local_14[0] = param_3;
  FUN_0014580c(param_1,&local_18,param_2);
  uVar2 = 0;
  if (local_18 != 0) {
    iVar3 = *(int *)(local_18 + 8);
    while( true ) {
      if (iVar3 == 0) {
        return 0;
      }
      iVar1 = memcmp((void *)(iVar3 + 4),local_14,4);
      if (iVar1 == 0) break;
      iVar3 = *(int *)(iVar3 + 0xc);
    }
    uVar2 = 1;
    *param_4 = iVar3;
  }
  return uVar2;
}

