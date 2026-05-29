/* ===== FUN FUN_40e502cc @ 40e502cc =====
 * callers: 40e50348:FUN_40e50348
 * callees: (none)
 */


void FUN_40e502cc(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = *DAT_40e502ec/*=0x92350000*/ & 0xfff0ffff | 0x200000;
  }
  else {
    uVar1 = *DAT_40e502ec/*=0x92350000*/ & 0xfff0ffff | 0x2f0000;
  }
  *DAT_40e502ec/*=0x92350000*/ = uVar1;
  return;
}
