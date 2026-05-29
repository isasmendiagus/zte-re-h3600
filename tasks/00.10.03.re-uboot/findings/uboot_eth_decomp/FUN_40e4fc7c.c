/* ===== FUN FUN_40e4fc7c @ 40e4fc7c =====
 * callers: 40e21050:FUN_40e21050
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45a90:FUN_40e45a90, 40e4fa08:FUN_40e4fa08, 40e4fa9c:FUN_40e4fa9c
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_40e4fc7c(void)

{
  int iVar1;
  
  FUN_40e4fa08(0);
  _DAT_94000008 = _DAT_94000008 & 0xffffffcf;
  FUN_40e45a90(100);
  _DAT_94000008 = _DAT_94000008 | 0x20;
  FUN_40e45a90(100);
  FUN_40e4fa9c();
  FUN_40e2a1b4(DAT_40e4fd14/*=0x47f3ebb6*/);
  _DAT_94000008 = _DAT_94000008 | 0x10;
  FUN_40e2a1b4(DAT_40e4fd18/*=0x47f3ebc9*/);
  iVar1 = DAT_40e4fd1c/*=0x94100000[SYSCTRL]*/;
  *(uint *)(DAT_40e4fd1c/*=0x94100000[SYSCTRL]*/ + 0x10) = *(uint *)(DAT_40e4fd1c/*=0x94100000[SYSCTRL]*/ + 0x10) & 0xfffff7ff;
  *(uint *)(iVar1 + 0x10) =
       *(uint *)(iVar1 + 0x10) & 0xfffffc3f | ((uint)(*(int *)(DAT_40e4fd20/*=0x9a107000*/ + 8) << 4) >> 0x1c) << 6
  ;
  return 0;
}
