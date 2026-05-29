/* ===== FUN FUN_40e219e0 @ 40e21b00 =====
 * callers: 40e21bd4:FUN_40e21bd4
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45a90:FUN_40e45a90, 40e5102c:FUN_40e5102c
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_40e219e0(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int extraout_r1;
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 1;
  uVar3 = 1;
  if ((0x4b0 < param_1 - 300) ||
     (FUN_40e5102c(param_1,100,param_3,param_1 - 300,0,1,1,0), extraout_r1 != 0)) {
    FUN_40e2a1b4(DAT_40e21b8c/*=0x47f35a48*/);
    return;
  }
  uVar1 = _DAT_9400000c & 0x1800;
  _DAT_9400000c = _DAT_9400000c & 0xffff87ff;
  if (param_1 < 1000) {
    if (param_1 < 500) {
      if (param_1 == 400) {
        iVar2 = 3;
        uVar3 = 1;
      }
      else {
        if (param_1 != 300) goto LAB_40e21aec;
        iVar2 = 2;
        uVar3 = 2;
      }
      param_1 = 0x30;
      goto LAB_40e21aec;
    }
    param_1 = (uint)((ulonglong)DAT_40e21b90/*=0x51eb851f*/ * (ulonglong)(param_1 << 1) >> 0x20);
    iVar2 = 2;
  }
  else {
    iVar2 = 1;
    param_1 = (uint)((ulonglong)DAT_40e21b90/*=0x51eb851f*/ * (ulonglong)param_1 >> 0x20);
  }
  param_1 = param_1 >> 3;
  uVar3 = 1;
LAB_40e21aec:
  _DAT_94000018 = _DAT_94000018 & 0xfffc0000 | 0x80000000 | param_1 << 6 | iVar2 << 3 | uVar3;
  FUN_40e45a90(200);
  _DAT_94000018 = _DAT_94000018 & 0x7fffffff;
  FUN_40e45a90(200);
  _DAT_9400000c = _DAT_9400000c | 0x6000 | uVar1;
  return;
}
