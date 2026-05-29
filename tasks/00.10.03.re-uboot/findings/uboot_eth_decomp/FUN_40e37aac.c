/* ===== FUN FUN_40e37aac @ 40e37aac =====
 * callers: 40e21c68:FUN_40e21c68
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e37a30:FUN_40e37a30, 40e3ddd8:FUN_40e3ddd8, 40e3e72c:FUN_40e3e72c, 40e3e988:FUN_40e3e988, 40e3fd08:FUN_40e3fd08
 */


void FUN_40e37aac(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  piVar2 = DAT_40e37b94/*=0x47f59604*/;
  iVar1 = DAT_40e37b90/*=0x47f549f8*/;
  iVar6 = DAT_40e37b90/*=0x47f549f8*/ + 0xc0;
  *(undefined1 **)(DAT_40e37b90/*=0x47f549f8*/ + 0xc4) = &DAT_00d00000;
  *(undefined1 **)(iVar1 + 0xc0) = &DAT_00d00000;
  iVar7 = *piVar2;
  *(int *)(iVar1 + 0x9c) = iVar6;
  if (((iVar7 != 1) || (iVar6 = FUN_40e3e988(), iVar6 == 0)) &&
     ((*piVar2 != 3 || (iVar6 = FUN_40e3fd08(DAT_40e37ba4/*=0x47f54ab8*/), iVar6 == 0)))) {
    piVar3 = DAT_40e37b94/*=0x47f59604*/;
    if (*piVar2 == 0) {
      iVar6 = FUN_40e3e72c();
      uVar5 = DAT_40e37ba4/*=0x47f54ab8*/;
      uVar4 = DAT_40e37b9c/*=0x0555aaaa*/;
      if (iVar6 == 0) {
        *piVar3 = 1;
        iVar6 = FUN_40e3e988(uVar5);
      }
      else {
        *piVar3 = 3;
        uVar5 = DAT_40e37ba4/*=0x47f54ab8*/;
        *(undefined4 *)(DAT_40e37ba0/*=0x94200000[PINMUX]*/ + 8) = uVar4;
        iVar6 = FUN_40e3fd08(uVar5);
      }
      if (iVar6 != 0) goto LAB_40e37b7c;
    }
    iVar6 = FUN_40e3ddd8(DAT_40e37b98/*=0x47f54a00*/,1);
    if (iVar6 == 0) {
      FUN_40e37a30();
    }
  }
LAB_40e37b7c:
  FUN_40e2a1b4(DAT_40e37ba8/*=0x47f3bdb1*/,*(uint *)(iVar1 + 0xb8) >> 10);
  return;
}
