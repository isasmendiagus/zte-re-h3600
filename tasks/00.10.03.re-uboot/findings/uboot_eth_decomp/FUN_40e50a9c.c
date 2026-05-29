/* ===== FUN FUN_40e50a9c @ 40e50a9c =====
 * callers: 40e50b0c:FUN_40e50b0c
 * callees: (none)
 */


undefined4 FUN_40e50a9c(void)

{
  int iVar1;
  
  iVar1 = DAT_40e50af8/*=0x92388000*/;
  *(undefined4 *)(DAT_40e50af8/*=0x92388000*/ + 4) = DAT_40e50afc/*=0x000200ff*/;
  *(undefined4 *)(iVar1 + 0x340) = DAT_40e50b00/*=0xff5555ff*/;
  *(undefined4 *)(iVar1 + 0x344) = 0x3e;
  *(undefined4 *)(iVar1 + 0x380) = 0x3f;
  *(undefined4 *)(iVar1 + 0x63c) = DAT_40e50b04/*=0xaaaaaaaa*/;
  *(undefined4 *)(iVar1 + 0x1c0) = 0xff;
  *(undefined4 *)(iVar1 + 0x1c4) = 0x5555;
  *(undefined4 *)(iVar1 + 0x188) = DAT_40e50b08/*=0x000bf874*/;
  *(undefined4 *)(iVar1 + 0x2c0) = 0xff;
  *(undefined4 *)(iVar1 + 0x300) = 0xffff;
  *(undefined4 *)(iVar1 + 0x304) = 0x3e;
  return 0;
}
