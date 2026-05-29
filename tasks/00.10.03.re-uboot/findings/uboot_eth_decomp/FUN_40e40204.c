/* ===== FUN FUN_40e40204 @ 40e40204 =====
 * callers: 40e40484:FUN_40e40484, 40e404fc:FUN_40e404fc, 40e4060c:FUN_40e4060c, 40e50c40:FUN_40e50c40
 * callees: 40e45a90:FUN_40e45a90
 */


undefined4 FUN_40e40204(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(*DAT_40e402dc/*=0x47f56e30*/ + 4);
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffbfff;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xfffff3ff;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x400;
  *(undefined4 *)(iVar1 + 4) = param_3;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xfffffc1f;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | param_1 << 5;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffffe0;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | param_2;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x4000;
  do {
  } while ((*(uint *)(iVar1 + 0x10) & 1) == 0);
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffbfff;
  FUN_40e45a90(3);
  return 0;
}
