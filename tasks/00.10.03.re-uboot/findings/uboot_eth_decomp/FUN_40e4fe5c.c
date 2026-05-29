/* ===== FUN FUN_40e4fe5c @ 40e4fe5c =====
 * callers: 40e50384:FUN_40e50384
 * callees: 40e45800:FUN_40e45800
 */


undefined4 FUN_40e4fe5c(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  
  uVar4 = DAT_40e4ff40/*=0x0104c040*/;
  puVar3 = DAT_40e4ff3c/*=0x92348000[TM]*/;
  uVar8 = 0;
  *DAT_40e4ff3c/*=0x92348000[TM]*/ = 0;
  puVar3[1] = uVar4;
  puVar3[2] = uVar4;
  puVar3[0x16] = 0x3f;
  puVar3[0x17] = 0xf;
  iVar6 = DAT_40e4ff48/*=0x41800000[RAM]*/;
  piVar5 = DAT_40e4ff44/*=0x47f59610*/;
  *DAT_40e4ff44/*=0x47f59610*/ = DAT_40e4ff48/*=0x41800000[RAM]*/;
  piVar5[1] = iVar6;
  iVar6 = iVar6 + 0x8000;
  piVar5[2] = iVar6;
  piVar5[3] = iVar6;
  puVar7 = DAT_40e4ff4c/*=0x417ffffe[RAM]*/;
  do {
    uVar1 = uVar8 & 0xff;
    uVar2 = uVar8 >> 8;
    uVar8 = uVar8 + 1;
    puVar7 = puVar7 + 1;
    *puVar7 = (ushort)(uVar1 << 8) | (ushort)uVar2 & 0xff;
  } while (uVar8 != 0x800);
  uVar8 = 0;
  puVar7 = DAT_40e4ff50/*=0x41807ffe[RAM]*/;
  do {
    uVar1 = uVar8 & 0xff;
    uVar2 = uVar8 >> 8;
    uVar8 = uVar8 + 1;
    puVar7 = puVar7 + 1;
    *puVar7 = (ushort)(uVar1 << 8) | (ushort)uVar2 & 0xff;
    iVar6 = DAT_40e4ff54/*=0x92340000[TM]*/;
  } while (uVar8 != 0x200);
  piVar5[4] = 0;
  *(undefined4 *)(iVar6 + 0xf4) = 0x41000000;
  *(undefined4 *)(iVar6 + 0xf8) = 0x41400000;
  uVar4 = DAT_40e4ff58/*=0x47f59624*/;
  *(int *)(iVar6 + 0xe8) = *piVar5;
  *(int *)(iVar6 + 0xec) = piVar5[2];
  *(undefined4 *)(iVar6 + 0xfc) = DAT_40e4ff5c/*=0x08000800*/;
  puVar3 = DAT_40e4ff3c/*=0x92348000[TM]*/;
  DAT_40e4ff3c/*=0x92348000[TM]*/[0x12] = 0x8000000;
  puVar3[0x13] = 0x2000000;
  puVar3[5] = 0;
  FUN_40e45800(uVar4,0,8);
  return 0;
}
