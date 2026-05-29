/* ===== FUN FUN_40e501f8 @ 40e501f8 =====
 * callers: 40e50384:FUN_40e50384
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e50060:FUN_40e50060
 */


undefined4 FUN_40e501f8(void)

{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar2 = 0;
  local_10 = 0;
  local_c = 0;
  local_18 = DAT_40e502b8/*=0x00800400*/;
  uStack_14 = 0;
  do {
    iVar1 = FUN_40e50060(uVar2 & 0xffff,&local_18,0);
    if (iVar1 < 0) goto LAB_40e5028c;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 400);
  uVar2 = 0;
  do {
    iVar1 = FUN_40e50060(uVar2 & 0xffff,&local_18,2);
    if (iVar1 < 0) goto LAB_40e5028c;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x180);
  uVar2 = 0;
  local_18 = DAT_40e502bc/*=0xff803fff*/;
  uStack_14 = DAT_40e502c0/*=0x0100ff80*/;
  local_10 = DAT_40e502c4/*=0x00100200*/;
  local_c = 0x20;
  while (iVar1 = FUN_40e50060(uVar2 & 0xffff,&local_18,4), -1 < iVar1) {
    uVar2 = uVar2 + 1;
    if (uVar2 == 0x180) {
      return 0;
    }
  }
LAB_40e5028c:
  FUN_40e2a1b4(DAT_40e502c8/*=0x47f3ebed*/,uVar2);
  return 0xffffffff;
}
