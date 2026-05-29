/* ===== FUN FUN_40e50bd4 @ 40e50bd4 =====
 * callers: 40e50c40:FUN_40e50c40
 * callees: (none)
 */


void FUN_40e50bd4(uint param_1,int param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  
  if (param_1 < 5) {
    puVar1 = (uint *)(param_1 * 0x40000 + -0x6de00000);
    uVar2 = *puVar1;
    if (param_2 == 2) {
      uVar2 = uVar2 & 0xffff7fff | 0x2000;
    }
    else {
      if (param_3 == 0) {
        uVar2 = uVar2 & 0xffffdfff | 0x8000;
      }
      else {
        uVar2 = uVar2 | 0xa000;
      }
      if (param_2 == 1) {
        uVar2 = uVar2 | 0x4000;
      }
      else {
        uVar2 = uVar2 & 0xffffbfff;
      }
    }
    *puVar1 = uVar2;
    return;
  }
  return;
}
