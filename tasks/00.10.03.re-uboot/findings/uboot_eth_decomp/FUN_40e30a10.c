/* ===== FUN FUN_40e30a10 @ 40e30a10 =====
 * callers: 40e21c68:FUN_40e21c68
 * callees: 40e309d4:FUN_40e309d4, 40e40900:FUN_40e40900, 40e45468:FUN_40e45468, 40e45800:FUN_40e45800, 40e4ee40:FUN_40e4ee40
 */


undefined4 FUN_40e30a10(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_44 [2];
  undefined1 auStack_3c [24];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = DAT_40e30a90/*=0x47f53f64*/;
  iVar2 = DAT_40e30a90/*=0x47f53f64*/ + 0x34;
  *(int *)(DAT_40e30a90/*=0x47f53f64*/ + 0x34) = iVar2;
  *(int *)(iVar1 + 0x38) = iVar2;
  FUN_40e4ee40(DAT_40e30a94/*=0x000186a0*/,0);
  FUN_40e45800(local_44,0,0x3c);
  FUN_40e45468(auStack_3c,DAT_40e30a98/*=0x47f399b7*/);
  local_44[0] = 0x80000003;
  local_24 = DAT_40e30a9c/*=0x47f20404*/;
  local_20 = DAT_40e30aa0/*=0x47f20420*/;
  local_18 = DAT_40e30aa4/*=0x47f203dc*/;
  local_1c = DAT_40e30aa8/*=0x47f203f0*/;
  FUN_40e309d4(local_44);
  FUN_40e40900();
  return 0;
}
