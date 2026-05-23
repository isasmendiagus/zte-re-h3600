// module: mt7915.ko
// function: show_mumimo_algorithm_monitor @ 0x18122c
// size: 868 bytes
//

void show_mumimo_algorithm_monitor(int param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  char *local_44 [2];
  uint local_3c;
  undefined2 local_38 [8];
  undefined2 auStack_28 [2];
  
  local_44[0] = param_2;
  pcVar4 = strsep(local_44,"");
  if (pcVar4 != (char *)0x0) {
    if (*pcVar4 == '1') {
      FUN_00180474(param_1,local_44[0]);
      return;
    }
    if (*pcVar4 == '4') {
      uVar14 = *(uint *)(param_1 + 0x795a60);
      cVar1 = *(char *)(param_1 + 0x795a64);
      uVar12 = *(uint *)(param_1 + 0x795a58);
      cVar2 = *(char *)(param_1 + 0x795a5c);
      uVar8 = *(uint *)(param_1 + 0x795a78);
      cVar3 = *(char *)(param_1 + 0x795a7c);
      if (0xdfffffff < uVar14) {
        FUN_0017f59c(param_1);
      }
      if (0xdfffffff < uVar12) {
        FUN_0017f59c(param_1);
      }
      if (0xdfffffff < uVar8) {
        FUN_0017f59c(param_1);
      }
      if (cVar3 == '\0' && (cVar2 == '\0' && cVar1 == '\0')) {
        puVar9 = local_38;
        do {
          uVar5 = FUN_00174528(param_1,uVar14 + 0x3f2);
          puVar10 = puVar9 + 1;
          if (uVar5 < 0x121) {
            *puVar9 = (short)uVar5;
          }
          else {
            *puVar9 = 0;
          }
          puVar9 = puVar10;
        } while (puVar10 != auStack_28);
        iVar6 = FUN_00174528(param_1,uVar14 + 0x544);
        uVar12 = uVar12 + iVar6 * 0x10;
        if (0xdfffffff < uVar12) {
          FUN_0017f59c(param_1);
        }
        if (0 < DebugLevel) {
          printk("|-(0x%08X)MURU MU ALGORITHM MONITOR:\n",uVar14);
        }
        uVar5 = 0;
        local_3c = 0;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar12,&local_3c);
        uVar14 = local_3c;
        local_3c = 0;
        uVar11 = uVar14 & 3;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar12 + 4,&local_3c);
        uVar12 = local_3c;
        if (uVar11 == 3) {
          uVar13 = uVar8 + 0x1e;
          do {
            uVar7 = FUN_00174570(param_1,uVar8);
            if ((((uVar7 == (uVar14 << 0x12) >> 0x1b) &&
                 (uVar7 = FUN_00174570(param_1,uVar8 + 1), (uVar14 << 0xd) >> 0x1b == uVar7)) &&
                (uVar7 = FUN_00174570(param_1,uVar8 + 2), (uVar14 << 8) >> 0x1b == uVar7)) &&
               (uVar7 = FUN_00174570(param_1,uVar8 + 3), (uVar14 << 3) >> 0x1b == uVar7)) {
              uVar5 = FUN_00174570(param_1,uVar8 + 4);
            }
            uVar8 = uVar8 + 6;
          } while (uVar8 != uVar13);
        }
        else {
          uVar5 = (uVar14 << 0xd) >> 0x1b;
        }
        if ((0 < DebugLevel) && (printk("\n GroupID = %d",uVar5), 0 < DebugLevel)) {
          uVar8 = (uVar14 << 0x12) >> 0x1b;
          printk("| |-u1PFIDUser0  = %u WlanIdx = %u Mustream = %u\n",uVar8,local_38[uVar8],
                 ((uVar12 << 0x16) >> 0x1e) + 1);
        }
        if (uVar11 != 0) {
          if (0 < DebugLevel) {
            uVar8 = (uVar14 << 0xd) >> 0x1b;
            printk("| |-u1PFIDUser1  = %u WlanIdx = %u Mustream = %u\n",uVar8,local_38[uVar8],
                   ((uVar12 << 0x14) >> 0x1e) + 1);
            if (uVar11 == 1) {
              return;
            }
            if (DebugLevel < 1) {
              return;
            }
            uVar8 = (uVar14 << 8) >> 0x1b;
            printk("| |-u1PFIDUser2  = %u WlanIdx = %u Mustream = %u\n",uVar8,local_38[uVar8],
                   ((uVar12 << 0x12) >> 0x1e) + 1);
          }
          if ((uVar11 == 3) && (0 < DebugLevel)) {
            uVar8 = (uVar14 << 3) >> 0x1b;
            printk("| |-u1PFIDUser3  = %u WlanIdx = %u Mustream = %u\n",uVar8,local_38[uVar8],
                   ((uVar12 << 0x10) >> 0x1e) + 1);
          }
        }
      }
    }
  }
  return;
}

