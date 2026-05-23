// compatible: zxic,tempsensor
// function: FUN_c00c7ce0 @ 0xc00c7ce0
// found via struct field ptr -> 0xc00c7ce0
// total struct-refs for compat: 4
//

undefined8 FUN_c00c7ce0(int param_1,undefined4 param_2,uint param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  iVar4 = *(int *)(param_1 + 0x90);
  FUN_c046e90c(iVar4 + 0x30);
  uVar1 = *(undefined4 *)(param_1 + 0x88);
  iVar3 = *(int *)(param_1 + 0x8c);
  *(undefined4 *)(iVar4 + 0x28) = uVar1;
  *(int *)(iVar4 + 0x2c) = iVar3;
  if (param_5 == 0) {
LAB_c00c7d30:
    if (-1 < param_4) {
      if (*(int *)(iVar4 + 0x24) == param_4 && *(uint *)(iVar4 + 0x20) == param_3) {
        *(uint *)(param_1 + 0x40) = param_3;
        *(int *)(param_1 + 0x44) = param_4;
        uVar1 = *(undefined4 *)(iVar4 + 0x28);
        iVar3 = *(int *)(iVar4 + 0x2c);
      }
      else {
        do {
          uVar2 = FUN_c00c7b04(iVar4,iVar3,param_3,param_4);
          iVar3 = (int)uVar2 >> 0x1f;
        } while (uVar2 == 0xfffffff5);
        if (uVar2 == 0) {
          *(uint *)(iVar4 + 0x20) = param_3;
          *(int *)(iVar4 + 0x24) = param_4;
          *(uint *)(param_1 + 0x40) = param_3;
          *(int *)(param_1 + 0x44) = param_4;
          uVar1 = *(undefined4 *)(iVar4 + 0x28);
          iVar3 = *(int *)(iVar4 + 0x2c);
        }
        else {
          uVar1 = 0;
          iVar3 = 0;
          *(undefined4 *)(param_1 + 0x40) = 0;
          *(undefined4 *)(param_1 + 0x44) = 0;
          *(undefined4 *)(iVar4 + 0x20) = 0;
          *(undefined4 *)(iVar4 + 0x24) = 0;
          *(undefined4 *)(iVar4 + 0x28) = 0;
          *(undefined4 *)(iVar4 + 0x2c) = 0;
          *(undefined4 *)(iVar4 + 0x18) = 0;
          *(undefined4 *)(iVar4 + 0x1c) = 0;
          *(undefined4 *)(iVar4 + 0xc) = 0;
          param_3 = uVar2;
          param_4 = (int)uVar2 >> 0x1f;
        }
      }
      goto LAB_c00c7db4;
    }
  }
  else if (param_5 == 1) {
    bVar5 = CARRY4(param_3,*(uint *)(param_1 + 0x40));
    param_3 = param_3 + *(uint *)(param_1 + 0x40);
    param_4 = param_4 + *(int *)(param_1 + 0x44) + (uint)bVar5;
    goto LAB_c00c7d30;
  }
  param_3 = 0xffffffea;
  param_4 = -1;
LAB_c00c7db4:
  *(undefined4 *)(param_1 + 0x88) = uVar1;
  *(int *)(param_1 + 0x8c) = iVar3;
  FUN_c046e750(iVar4 + 0x30);
  return CONCAT44(param_4,param_3);
}

