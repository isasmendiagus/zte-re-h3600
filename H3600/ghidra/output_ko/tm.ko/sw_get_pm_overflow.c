// module: tm.ko
// function: sw_get_pm_overflow @ 0x60774
// size: 116 bytes
//

void sw_get_pm_overflow(uint *param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar3 = *param_1;
  uVar4 = param_1[1];
  uVar1 = *param_2;
  uVar2 = param_2[1];
  bVar5 = uVar2 <= uVar4;
  if (uVar4 == uVar2) {
    bVar5 = uVar1 <= uVar3;
  }
  if ((!bVar5) && (uVar4 - (uVar2 + (uVar3 < uVar1)) == -1 && uVar3 - uVar1 < 0xa0000000)) {
    uVar1 = *param_3;
    *param_3 = uVar1 + 1;
    param_3[1] = param_3[1] + (uint)(0xfffffffe < uVar1);
    uVar3 = *param_1;
    uVar4 = param_1[1];
  }
  *param_2 = uVar3;
  param_2[1] = uVar4;
  uVar1 = *param_3;
  *param_1 = *param_1;
  param_1[1] = uVar1 + param_1[1];
  return;
}

