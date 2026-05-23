// module: mt7915.ko
// function: ExtEventICap96BitDataParser @ 0x1a649c
// size: 1916 bytes
//

void ExtEventICap96BitDataParser(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int extraout_r1;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  int local_54;
  void *local_4c;
  void *local_48;
  void *local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  int local_2c;
  
  puVar7 = *(uint **)(param_1 + 0xa78acc);
  local_4c = (void *)0x0;
  local_48 = (void *)0x0;
  local_44 = (void *)0x0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar9 = (uint)*(byte *)(iVar2 + 0x164);
  iVar12 = *(int *)(iVar2 + 0x160);
  iVar16 = *(int *)(iVar2 + 0x178);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","ExtEventICap96BitDataParser");
  }
  local_40 = 0x810c0098;
  MtCmdMultipleMacRegAccessRead(param_1,&local_40,1);
  local_38 = 0x810c00b4;
  MtCmdMultipleMacRegAccessRead(param_1,&local_38,1);
  local_30 = 0x810c0090;
  uVar14 = local_34 - local_3c;
  MtCmdMultipleMacRegAccessRead(param_1,&local_30,1);
  uVar14 = uVar14 >> 2;
  iVar10 = -((local_2c << 0xe) >> 0x1f);
  if (0 < DebugLevel) {
    printk(&_LC55,local_3c,local_34,iVar10);
  }
  if (iVar10 == 0) {
    iVar10 = (uVar14 + 1) * 4;
    local_54 = (int)((ulonglong)uVar9 * 0xaaaaaaab >> 0x20);
    iVar16 = ((iVar16 * ((uint)(local_54 << 0x17) >> 0x18) - uVar14) + 0x3fffffff) * 4;
    os_zero_mem(*(int *)(param_1 + 0xa78a88) + iVar10,iVar16);
    os_zero_mem(*(int *)(param_1 + 0xa78a8c) + iVar10,iVar16);
    os_zero_mem(*(int *)(param_1 + 0xa78a90) + iVar10,iVar16);
  }
  else {
    uVar8 = ((uint)((int)((ulonglong)uVar9 * 0xaaaaaaab >> 0x20) << 0x17) >> 0x18) * iVar16 * 4;
    iVar16 = os_alloc_mem(param_1,&local_4c,uVar8);
    if (((iVar16 != 0) || (iVar16 = os_alloc_mem(param_1,&local_48,uVar8), iVar16 != 0)) ||
       (iVar16 = os_alloc_mem(param_1,&local_44,uVar8), iVar16 != 0)) {
      if (-1 < DebugLevel) {
        printk("%s : Not enough memory for dynamic allocating !!\n","ExtEventICap96BitDataParser");
      }
      goto LAB_001a67dc;
    }
    os_zero_mem(local_4c,uVar8);
    os_zero_mem(local_48,uVar8);
    os_zero_mem(local_44,uVar8);
    os_move_mem(local_4c,*(void **)(param_1 + 0xa78a88),uVar8);
    os_move_mem(local_48,*(void **)(param_1 + 0xa78a8c),uVar8);
    os_move_mem(local_44,*(void **)(param_1 + 0xa78a90),uVar8);
    uVar8 = uVar8 >> 2;
    if (uVar8 != 0) {
      uVar13 = 0;
      do {
        __aeabi_uidivmod(uVar13 + uVar14 + 1,uVar8);
        *(undefined4 *)(*(int *)(param_1 + 0xa78a88) + uVar13 * 4) =
             *(undefined4 *)((int)local_4c + extraout_r1 * 4);
        *(undefined4 *)(*(int *)(param_1 + 0xa78a8c) + uVar13 * 4) =
             *(undefined4 *)((int)local_48 + extraout_r1 * 4);
        *(undefined4 *)(*(int *)(param_1 + 0xa78a90) + uVar13 * 4) =
             *(undefined4 *)((int)local_44 + extraout_r1 * 4);
        uVar13 = uVar13 + 1;
      } while (uVar13 != uVar8);
    }
  }
  iVar16 = Get_System_CapNode_Info(param_1);
  if (*(int *)(iVar2 + 0x17c) == iVar16) {
    if (0 < DebugLevel) {
      printk(&_LC57);
    }
    uVar14 = *(uint *)(iVar2 + 0x16c);
    if (2 < uVar14) {
      uVar8 = 0;
      do {
        if (*(char *)(iVar12 + 0x11) == '\x04') {
          puVar7[1] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 0x14) >> 0x1c;
          puVar7[9] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 0x18) >> 0x1c;
          puVar7[0x11] = *(uint *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) & 0xf;
          *puVar7 = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 8) >> 0x1c;
          puVar7[8] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 0xc) >> 0x1c;
          puVar7[0x10] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 0x10) >> 0x1c;
          puVar7[3] = *(uint *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) & 0xf;
          puVar7[0xb] = *(uint *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) >> 0x1c;
          puVar7[0x13] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 4) >> 0x1c;
          puVar7[2] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 0x10) >> 0x1c;
          puVar7[10] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 0x14) >> 0x1c;
          puVar7[0x12] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 0x18) >> 0x1c;
          puVar7[5] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 4) >> 0x1c;
          puVar7[0xd] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 8) >> 0x1c;
          puVar7[0x15] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 0xc) >> 0x1c;
          puVar7[4] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 0x18) >> 0x1c;
          puVar7[0xc] = *(uint *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) & 0xf;
          puVar7[0x14] = *(uint *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) >> 0x1c;
          puVar7[7] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 0xc) >> 0x1c;
          puVar7[0xf] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 0x10) >> 0x1c;
          puVar7[0x17] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 0x14) >> 0x1c;
          puVar7[6] = *(uint *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) >> 0x1c;
          puVar7[0xe] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 4) >> 0x1c;
          puVar7[0x16] = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 8) >> 0x1c;
          puVar5 = puVar7;
          do {
            puVar6 = puVar5 + 8;
            puVar5[1] = puVar5[1] - 8;
            *puVar5 = *puVar5 - 8;
            puVar5[3] = puVar5[3] - 8;
            puVar5[2] = puVar5[2] - 8;
            puVar5[5] = puVar5[5] - 8;
            puVar5[4] = puVar5[4] - 8;
            puVar5[7] = puVar5[7] - 8;
            puVar5[6] = puVar5[6] - 8;
            puVar5 = puVar6;
          } while (puVar7 + 0x18 != puVar6);
          uVar14 = *(uint *)(iVar2 + 0x16c);
        }
        puVar7 = puVar7 + 0x18;
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar14 / 3);
    }
  }
  else {
    if (0 < DebugLevel) {
      printk(&_LC58);
    }
    uVar14 = *(uint *)(iVar2 + 0x170);
    if (uVar14 != 0) {
      uVar8 = 0;
      do {
        while (*(char *)(iVar12 + 0x12) == '\f') {
          uVar13 = *(uint *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) & 0xfff;
          puVar7[1] = uVar13;
          uVar14 = uVar13;
          if (0x7ff < uVar13) {
            uVar14 = uVar13 - 0x1000;
          }
          uVar11 = (uint)(*(int *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) << 8) >> 0x14;
          *puVar7 = uVar11;
          uVar3 = *(uint *)(*(int *)(param_1 + 0xa78a88) + uVar8 * 4) >> 0x18;
          puVar7[3] = uVar3;
          uVar3 = uVar3 | (*(uint *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) & 0xf) << 8;
          puVar7[3] = uVar3;
          uVar19 = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 0x10) >> 0x14;
          puVar7[2] = uVar19;
          uVar18 = (uint)(*(int *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) << 4) >> 0x14;
          puVar7[5] = uVar18;
          uVar4 = *(uint *)(*(int *)(param_1 + 0xa78a8c) + uVar8 * 4) >> 0x1c;
          puVar7[4] = uVar4;
          uVar4 = uVar4 | (uint)*(byte *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 4;
          puVar7[4] = uVar4;
          uVar17 = (uint)(*(int *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4) << 0xc) >> 0x14;
          puVar7[7] = uVar17;
          uVar15 = *(uint *)(*(int *)(param_1 + 0xa78a90) + uVar8 * 4);
          uVar8 = uVar8 + 1;
          if (0x7ff < uVar13) {
            puVar7[1] = uVar14;
          }
          if (0x7ff < uVar11) {
            *puVar7 = uVar11 - 0x1000;
          }
          uVar15 = uVar15 >> 0x14;
          if (0x7ff < uVar3) {
            puVar7[3] = uVar3 - 0x1000;
          }
          puVar7[6] = uVar15;
          if (0x7ff < uVar19) {
            puVar7[2] = uVar19 - 0x1000;
          }
          if (0x7ff < uVar18) {
            puVar7[5] = uVar18 - 0x1000;
          }
          if (0x7ff < uVar4) {
            puVar7[4] = uVar4 - 0x1000;
          }
          if (0x7ff < uVar17) {
            puVar7[7] = uVar17 - 0x1000;
          }
          if (0x7ff < uVar15) {
            puVar7[6] = uVar15 - 0x1000;
          }
          uVar14 = *(uint *)(iVar2 + 0x170);
          puVar7 = puVar7 + 8;
          if (uVar14 <= uVar8) goto LAB_001a6750;
        }
        uVar8 = uVar8 + 1;
        puVar7 = puVar7 + 8;
      } while (uVar8 < uVar14);
    }
  }
LAB_001a6750:
  if (uVar9 == 0) {
    iVar12 = 0;
  }
  else {
    iVar12 = 0;
    iVar16 = *(int *)(iVar2 + 0x160);
    iVar2 = iVar16 + uVar9 * 0x1f;
    do {
      piVar1 = (int *)(iVar16 + 0xc);
      iVar16 = iVar16 + 0x1f;
      iVar12 = iVar12 + *piVar1;
    } while (iVar16 != iVar2);
  }
  if (0 < DebugLevel) {
    printk(&_LC48,"ExtEventICap96BitDataParser",iVar12);
  }
  *(undefined4 *)(param_1 + 0xa78a50) = 0;
LAB_001a67dc:
  if (local_4c != (void *)0x0) {
    os_free_mem();
  }
  if (local_48 != (void *)0x0) {
    os_free_mem();
  }
  if (local_44 != (void *)0x0) {
    os_free_mem();
  }
  if ((0 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","ExtEventICap96BitDataParser",*(undefined4 *)(param_1 + 0xa78a50))
     , 2 < DebugLevel)) {
    printk("%s<-----------------\n","ExtEventICap96BitDataParser");
  }
  return;
}

