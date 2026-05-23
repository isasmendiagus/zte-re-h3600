// kallsyms symbol: denali_init
// string @ 0xc06008b1, .value @ 0xc05e6e60 = 0xc023bf4c
// Function: FUN_c023bf4c @ 0xc023bf4c
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_c023bf4c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  
  if ((*(int *)(param_1 + 0x5a0) == 1) && (2 < DAT_c069d044 + 1U)) {
    FUN_c046918c(&DAT_c05ae850);
    return -0x16;
  }
  iVar1 = FUN_c01ed3bc(*(undefined4 *)(param_1 + 0x5b4),0x1000,0x80d1);
  *(int *)(param_1 + 0x5ac) = iVar1;
  if (iVar1 == 0) {
    return -0xc;
  }
  *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)(param_1 + 0x5b4);
  FUN_c023ba10(param_1);
  uVar3 = DAT_c023c588;
  *(undefined4 *)(param_1 + 0x664) = 0;
  *(undefined4 *)(param_1 + 0x5cc) = 0;
  FUN_c0044d54(param_1 + 0x5d0,s__x_>wait_c05853a0,uVar3);
  *(undefined4 *)(param_1 + 0x5dc) = 0;
  *(undefined4 *)(param_1 + 0x598) = 0;
  *(undefined4 *)(param_1 + 0x5e0) = 0;
  FUN_c023a1dc(param_1,0);
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x410) = 0xffff;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x460) = 0xffff;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x4b0) = 0xffff;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x500) = 0xffff;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x420) = 0x21fd;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x470) = 0x21fd;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x4c0) = 0x21fd;
  iVar1 = *(int *)(param_1 + 0x5c4);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066b2b8 != (code *)0x0) {
    (*DAT_c066b2b8)();
  }
  *(undefined4 *)(iVar1 + 0x510) = 0x21fd;
  iVar1 = FUN_c004e110(*(undefined4 *)(param_1 + 0x668),FUN_c023a0e4,0,0x80,s_denali_nand_c05ae88c,
                       param_1);
  if (iVar1 != 0) {
    FUN_c046918c(&DAT_c05ae898);
    return -0x13;
  }
  FUN_c023a1ac(param_1);
  *(undefined1 **)(param_1 + 0x284) = &LAB_c0239f08;
  *(char **)(param_1 + 0x38) = s_denali_nand_c05ae88c;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(int *)(param_1 + 0xe8) = param_1 + 0x250;
  *(code **)(param_1 + 0x26c) = FUN_c0239d94;
  *(undefined1 **)(param_1 + 0x288) = &LAB_c0239d20;
  *(undefined1 **)(param_1 + 600) = &LAB_c0239d34;
  iVar1 = FUN_c0234d48(param_1,*(undefined4 *)(param_1 + 0x680),0);
  if (iVar1 == 0) {
    FUN_c01ed868(*(undefined4 *)(param_1 + 0x5b4),*(undefined4 *)(param_1 + 0x5ac));
    iVar1 = FUN_c01ed3bc(*(undefined4 *)(param_1 + 0x5b4),
                         *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x14),0x80d0);
    *(int *)(param_1 + 0x5ac) = iVar1;
    if (iVar1 == 0) {
      iVar1 = -0xc;
      goto LAB_c023c470;
    }
    iVar1 = *(int *)(param_1 + 0x5b4);
    if (iVar1 == 0) {
      puVar8 = &DAT_c06744c4;
    }
    else {
      puVar8 = *(undefined4 **)(iVar1 + 0x10c);
      if (*(undefined4 **)(iVar1 + 0x10c) == (undefined4 *)0x0) {
        puVar8 = &DAT_c06744c4;
      }
    }
    iVar1 = (*(code *)puVar8[0xe])(iVar1,(code *)puVar8[0xe],0xffffffff,0);
    if (iVar1 != 0) {
      FUN_c046918c(&DAT_c05ae8bc);
      goto LAB_c023c470;
    }
    iVar1 = *(int *)(param_1 + 0x5b4);
    if (iVar1 == 0) {
      puVar8 = &DAT_c06744c4;
    }
    else {
      puVar8 = *(undefined4 **)(iVar1 + 0x10c);
      if (*(undefined4 **)(iVar1 + 0x10c) == (undefined4 *)0x0) {
        puVar8 = &DAT_c06744c4;
      }
    }
    iVar1 = (*(code *)puVar8[4])
                      (iVar1,_DAT_c06b7084 + (*(uint *)(param_1 + 0x5ac) + 0x40000000 >> 0xc) * 0x20
                       ,*(uint *)(param_1 + 0x5ac) & 0xfff,
                       *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x14),0,0);
    *(int *)(param_1 + 0x5b0) = iVar1;
    if (iVar1 == -1) {
      iVar1 = -5;
      FUN_c01e7918(*(undefined4 *)(param_1 + 0x5b4),s_Spectra__failed_to_map_DMA_buffe_c05ae8e4);
      goto LAB_c023c470;
    }
    iVar1 = *(int *)(*(int *)(param_1 + 0x5c4) + 0x250);
    DataSynchronizationBarrier(0xf);
    uVar7 = iVar1 - 1;
    uVar4 = *(uint *)(param_1 + 0x2c8);
    uVar5 = *(uint *)(param_1 + 0x2c4);
    uVar6 = uVar4 << (uVar7 & 0xff);
    uVar9 = *(int *)(param_1 + 0x2cc) << (uVar7 & 0xff) | uVar4 << (iVar1 - 0x21U & 0xff) |
            uVar4 >> (0x20 - uVar7 & 0xff);
    *(uint *)(param_1 + 0x2c8) = uVar6;
    *(undefined4 *)(param_1 + 0x2ac) = 0x8200;
    uVar4 = *(int *)(param_1 + 0x2b4) + -1 + iVar1;
    bVar10 = DAT_c06bd7d4 == '\x01';
    *(uint *)(param_1 + 0x2cc) = uVar9;
    *(int *)(param_1 + 8) = (int)((ulonglong)uVar5 * (ulonglong)uVar6);
    *(uint *)(param_1 + 0xc) =
         uVar5 * uVar9 + uVar6 * ((int)uVar5 >> 0x1f) +
         (int)((ulonglong)uVar5 * (ulonglong)uVar6 >> 0x20);
    *(int *)(param_1 + 0x66c) = iVar1;
    *(uint *)(param_1 + 0x2b4) = uVar4;
    iVar2 = *(int *)(param_1 + 700) + -1 + iVar1;
    *(uint *)(param_1 + 0x2d0) =
         (uVar6 >> (uVar4 & 0xff) | uVar9 << (0x20 - uVar4 & 0xff) | uVar9 >> (uVar4 - 0x20 & 0xff))
         - 1;
    *(int *)(param_1 + 0x2c0) = *(int *)(param_1 + 0x2c0) + -1 + iVar1;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) << (uVar7 & 0xff);
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) << (uVar7 & 0xff);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) << (uVar7 & 0xff);
    *(int *)(param_1 + 0x67c) = iVar1 * *(int *)(param_1 + 0x67c);
    *(int *)(param_1 + 700) = iVar2;
    *(int *)(param_1 + 0x2b8) = iVar2;
    if (bVar10) {
      FUN_c046918c(s_16_bit_device__c05ae908);
      *(uint *)(param_1 + 0x2ac) = *(uint *)(param_1 + 0x2ac) | 2;
    }
    else {
      FUN_c046918c(s_8_bit_device__c05ae918);
    }
    iVar1 = _DAT_c06bd7b0;
    bVar10 = _DAT_c06bd7b0 == 0x1580f198;
    bVar11 = _DAT_c06bd7b0 == 0x1590da98;
    bVar12 = _DAT_c06bd7b0 == 0x1d00f101;
    bVar13 = _DAT_c06bd7b0 == -0x6aff0e14;
    bVar14 = _DAT_c06bd7b0 == -0x6aef2514;
    *(code **)(param_1 + 0x544) = FUN_c023b55c;
    *(code **)(param_1 + 0x548) = FUN_c023a420;
    *(code **)(param_1 + 0x540) = FUN_c023a420;
    *(int *)(param_1 + 0x514) = *(int *)(param_1 + 0x66c) << 9;
    *(code **)(param_1 + 0x564) = FUN_c023b3d4;
    *(code **)(param_1 + 0x560) = FUN_c023a8c4;
    *(code **)(param_1 + 0x554) = FUN_c023aa3c;
    *(code **)(param_1 + 0x28c) = FUN_c0239e98;
    *(undefined4 *)(param_1 + 0x50c) = 2;
    *(undefined4 *)(param_1 + 0x520) = 4;
    if ((bVar14 || (bVar13 || (bVar12 || (bVar10 || bVar11)))) ||
       ((iVar1 == -0x6a7f0e3e || iVar1 == -0x6a6f253e && (DAT_c06bd7b4 == -0x7e)))) {
      *(undefined4 *)(param_1 + 0x684) = 1;
    }
    uVar6 = *(uint *)(param_1 + 0x2b8);
    uVar6 = *(uint *)(param_1 + 8) >> (uVar6 & 0xff) |
            *(uint *)(param_1 + 0xc) << (0x20 - uVar6 & 0xff) |
            *(uint *)(param_1 + 0xc) >> (uVar6 - 0x20 & 0xff);
    *(uint *)(param_1 + 0x674) = uVar6;
    uVar3 = FUN_c0181098(uVar6,*(undefined4 *)(param_1 + 0x2c4));
    *(undefined4 *)(param_1 + 0x678) = uVar3;
    iVar1 = FUN_c0233bd4(param_1);
    if (iVar1 == 0) {
      iVar1 = FUN_c0217360(param_1,_DAT_c06ada14,_DAT_c06ada18);
      if (iVar1 == 0) {
        return 0;
      }
      FUN_c01e7918(*(undefined4 *)(param_1 + 0x5b4),s_denali__Failed_to_register_MTD____c05ae928,
                   iVar1);
      goto LAB_c023c470;
    }
  }
  iVar1 = -6;
LAB_c023c470:
  uVar3 = *(undefined4 *)(param_1 + 0x668);
  FUN_c023a1dc(param_1,0);
  FUN_c004cf1c(uVar3,param_1);
  return iVar1;
}

