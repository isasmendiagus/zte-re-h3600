// module: mt7915.ko
// function: RcUpdateBandCtrl @ 0xab694
// size: 1556 bytes
//

undefined4 RcUpdateBandCtrl(int param_1)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  ushort uVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  char *pcVar11;
  int *piVar12;
  uint uVar13;
  int iVar14;
  int *piVar15;
  int iVar16;
  undefined1 *puVar17;
  undefined4 *puVar18;
  int iVar19;
  undefined4 *puVar20;
  int iVar21;
  char local_f0 [4];
  uint local_ec;
  char acStack_e8 [196];
  
  iVar14 = *(int *)(param_1 + 0x4328);
  os_zero_mem(local_f0,200);
  local_f0[0] = *(char *)(iVar14 + 0x79504d);
  if (((uint)(local_f0[0] != '\0') & *(uint *)(param_1 + 0xb58) >> 5) == 0) goto LAB_000ab6d8;
  if (*(char *)(param_1 + 0x32d8) != '\0') {
    piVar15 = (int *)(param_1 + 0xc);
    iVar21 = 0;
    do {
      for (piVar12 = (int *)*piVar15; piVar15 != piVar12; piVar12 = (int *)*piVar12) {
        uVar4 = *(ushort *)((int)piVar12 + -0x12);
        if (uVar4 == 0x40) {
LAB_000ab7f4:
          iVar7 = local_ec * 3;
          cVar1 = **(char **)(piVar12[-3] + 4);
          acStack_e8[iVar7 + 1] = *(char *)(piVar12 + -4);
          acStack_e8[iVar7] = '\x02';
          acStack_e8[iVar7 + 2] = cVar1;
        }
        else {
          if (uVar4 < 0x41) {
            if (uVar4 != 2) {
              if (uVar4 < 3) {
                if (uVar4 == 1) goto LAB_000ab7a8;
              }
              else if ((uVar4 == 4) || (uVar4 == 0x20)) goto LAB_000ab7f4;
              goto LAB_000ab760;
            }
            goto LAB_000ab7f4;
          }
          if (uVar4 == 0x1000) goto LAB_000ab7f4;
          if (uVar4 < 0x1001) {
            if (uVar4 != 0x800) goto LAB_000ab760;
LAB_000ab7a8:
            cVar1 = *(char *)(piVar12 + -4);
            pcVar8 = *(char **)(piVar12[-3] + 4);
            iVar7 = local_ec * 3;
            if (cVar1 == '\0') {
              acStack_e8[iVar7 + 2] = *pcVar8;
              acStack_e8[iVar7] = '\x02';
              acStack_e8[iVar7 + 1] = '\0';
            }
            else {
              cVar3 = *(char *)(*(int *)(piVar12[-3] + 0x18) + 0xc7f);
              acStack_e8[iVar7 + 2] = *pcVar8;
              acStack_e8[iVar7 + 1] = (cVar1 + -1) - cVar3;
              acStack_e8[iVar7] = '\x03';
            }
          }
          else {
            if (uVar4 == 0x2000) goto LAB_000ab7a8;
            if (uVar4 == 0x4000) goto LAB_000ab7f4;
LAB_000ab760:
            if (3 < DebugLevel) {
              printk("%s(): Current not support this type of WdevType=%d\n","rcUpdateBandByType");
            }
          }
        }
        local_ec = local_ec + 1;
      }
      iVar21 = iVar21 + 1;
      piVar15 = piVar15 + 7;
    } while (iVar21 < (int)(uint)*(byte *)(param_1 + 0x32d8));
  }
  iVar19 = *(int *)(param_1 + 0x4328);
  iVar7 = hc_get_chip_cap(*(undefined4 *)(iVar19 + 0xa797a0));
  iVar21 = FUN_000ab5f4(param_1,2);
  if (((iVar21 == 0) || (*(char *)(iVar21 + 0x14) == '\0')) &&
     (iVar21 = FUN_000ab5f4(param_1,1), iVar21 == 0)) {
    iVar21 = param_1;
  }
  pcVar8 = *(char **)(iVar21 + 4);
  if (pcVar8 != (char *)0x0) {
    cVar1 = *pcVar8;
    iVar16 = local_ec + 2;
    iVar21 = local_ec * 3;
    pcVar11 = local_f0 + iVar21;
    iVar9 = 0;
    acStack_e8[iVar21] = '\x05';
    acStack_e8[iVar21 + 2] = cVar1;
    acStack_e8[iVar21 + 1] = '\0';
    do {
      cVar1 = *pcVar8;
      local_ec = iVar16 + iVar9;
      pcVar11[0xc] = (char)iVar9;
      iVar9 = iVar9 + 1;
      pcVar11[0xb] = '\x06';
      pcVar11[0xd] = cVar1;
      pcVar11 = pcVar11 + 3;
    } while (iVar9 != 3);
    if ((*(byte *)(iVar7 + 0x96) & 5) == 5) {
      if (*(char *)(param_1 + 0x32d8) != '\0') {
        *(undefined1 *)(param_1 + 0x16a6) = 1;
        if (*(char *)(param_1 + 0x32d8) != '\x01') {
          *(undefined1 *)(param_1 + 0x19fa) = 1;
        }
        goto LAB_000ab99c;
      }
    }
    else {
      iVar21 = 1;
      pcVar8[10] = '\x01';
      bVar2 = *(byte *)(param_1 + 0x32d8);
      if (bVar2 != 0) {
        pcVar11 = (char *)(param_1 + 0x169c);
        do {
          iVar21 = iVar21 + 1;
          if ((pcVar11[10] != '\0') && (*pcVar11 != *pcVar8)) {
            pcVar11[10] = '\0';
          }
          pcVar11 = pcVar11 + 0x354;
        } while (iVar21 != bVar2 + 1);
LAB_000ab99c:
        puVar17 = (undefined1 *)(param_1 + 0x16a6);
        uVar13 = 0;
        do {
          if (0 < DebugLevel) {
            printk("%s\tPhyCtrl[%d].RadioCtrl.IsBfBand = %d\n","rcUpdateBandForBFMU",uVar13,*puVar17
                  );
          }
          uVar13 = uVar13 + 1;
          puVar17 = puVar17 + 0x354;
        } while (uVar13 < *(byte *)(param_1 + 0x32d8));
      }
    }
    TxBfModuleEnCtrl(iVar19);
    TxBfCfgBfPhy(iVar19);
  }
  if (*(char *)(param_1 + 0x1a08) != '\0') {
    iVar21 = 0;
    do {
      pcVar8 = (char *)wmm_ctrl_get_entry_by_idx(param_1,iVar21);
      if (pcVar8[4] != '\0') {
        cVar1 = *pcVar8;
        iVar7 = local_ec * 3;
        acStack_e8[iVar7] = '\0';
        acStack_e8[iVar7 + 2] = cVar1;
        acStack_e8[iVar7 + 1] = (char)iVar21;
        local_ec = local_ec + 1;
      }
      iVar21 = iVar21 + 1;
    } while (iVar21 < (int)(uint)*(byte *)(param_1 + 0x1a08));
  }
  iVar19 = 1;
  cVar1 = *(char *)(param_1 + 0x32d8);
  iVar7 = local_ec * 3;
  iVar21 = (local_ec + 1) * 3;
  acStack_e8[iVar7] = '\x01';
  acStack_e8[iVar7 + 2] = '\0';
  acStack_e8[iVar7 + 1] = '\0';
  acStack_e8[iVar21] = '\x01';
  acStack_e8[iVar21 + 2] = '\x01';
  acStack_e8[iVar21 + 1] = '\x01';
  if (cVar1 == '\0') {
LAB_000abab8:
    iVar21 = (local_ec + 2) * 3;
    acStack_e8[iVar21 + 2] = '\0';
    acStack_e8[iVar21] = '\a';
    acStack_e8[iVar21 + 1] = '\0';
  }
  else {
    if ((*(byte *)(param_1 + 0x1360) & 1) == 0) {
      if ((cVar1 == '\x01') || ((*(byte *)(param_1 + 0x16b4) & 1) == 0)) goto LAB_000abab8;
    }
    else {
      iVar19 = 0;
    }
    if (param_1 + iVar19 * 0x354 == -0x169c) goto LAB_000abab8;
    iVar21 = (local_ec + 2) * 3;
    cVar3 = *(char *)(param_1 + iVar19 * 0x354 + 0x169c);
    acStack_e8[iVar21] = '\a';
    acStack_e8[iVar21 + 2] = cVar3;
    acStack_e8[iVar21 + 1] = '\0';
  }
  iVar21 = local_ec + 3;
  if (cVar1 == '\x02') {
    puVar20 = (undefined4 *)(param_1 + 0xc);
    do {
      for (puVar18 = (undefined4 *)*puVar20; puVar20 != puVar18; puVar18 = (undefined4 *)*puVar18) {
        while( true ) {
          piVar12 = puVar18 + -2;
          piVar15 = (int *)*piVar12;
          if (piVar12 == piVar15) break;
          pcVar11 = (char *)puVar20[-2];
          pcVar8 = local_f0 + iVar21 * 3;
          piVar6 = (int *)*piVar15;
          do {
            piVar5 = piVar6;
            iVar7 = piVar15[-1];
            iVar21 = iVar21 + 1;
            cVar1 = *pcVar11;
            pcVar8[8] = '\x04';
            pcVar8[9] = (char)iVar7;
            pcVar8[10] = cVar1;
            pcVar8 = pcVar8 + 3;
            piVar6 = (int *)*piVar5;
            piVar15 = piVar5;
          } while (piVar5 != piVar12);
          puVar18 = (undefined4 *)*puVar18;
          if (puVar20 == puVar18) goto LAB_000abb5c;
        }
      }
LAB_000abb5c:
      puVar20 = puVar20 + 7;
    } while (puVar20 != (undefined4 *)(param_1 + 0x44));
  }
  else {
    uVar13 = (uint)*(byte *)(param_1 + 0xc7e);
    if (uVar13 != 0) {
      uVar10 = 0;
      pcVar8 = local_f0 + local_ec * 3;
      do {
        pcVar8[0x12] = (char)uVar10;
        uVar10 = uVar10 + 1;
        pcVar8[0x11] = '\x04';
        pcVar8[0x13] = '\0';
        pcVar8 = pcVar8 + 3;
      } while (uVar13 != uVar10);
      iVar21 = iVar21 + uVar13;
    }
  }
  local_ec = iVar21 - 1;
  if (0x40 < local_ec) {
    local_ec = 0x40;
  }
LAB_000ab6d8:
  iVar14 = AsicSetDbdcCtrl(iVar14,local_f0);
  if ((iVar14 != 0) && (-1 < DebugLevel)) {
    printk("%s(): Error for conifgure dbdc, ret = %d !\n","RcUpdateBandCtrl");
  }
  return 0;
}

