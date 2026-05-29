/* ===== FUN FUN_40e40094 @ 40e40094 =====
 * callers: 40e40454:FUN_40e40454
 * callees: 40e2a914:FUN_40e2a914
 */


undefined4 FUN_40e40094(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_40e2a914(0xc);
  *DAT_40e40104/*=0x47f56e30*/ = iVar2;
  iVar1 = DAT_40e40108/*=0x9a101000[MDIO]*/;
  if (iVar2 != 0) {
    uVar3 = *(uint *)(DAT_40e40108/*=0x9a101000[MDIO]*/ + 0x14);
    *(int *)(iVar2 + 4) = DAT_40e40108/*=0x9a101000[MDIO]*/;
    *(uint *)(iVar1 + 0x14) = uVar3 & 0xffffbfff;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffff7fff;
    *(undefined4 *)(iVar1 + 0x10) = 0;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x1000;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffdfff;
    *(undefined4 *)(iVar1 + 0xc) = 0;
    return 0;
  }
  return 0x16;
}
