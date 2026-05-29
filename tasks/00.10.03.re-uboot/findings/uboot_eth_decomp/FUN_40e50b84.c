/* ===== FUN FUN_40e50b84 @ 40e50b84 =====
 * callers: 40e50f20:FUN_40e50f20
 * callees: 40e50b58:FUN_40e50b58
 */


undefined4 FUN_40e50b84(void)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  do {
    uVar2 = uVar3 & 0xff;
    uVar3 = uVar3 + 1;
    FUN_40e50b58(uVar2,1);
    puVar1 = DAT_40e50bd0/*=0x921d4000*/;
  } while (uVar3 != 8);
  *DAT_40e50bd0/*=0x921d4000*/ = 0x30000000;
  puVar1[1] = 0x8800;
  puVar1[0x10] = 0x30000000;
  puVar1[0x11] = 0x8800;
  puVar1[0x70] = 0x11000000;
  return 0;
}
