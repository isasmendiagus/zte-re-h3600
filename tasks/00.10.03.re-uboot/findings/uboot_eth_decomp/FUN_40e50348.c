/* ===== FUN FUN_40e50348 @ 40e50348 =====
 * callers: 40e50384:FUN_40e50384
 * callees: 40e502cc:FUN_40e502cc
 */


undefined4 FUN_40e50348(void)

{
  int iVar1;
  int iVar2;
  
  FUN_40e502cc(1);
  iVar2 = DAT_40e5037c/*=0x41b00000[RAM]*/;
  iVar1 = DAT_40e50378/*=0x92350000*/;
  *(int *)(DAT_40e50378/*=0x92350000*/ + 0x50) = DAT_40e5037c/*=0x41b00000[RAM]*/;
  *(int *)(iVar1 + 0x60) = iVar2 + 0x100000;
  *(undefined4 *)(iVar1 + 0x3c) = DAT_40e50380/*=0x00400040*/;
  return 0;
}
