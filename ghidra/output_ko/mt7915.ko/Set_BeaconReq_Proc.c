// module: mt7915.ko
// function: Set_BeaconReq_Proc @ 0x21f600
// size: 1700 bytes
//

undefined4 Set_BeaconReq_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  byte bVar2;
  char *pcVar3;
  size_t sVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  undefined1 *puVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  char *local_bc [2];
  char *local_b4;
  undefined2 local_b0 [2];
  int local_ac;
  uint local_a5;
  undefined4 local_a1;
  undefined4 local_9d;
  undefined1 local_99;
  ushort local_98;
  undefined1 auStack_96 [14];
  char *local_88;
  undefined1 local_84;
  undefined1 local_83;
  char local_82;
  char local_81;
  byte local_80;
  byte local_7f [15];
  undefined1 uStack_70;
  undefined1 local_6f [59];
  undefined2 local_34;
  undefined1 local_32;
  byte local_31;
  uint local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined1 local_24;
  
  local_a5 = 0x2d320100;
  local_a1 = 0xc0bf7f3d;
  local_9d = 0x364630c3;
  local_99 = 0xdd;
  iVar12 = 0;
  uVar14 = *(uint *)(*param_1 + 0x3c);
  uVar13 = 0xffff;
  local_bc[0] = param_2;
  __memzero(&local_98,0x78);
  local_32 = 1;
  local_30 = local_a5;
  uStack_2c = local_a1;
  uStack_28 = local_9d;
  local_31 = 0xd;
  local_24 = local_99;
  do {
    pcVar3 = strsep(local_bc,"!");
    local_b4 = pcVar3;
    if (pcVar3 == (char *)0x0) {
      if (iVar12 - 7U < 5) {
        local_80 = local_80 | 1;
        uVar7 = HcGetMaxStaNum(param_1);
        if (uVar13 < uVar7) {
          if (param_1 + uVar13 * 0x530 + 0x28748 == (int *)0x0) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s: pEntry is  NULL!\n","Set_BeaconReq_Proc");
            uVar6 = 0;
          }
          else {
            if (local_81 == '\x01') {
              uVar7 = (uint)*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3);
              if (((*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3) & 0x20) == 0) && (-1 < DebugLevel)
                 ) {
                printk("%s: invalid Measure Mode. %d, Peer STA Support(PASS:%d, ACT:%d, TAB:%d)!\n",
                       "Set_BeaconReq_Proc",1,(uVar7 << 0x1b) >> 0x1f,uVar7 & 0x20,
                       (uVar7 << 0x19) >> 0x1f);
              }
            }
            else if (local_81 == '\0') {
              uVar7 = (uint)*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3);
              if (((*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3) & 0x10) == 0) && (-1 < DebugLevel)
                 ) {
                printk("%s: invalid Measure Mode. %d, Peer STA Support(PASS:%d, ACT:%d, TAB:%d)!\n",
                       "Set_BeaconReq_Proc",uVar7 & 0x10,uVar7 & 0x10,(uVar7 << 0x1a) >> 0x1f,
                       (uVar7 << 0x19) >> 0x1f);
              }
            }
            else if (local_81 == '\x02') {
              uVar7 = (uint)*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3);
              if (((*(byte *)(param_1 + uVar13 * 0x530 + 0x28bc3) & 0x40) == 0) && (-1 < DebugLevel)
                 ) {
                printk("%s: invalid Measure Mode. %d, Peer STA Support(PASS:%d, ACT:%d, TAB:%d)!\n",
                       "Set_BeaconReq_Proc",2,(uVar7 << 0x1b) >> 0x1f,(uVar7 << 0x1a) >> 0x1f,
                       uVar7 & 0x40);
              }
            }
            else if (-1 < DebugLevel) {
              printk("%s: invalid Measure Mode. %d\n","Set_BeaconReq_Proc");
            }
            if (local_82 == -1) {
              local_80 = local_80 | 3;
            }
            else {
              local_80 = local_80 & 0xfd | 1;
            }
            local_34 = bcn_rand_int;
            RRM_EnqueueBcnReq(param_1,uVar13,uVar14 & 0xff,&local_98);
            uVar6 = 1;
          }
        }
        else {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: invalid wcid\n","Set_BeaconReq_Proc");
          uVar6 = 0;
        }
      }
      else if (((DebugLevel < 0) ||
               (printk("%s: invalid args (%d).\n","Set_BeaconReq_Proc",iVar12), DebugLevel < 0)) ||
              (printk(
                     "eg: iwpriv ra0 set BcnReq=<Aid>-<Duration>-<RegulatoryClass>-<BSSID>-<SSID>-<MeasureCh>-<MeasureMode>-<ChRegClass>-<ChReptList>\n"
                     ), DebugLevel < 0)) {
LAB_0021f8bc:
        uVar6 = 1;
      }
      else {
        printk("eg: iwpriv ra0 set BcnReq=1!50!12!FF:FF:FF:FF:FF:FF!WiFi1!255!1!32+1!1#6#36#48\n");
        uVar6 = 1;
      }
      return uVar6;
    }
    switch(iVar12) {
    case 0:
      sVar4 = strlen(pcVar3);
      if (sVar4 == 0x11) {
        iVar5 = rstrtok(pcVar3,&_LC21);
        if (iVar5 != 0) {
          iVar11 = 1;
          AtoH(iVar5,local_b0);
          do {
            iVar5 = rstrtok(0,&_LC21);
            iVar8 = (int)local_b0 + iVar11;
            iVar11 = iVar11 + 1;
            if (iVar5 == 0) break;
            AtoH(iVar5,iVar8);
          } while (iVar11 != 6);
        }
        iVar5 = MacTableLookup(param_1,local_b0);
        if (iVar5 != 0) {
          uVar13 = (uint)*(ushort *)(iVar5 + 0xe0);
        }
      }
      else {
        os_zero_mem(local_b0,8);
        local_b0[0] = simple_strtol(local_b4,0,0x10);
        iVar5 = entrytb_traversal(param_1,traversal_func_find_entry_by_aid,local_b0);
        if (iVar5 == 1) {
          uVar13 = (uint)*(ushort *)(local_ac + 0xe0);
        }
      }
      uVar7 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]);
      if (uVar7 <= uVar13) {
        if (-1 < DebugLevel) {
          printk("%s: unknow sta of wcid(%d)\n","Set_BeaconReq_Proc",uVar13);
        }
        goto LAB_0021f8bc;
      }
      break;
    case 1:
      local_98 = os_str_tol(pcVar3,0,10);
      local_98 = local_98 & 0xff;
      break;
    case 2:
      local_83 = os_str_tol(pcVar3,0,10);
      break;
    case 3:
      sVar4 = strlen(pcVar3);
      if (sVar4 != 0x11) {
        if (-1 < DebugLevel) {
          printk("%s: invalid value BSSID.\n","Set_BeaconReq_Proc");
          return 1;
        }
        goto LAB_0021f8bc;
      }
      pbVar9 = (byte *)rstrtok(pcVar3,&_LC21);
      if (pbVar9 == (byte *)0x0) goto LAB_0021f8bc;
      iVar5 = 0;
      do {
        iVar11 = iVar5 + 1;
        sVar4 = strlen((char *)pbVar9);
        if (sVar4 != 2) {
          return 0;
        }
        if (((&_ctype)[*pbVar9] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[pbVar9[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(pbVar9,auStack_96 + iVar5,1);
        pbVar9 = (byte *)rstrtok(0,&_LC21);
        iVar5 = iVar11;
      } while (pbVar9 != (byte *)0x0);
      if (iVar11 != 6) goto LAB_0021f8bc;
      break;
    case 4:
      local_88 = pcVar3;
      sVar4 = strlen(pcVar3);
      local_84 = (undefined1)sVar4;
      break;
    case 5:
      local_82 = os_str_tol(pcVar3,0,10);
      break;
    case 6:
      local_81 = os_str_tol(pcVar3,0,10);
      break;
    case 7:
      pbVar9 = &local_80;
      while (pcVar3 = strsep(&local_b4,"+"), pcVar3 != (char *)0x0) {
        bVar2 = os_str_tol(pcVar3,0,10);
        pbVar9 = pbVar9 + 1;
        *pbVar9 = bVar2;
      }
      break;
    case 8:
      puVar10 = &uStack_70;
      while (pcVar3 = strsep(&local_b4,"#"), pcVar3 != (char *)0x0) {
        uVar1 = os_str_tol(pcVar3,0,10);
        puVar10 = puVar10 + 1;
        *puVar10 = uVar1;
      }
      break;
    case 9:
      local_32 = os_str_tol(pcVar3,0,10);
      break;
    case 10:
      local_31 = 0;
      while ((pcVar3 = strsep(&local_b4,"#"), pcVar3 != (char *)0x0 && (*pcVar3 != '\0'))) {
        uVar7 = (uint)local_31;
        uVar1 = os_str_tol(pcVar3,0,10);
        local_31 = local_31 + 1;
        *(undefined1 *)((int)&local_30 + uVar7) = uVar1;
      }
      if (local_31 == 0) {
        local_30 = local_30 & 0xffffff00;
        local_31 = 1;
      }
    }
    iVar12 = iVar12 + 1;
  } while( true );
}

