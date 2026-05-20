// compatible: zxic,tempsensor
// function: FUN_c02c85ec @ 0xc02c85ec
// found via struct field ptr -> 0xc02c85ec
// total struct-refs for compat: 4
//

uint FUN_c02c85ec(undefined4 param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auStack_110 [260];
  
  FUN_c0181a60(auStack_110,0,0x100);
  if (0x100 < param_3) {
    uVar4 = FUN_c046b544(param_3);
    return uVar4;
  }
  uVar5 = *(uint *)(((uint)auStack_110 & 0xffffe000) + 8);
  uVar3 = param_2 + param_3;
  uVar4 = uVar3;
  if (!CARRY4(param_2,param_3)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar2 = FUN_c017f4e8(auStack_110,param_2,param_3);
    if (iVar2 != 0) goto LAB_c02c8688;
  }
  else if (param_3 != 0) {
    FUN_c0181b40(auStack_110,param_3,uVar4);
LAB_c02c8688:
    FUN_c046918c(s_copy_from_user_failed_c05bf138);
    return 0xffffffff;
  }
  uVar1 = FUN_c01883b0(auStack_110);
  FUN_c02c7f40(auStack_110,uVar1);
  return param_3;
}

