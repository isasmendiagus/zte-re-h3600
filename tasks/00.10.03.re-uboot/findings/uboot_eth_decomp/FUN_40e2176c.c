/* ===== FUN FUN_40e2176c @ 40e2176c =====
 * callers: 40e45a90:FUN_40e45a90
 * callees: (none)
 */


void FUN_40e2176c(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (uint)((ulonglong)DAT_40e217c0/*=0x10624dd3*/ * (ulonglong)(uint)(param_1 * 0x30d4) >> 0x26);
  uVar1 = *(uint *)(DAT_40e217bc/*=0x94401000*/ + 0x18);
  while (0 < (int)uVar2) {
    uVar3 = *(uint *)(DAT_40e217bc/*=0x94401000*/ + 0x18);
    if (uVar1 < uVar3) {
      uVar2 = (uVar3 + 1 + uVar2) - uVar1;
      uVar1 = uVar3;
    }
    else {
      uVar2 = (uVar2 - uVar1) + uVar3;
      uVar1 = uVar3;
    }
  }
  return;
}
