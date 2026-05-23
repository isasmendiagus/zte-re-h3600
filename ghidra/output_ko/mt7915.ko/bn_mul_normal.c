// module: mt7915.ko
// function: bn_mul_normal @ 0x211f80
// size: 248 bytes
//

void bn_mul_normal(int param_1,undefined4 *param_2,int param_3,undefined4 *param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar5 = param_4;
  iVar4 = param_5;
  if (param_3 < param_5) {
    puVar5 = param_2;
    iVar4 = param_3;
    param_2 = param_4;
    param_3 = param_5;
  }
  puVar6 = (undefined4 *)(param_1 + param_3 * 4);
  if (iVar4 < 1) {
    FUN_0020cb1c(param_1,param_2,param_3,0);
    return;
  }
  uVar1 = FUN_0020cb1c(param_1,param_2,param_3,*puVar5);
  *(undefined4 *)(param_1 + param_3 * 4) = uVar1;
  if (iVar4 == 1) {
    return;
  }
  do {
    uVar1 = FUN_0020c980(param_1 + 4,param_2,param_3,puVar5[1]);
    puVar6[1] = uVar1;
    if (iVar4 + -2 < 1) {
      return;
    }
    uVar1 = FUN_0020c980(param_1 + 8,param_2,param_3,puVar5[2]);
    iVar3 = iVar4 + -3;
    iVar4 = iVar4 + -4;
    puVar6[2] = uVar1;
    iVar2 = param_1 + 0xc;
    param_1 = param_1 + 0x10;
    if (iVar3 < 1) {
      return;
    }
    uVar1 = FUN_0020c980(iVar2,param_2,param_3,puVar5[3]);
    puVar6[3] = uVar1;
    if (iVar4 < 1) {
      return;
    }
    puVar5 = puVar5 + 4;
    uVar1 = FUN_0020c980(param_1,param_2,param_3,*puVar5);
    puVar6 = puVar6 + 4;
    *puVar6 = uVar1;
  } while (iVar4 != 1);
  return;
}

