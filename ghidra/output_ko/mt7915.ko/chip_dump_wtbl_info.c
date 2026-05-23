// module: mt7915.ko
// function: chip_dump_wtbl_info @ 0x190e04
// size: 7972 bytes
//

void chip_dump_wtbl_info(int param_1,uint param_2)

{
  char *pcVar1;
  char *extraout_r1;
  char *extraout_r1_00;
  char *extraout_r1_01;
  char *extraout_r1_02;
  undefined *puVar2;
  undefined *extraout_r1_03;
  undefined *extraout_r1_04;
  char *extraout_r1_05;
  undefined *extraout_r1_06;
  char *extraout_r1_07;
  char *extraout_r1_08;
  char *extraout_r1_09;
  char *extraout_r1_10;
  undefined *extraout_r1_11;
  char *extraout_r1_12;
  char *extraout_r1_13;
  char *extraout_r1_14;
  char *extraout_r1_15;
  char *extraout_r1_16;
  char *extraout_r1_17;
  char *extraout_r1_18;
  char *extraout_r1_19;
  char *extraout_r1_20;
  char *extraout_r1_21;
  char *extraout_r1_22;
  char *extraout_r1_23;
  char *extraout_r1_24;
  char *extraout_r1_25;
  char *extraout_r1_26;
  undefined *extraout_r1_27;
  char *extraout_r1_28;
  char *extraout_r1_29;
  char *extraout_r1_30;
  undefined *extraout_r1_31;
  char *extraout_r1_32;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 local_e8;
  uint local_e4;
  uint local_e0;
  uint local_dc;
  uint local_d8;
  uint local_d4;
  uint local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined1 local_a4;
  undefined1 local_a3;
  undefined1 local_a2;
  byte local_a1;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  memset(&local_a8,0,0x80);
  local_e8 = 0;
  local_e4 = 0;
  local_e0 = 0;
  local_dc = 0;
  local_d8 = 0;
  local_d4 = 0;
  local_d0 = 0;
  local_cc = 0;
  halWtblReadRaw(param_1,param_2,0,0,0x20,&local_a8);
  if ((0 < DebugLevel) && (printk("Dump WTBL info of WLAN_IDX:%d\n",param_2), 0 < DebugLevel)) {
    local_c8 = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4000);
    printk("LMAC WTBL Addr: group:0x%x=0x%x addr: 0x%x\n",0x820d4000,local_c8,
           (param_2 & 0x7f) << 8 | 0x820d8000);
  }
  puVar9 = &local_a8;
  iVar3 = 0;
  do {
    if (0 < DebugLevel) {
      printk("DW%02d: %02x %02x %02x %02x\n",iVar3,*(undefined1 *)((int)puVar9 + 3),
             *(undefined1 *)((int)puVar9 + 2),*(undefined1 *)((int)puVar9 + 1),
             *(undefined1 *)(&local_a8 + iVar3));
    }
    iVar3 = iVar3 + 1;
    puVar9 = puVar9 + 1;
  } while (iVar3 != 0x20);
  uVar10 = 8;
  puVar9 = &local_e8;
  halWtblReadRaw(param_1,param_2,1,0,8,puVar9);
  if (0 < DebugLevel) {
    local_c8 = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c4000);
    printk("UMAC WTBL Addr: group:0x%x=0x%x addr: 0x%x\n",0x820c4000,local_c8,
           (param_2 & 0x7f) << 6 | 0x820c6000);
  }
  puVar5 = &local_e8;
  iVar4 = 0;
  iVar3 = DebugLevel;
  do {
    if (0 < iVar3) {
      uVar10 = (uint)*(byte *)((int)puVar5 + 1);
      puVar9 = (undefined4 *)(uint)*(byte *)(&local_e8 + iVar4);
      printk("DW%02d: %02x %02x %02x %02x\n",iVar4,*(undefined1 *)((int)puVar5 + 3),
             *(undefined1 *)((int)puVar5 + 2),uVar10,puVar9);
      iVar3 = DebugLevel;
    }
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar4 != 8);
  if (0 < iVar3) {
    uVar10 = (uint)local_a1;
    puVar9 = (undefined4 *)(local_a8 & 0xff);
    printk("\n\tAddr: %02x:%02x:%02x:%02x:%02x:%02x(D0[B0~15], D1[B0~31])\n",local_a4,local_a3,
           local_a2,uVar10,puVar9,local_a8 >> 8 & 0xff);
    iVar3 = DebugLevel;
    if (0 < DebugLevel) {
      printk("\nLWTBL DW 0/1\n\t");
      iVar3 = DebugLevel;
    }
  }
  uVar6 = 0;
  pcVar1 = "MUAR_IDX";
  do {
    if ((&DAT_0029c840)[uVar6 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_00190f34;
      printk("%s:%d",pcVar1,(local_a8 & (&DAT_0029c83c)[uVar6 * 4]) != 0,(&DAT_0029c83c)[uVar6 * 4],
             uVar10,puVar9);
      pcVar1 = extraout_r1;
LAB_00191594:
      iVar3 = DebugLevel;
      if ((&DAT_0029c844)[uVar6 * 0x10] == '\0') goto LAB_00190f44;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",pcVar1,
               ((&DAT_0029c83c)[uVar6 * 4] & local_a8) >> ((&DAT_0029c840)[uVar6 * 4] & 0xff),
               (&DAT_0029c83c)[uVar6 * 4] & local_a8,uVar10,puVar9);
        pcVar1 = extraout_r1_08;
        goto LAB_00191594;
      }
LAB_00190f34:
      if ((&DAT_0029c844)[uVar6 * 0x10] == '\0') {
LAB_00190f44:
        if (0 < iVar3) {
          printk(&_LC406,pcVar1);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar6 = uVar6 + 1 & 0xffff;
    pcVar1 = *(char **)(&UNK_0029c838 + uVar6 * 0x10);
  } while (pcVar1 != (char *)0x0);
  uVar6 = local_a0;
  if (0 < iVar3) {
    printk("\nLWTBL DW 2\n\t");
    iVar3 = DebugLevel;
    uVar6 = local_a0;
  }
  uVar7 = 0;
  pcVar1 = "AID12";
  do {
    if ((&DAT_0029c8e0)[uVar7 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_00190fd4;
      printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029c8dc)[uVar7 * 4]) != 0);
      pcVar1 = extraout_r1_00;
LAB_0019166c:
      iVar3 = DebugLevel;
      if ((&DAT_0029c8e4)[uVar7 * 0x10] == '\0') goto LAB_00190fe4;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",pcVar1,
               ((&DAT_0029c8dc)[uVar7 * 4] & uVar6) >> ((&DAT_0029c8e0)[uVar7 * 4] & 0xff));
        pcVar1 = extraout_r1_10;
        goto LAB_0019166c;
      }
LAB_00190fd4:
      if ((&DAT_0029c8e4)[uVar7 * 0x10] == '\0') {
LAB_00190fe4:
        if (0 < iVar3) {
          printk(&_LC406,pcVar1);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar7 = uVar7 + 1 & 0xffff;
    pcVar1 = *(char **)(&UNK_0029c8d8 + uVar7 * 0x10);
  } while (pcVar1 != (char *)0x0);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x10] == '\0')) {
    uVar6 = local_9c;
    if (0 < iVar3) {
      printk("\nLWTBL DW 3\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_9c;
    }
    uVar7 = 0;
    pcVar1 = "WMM_Q";
    do {
      if ((&DAT_0029c9e0)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_001913d0;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029c9dc)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_05;
LAB_0019143c:
        iVar3 = DebugLevel;
        if ((&DAT_0029c9e4)[uVar7 * 0x10] == '\0') goto LAB_001913e0;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029c9dc)[uVar7 * 4] & uVar6) >> ((&DAT_0029c9e0)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_32;
          goto LAB_0019143c;
        }
LAB_001913d0:
        if ((&DAT_0029c9e4)[uVar7 * 0x10] == '\0') {
LAB_001913e0:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029c9d8 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
  }
  else {
    uVar6 = local_9c;
    if (0 < iVar3) {
      printk("\nLWTBL DW 3\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_9c;
    }
    uVar7 = 0;
    pcVar1 = "WMM_Q";
    do {
      if ((&DAT_0029ca70)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00191090;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029ca6c)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_01;
LAB_00191610:
        iVar3 = DebugLevel;
        if ((&DAT_0029ca74)[uVar7 * 0x10] == '\0') goto LAB_001910a0;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029ca6c)[uVar7 * 4] & uVar6) >> ((&DAT_0029ca70)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_09;
          goto LAB_00191610;
        }
LAB_00191090:
        if ((&DAT_0029ca74)[uVar7 * 0x10] == '\0') {
LAB_001910a0:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029ca68 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
  }
  uVar6 = local_98;
  if (0 < iVar3) {
    printk("\nLWTBL DW 4\n\t");
    iVar3 = DebugLevel;
    uVar6 = local_98;
  }
  uVar7 = 0;
  pcVar1 = "ANT_ID_STS0";
  do {
    if ((&DAT_0029cb50)[uVar7 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_00191130;
      printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029cb4c)[uVar7 * 4]) != 0);
      pcVar1 = extraout_r1_02;
LAB_00191510:
      iVar3 = DebugLevel;
      if ((&DAT_0029cb54)[uVar7 * 0x10] == '\0') goto LAB_00191140;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",pcVar1,
               ((&DAT_0029cb4c)[uVar7 * 4] & uVar6) >> ((&DAT_0029cb50)[uVar7 * 4] & 0xff));
        pcVar1 = extraout_r1_07;
        goto LAB_00191510;
      }
LAB_00191130:
      if ((&DAT_0029cb54)[uVar7 * 0x10] == '\0') {
LAB_00191140:
        if (0 < iVar3) {
          printk(&_LC406,pcVar1);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar7 = uVar7 + 1 & 0xffff;
    pcVar1 = *(char **)(&UNK_0029cb48 + uVar7 * 0x10);
  } while (pcVar1 != (char *)0x0);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x10] == '\0')) {
    uVar6 = local_94;
    if (0 < iVar3) {
      printk("\nLWTBL DW 5\n\t");
      uVar6 = local_94;
      iVar3 = DebugLevel;
    }
    uVar7 = 0;
    puVar2 = &_LC386;
    do {
      if ((&DAT_0029cc60)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_001912f8;
        printk("%s:%d",puVar2,(uVar6 & (&DAT_0029cc5c)[uVar7 * 4]) != 0);
        puVar2 = extraout_r1_04;
LAB_00191364:
        iVar3 = DebugLevel;
        if ((&DAT_0029cc64)[uVar7 * 0x10] == '\0') goto LAB_00191308;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",puVar2,
                 ((&DAT_0029cc5c)[uVar7 * 4] & uVar6) >> ((&DAT_0029cc60)[uVar7 * 4] & 0xff));
          puVar2 = extraout_r1_31;
          goto LAB_00191364;
        }
LAB_001912f8:
        if ((&DAT_0029cc64)[uVar7 * 0x10] == '\0') {
LAB_00191308:
          if (0 < iVar3) {
            printk(&_LC406,puVar2);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      puVar2 = *(undefined **)(&UNK_0029cc58 + uVar7 * 0x10);
    } while (puVar2 != (undefined *)0x0);
  }
  else {
    uVar6 = local_94;
    if (0 < iVar3) {
      printk("\nLWTBL DW 5\n\t");
      uVar6 = local_94;
      iVar3 = DebugLevel;
    }
    uVar7 = 0;
    puVar2 = &_LC386;
    do {
      if ((&DAT_0029cda0)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_001911e8;
        printk("%s:%d",puVar2,(uVar6 & (&DAT_0029cd9c)[uVar7 * 4]) != 0);
        puVar2 = extraout_r1_03;
LAB_001914c8:
        iVar3 = DebugLevel;
        if ((&DAT_0029cda4)[uVar7 * 0x10] == '\0') goto LAB_001911f8;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",puVar2,
                 ((&DAT_0029cd9c)[uVar7 * 4] & uVar6) >> ((&DAT_0029cda0)[uVar7 * 4] & 0xff));
          puVar2 = extraout_r1_06;
          goto LAB_001914c8;
        }
LAB_001911e8:
        if ((&DAT_0029cda4)[uVar7 * 0x10] == '\0') {
LAB_001911f8:
          if (0 < iVar3) {
            printk(&_LC406,puVar2);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      puVar2 = *(undefined **)(&UNK_0029cd98 + uVar7 * 0x10);
    } while (puVar2 != (undefined *)0x0);
  }
  uVar6 = local_90;
  if ((0 < iVar3) &&
     (printk("\nLWTBL DW 6\n"), uVar6 = local_90, iVar3 = DebugLevel, 0 < DebugLevel)) {
    printk("\tTID 0/1/2/3/4/5/6/7 BA_WIN_SIZE:");
    iVar3 = DebugLevel;
  }
  uVar7 = 0;
  do {
    if (0 < iVar3) {
      uVar8 = 1 << (uVar7 + 3 & 0xff);
      printk(&_LC413,(-(1 << (uVar7 & 0xff)) & uVar6 & (uVar8 - 1 | uVar8)) >> (uVar7 & 0xff));
      iVar3 = DebugLevel;
    }
    uVar7 = uVar7 + 4;
  } while (uVar7 != 0x1c);
  if ((0 < iVar3) && (printk(&_LC414,uVar6 >> 0x1c), iVar3 = DebugLevel, 0 < DebugLevel)) {
    printk("\nLWTBL DW 7\n\t");
    iVar3 = DebugLevel;
  }
  uVar6 = 0;
  puVar2 = &_LC387;
  do {
    if ((&DAT_0029ced0)[uVar6 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_001917bc;
      printk("%s:%d",puVar2,(local_8c & (&DAT_0029cecc)[uVar6 * 4]) != 0);
      puVar2 = extraout_r1_11;
LAB_00191828:
      iVar3 = DebugLevel;
      if ((&DAT_0029ced4)[uVar6 * 0x10] == '\0') goto LAB_001917cc;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",puVar2,
               ((&DAT_0029cecc)[uVar6 * 4] & local_8c) >> ((&DAT_0029ced0)[uVar6 * 4] & 0xff));
        puVar2 = extraout_r1_27;
        goto LAB_00191828;
      }
LAB_001917bc:
      if ((&DAT_0029ced4)[uVar6 * 0x10] == '\0') {
LAB_001917cc:
        if (0 < iVar3) {
          printk(&_LC406,puVar2);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar6 = uVar6 + 1 & 0xffff;
    puVar2 = *(undefined **)(&UNK_0029cec8 + uVar6 * 0x10);
  } while (puVar2 != (undefined *)0x0);
  uVar6 = local_88;
  if (0 < iVar3) {
    printk("\nLWTBL DW 8\n\t");
    uVar6 = local_88;
    iVar3 = DebugLevel;
  }
  uVar7 = 0;
  pcVar1 = "FAIL_CNT_AC0";
  do {
    if ((&DAT_0029d000)[uVar7 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_00191888;
      printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029cffc)[uVar7 * 4]) != 0);
      pcVar1 = extraout_r1_12;
LAB_001918f4:
      iVar3 = DebugLevel;
      if ((&DAT_0029d004)[uVar7 * 0x10] == '\0') goto LAB_00191898;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",pcVar1,
               ((&DAT_0029cffc)[uVar7 * 4] & uVar6) >> ((&DAT_0029d000)[uVar7 * 4] & 0xff));
        pcVar1 = extraout_r1_26;
        goto LAB_001918f4;
      }
LAB_00191888:
      if ((&DAT_0029d004)[uVar7 * 0x10] == '\0') {
LAB_00191898:
        if (0 < iVar3) {
          printk(&_LC406,pcVar1);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar7 = uVar7 + 1 & 0xffff;
    pcVar1 = *(char **)(&UNK_0029cff8 + uVar7 * 0x10);
  } while (pcVar1 != (char *)0x0);
  uVar6 = local_84;
  if (0 < iVar3) {
    printk("\nLWTBL DW 9\n\t");
    uVar6 = local_84;
    iVar3 = DebugLevel;
  }
  uVar7 = 0;
  pcVar1 = "RX_AVG_MPDU";
  do {
    if ((&DAT_0029d070)[uVar7 * 4] == 0xffffffff) {
      if (iVar3 < 1) goto LAB_0019195c;
      printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d06c)[uVar7 * 4]) != 0);
      pcVar1 = extraout_r1_13;
LAB_001919c8:
      iVar3 = DebugLevel;
      if ((&DAT_0029d074)[uVar7 * 0x10] == '\0') goto LAB_0019196c;
      if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    else {
      if (0 < iVar3) {
        printk("%s:%u",pcVar1,
               ((&DAT_0029d06c)[uVar7 * 4] & uVar6) >> ((&DAT_0029d070)[uVar7 * 4] & 0xff));
        pcVar1 = extraout_r1_25;
        goto LAB_001919c8;
      }
LAB_0019195c:
      if ((&DAT_0029d074)[uVar7 * 0x10] == '\0') {
LAB_0019196c:
        if (0 < iVar3) {
          printk(&_LC406,pcVar1);
          iVar3 = DebugLevel;
        }
      }
    }
    uVar7 = uVar7 + 1 & 0xffff;
    pcVar1 = *(char **)(&UNK_0029d068 + uVar7 * 0x10);
  } while (pcVar1 != (char *)0x0);
  if ((0 < iVar3) &&
     (printk("FCAP:%s\n",*(undefined4 *)(fcap_name + ((uVar6 << 9) >> 0x1e) * 4)), 0 < DebugLevel))
  {
    printk("\nLWTBL DW 10\n");
  }
  uVar6 = 0;
  do {
    uVar7 = uVar6 + 1 & 0xffff;
    FUN_00189d1c(param_1,uVar6,
                 (local_80 & (&DAT_0029d10c)[uVar6 * 3]) >> ((&DAT_0029d110)[uVar6 * 3] & 0xff) &
                 0xffff);
    uVar6 = uVar7;
  } while (*(int *)(&UNK_0029d108 + uVar7 * 0xc) != 0);
  if (0 < DebugLevel) {
    printk("\nLWTBL DW 11\n");
  }
  uVar6 = 0;
  do {
    uVar7 = uVar6 + 1 & 0xffff;
    FUN_00189d1c(param_1,uVar6 + 2 & 0xffff,
                 (local_7c & (&DAT_0029d130)[uVar6 * 3]) >> ((&DAT_0029d134)[uVar6 * 3] & 0xff) &
                 0xffff);
    uVar6 = uVar7;
  } while (*(int *)(&UNK_0029d12c + uVar7 * 0xc) != 0);
  if (0 < DebugLevel) {
    printk("\nLWTBL DW 12\n");
  }
  uVar6 = 0;
  do {
    uVar7 = uVar6 + 1 & 0xffff;
    FUN_00189d1c(param_1,uVar6 + 4 & 0xffff,
                 (local_78 & (&DAT_0029d154)[uVar6 * 3]) >> ((&DAT_0029d158)[uVar6 * 3] & 0xff) &
                 0xffff);
    uVar6 = uVar7;
  } while (*(int *)(&UNK_0029d150 + uVar7 * 0xc) != 0);
  if (0 < DebugLevel) {
    printk("\nLWTBL DW 13\n");
  }
  uVar6 = 0;
  do {
    uVar7 = uVar6 + 1 & 0xffff;
    FUN_00189d1c(param_1,uVar6 + 6 & 0xffff,
                 (local_74 & (&DAT_0029d178)[uVar6 * 3]) >> ((&DAT_0029d17c)[uVar6 * 3] & 0xff) &
                 0xffff);
    uVar6 = uVar7;
  } while (*(int *)(&UNK_0029d174 + uVar7 * 0xc) != 0);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x10] == '\0')) {
    if (0 < DebugLevel) {
      printk("\nLWTBL DW 28\n\t");
    }
    uVar6 = 0;
    pcVar1 = "USER_RSSI";
    iVar3 = DebugLevel;
    do {
      if ((&DAT_0029d1a0)[uVar6 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_001921a0;
        printk("%s:%d",pcVar1,(local_38 & (&DAT_0029d19c)[uVar6 * 4]) != 0);
        pcVar1 = extraout_r1_18;
LAB_0019220c:
        iVar3 = DebugLevel;
        if ((&DAT_0029d1a4)[uVar6 * 0x10] == '\0') goto LAB_001921b0;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d19c)[uVar6 * 4] & local_38) >> ((&DAT_0029d1a0)[uVar6 * 4] & 0xff));
          pcVar1 = extraout_r1_28;
          goto LAB_0019220c;
        }
LAB_001921a0:
        if ((&DAT_0029d1a4)[uVar6 * 0x10] == '\0') {
LAB_001921b0:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar6 = uVar6 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d198 + uVar6 * 0x10);
    } while (pcVar1 != (char *)0x0);
    uVar6 = local_34;
    if (0 < iVar3) {
      printk("\nLWTBL DW 29\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_34;
    }
    uVar7 = 0;
    pcVar1 = "RCPI 0";
    do {
      if ((&DAT_0029d200)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_0019226c;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d1fc)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_19;
LAB_001922d8:
        iVar3 = DebugLevel;
        if ((&DAT_0029d204)[uVar7 * 0x10] == '\0') goto LAB_0019227c;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d1fc)[uVar7 * 4] & uVar6) >> ((&DAT_0029d200)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_30;
          goto LAB_001922d8;
        }
LAB_0019226c:
        if ((&DAT_0029d204)[uVar7 * 0x10] == '\0') {
LAB_0019227c:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d1f8 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
    uVar6 = local_30;
    if (0 < iVar3) {
      printk("\nLWTBL DW 30\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_30;
    }
    uVar7 = 0;
    pcVar1 = "SNR 0";
    do {
      if ((&DAT_0029d250)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00192338;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d24c)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_20;
LAB_001923a4:
        iVar3 = DebugLevel;
        if ((&DAT_0029d254)[uVar7 * 0x10] == '\0') goto LAB_00192348;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d24c)[uVar7 * 4] & uVar6) >> ((&DAT_0029d250)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_29;
          goto LAB_001923a4;
        }
LAB_00192338:
        if ((&DAT_0029d254)[uVar7 * 0x10] == '\0') {
LAB_00192348:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d248 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
  }
  else {
    if (0 < DebugLevel) {
      printk("\nLWTBL DW 28\n\t");
    }
    uVar6 = 0;
    pcVar1 = "OM_INFO";
    iVar3 = DebugLevel;
    do {
      if ((&DAT_0029d2a0)[uVar6 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00191bdc;
        printk("%s:%d",pcVar1,(local_38 & (&DAT_0029d29c)[uVar6 * 4]) != 0);
        pcVar1 = extraout_r1_14;
LAB_00191c48:
        iVar3 = DebugLevel;
        if ((&DAT_0029d2a4)[uVar6 * 0x10] == '\0') goto LAB_00191bec;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d29c)[uVar6 * 4] & local_38) >> ((&DAT_0029d2a0)[uVar6 * 4] & 0xff));
          pcVar1 = extraout_r1_23;
          goto LAB_00191c48;
        }
LAB_00191bdc:
        if ((&DAT_0029d2a4)[uVar6 * 0x10] == '\0') {
LAB_00191bec:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar6 = uVar6 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d298 + uVar6 * 0x10);
    } while (pcVar1 != (char *)0x0);
    uVar6 = local_34;
    if (0 < iVar3) {
      printk("\nLWTBL DW 29\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_34;
    }
    uVar7 = 0;
    pcVar1 = "USER_RSSI";
    do {
      if ((&DAT_0029d2d0)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00191ca8;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d2cc)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_15;
LAB_00191d14:
        iVar3 = DebugLevel;
        if ((&DAT_0029d2d4)[uVar7 * 0x10] == '\0') goto LAB_00191cb8;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d2cc)[uVar7 * 4] & uVar6) >> ((&DAT_0029d2d0)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_22;
          goto LAB_00191d14;
        }
LAB_00191ca8:
        if ((&DAT_0029d2d4)[uVar7 * 0x10] == '\0') {
LAB_00191cb8:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = (char *)(&DAT_0029d2c8)[uVar7 * 4];
    } while (pcVar1 != (char *)0x0);
    uVar6 = local_30;
    if (0 < iVar3) {
      printk("\nLWTBL DW 30\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_30;
    }
    uVar7 = 0;
    pcVar1 = "RCPI 0";
    do {
      if ((&DAT_0029d330)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00191d74;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d32c)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_16;
LAB_00191de0:
        iVar3 = DebugLevel;
        if ((&DAT_0029d334)[uVar7 * 0x10] == '\0') goto LAB_00191d84;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d32c)[uVar7 * 4] & uVar6) >> ((&DAT_0029d330)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_24;
          goto LAB_00191de0;
        }
LAB_00191d74:
        if ((&DAT_0029d334)[uVar7 * 0x10] == '\0') {
LAB_00191d84:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d328 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
    uVar6 = local_2c;
    if (0 < iVar3) {
      printk("\nLWTBL DW 31\n\t");
      iVar3 = DebugLevel;
      uVar6 = local_2c;
    }
    uVar7 = 0;
    pcVar1 = "RCPI 4";
    do {
      if ((&DAT_0029d380)[uVar7 * 4] == 0xffffffff) {
        if (iVar3 < 1) goto LAB_00191e40;
        printk("%s:%d",pcVar1,(uVar6 & (&DAT_0029d37c)[uVar7 * 4]) != 0);
        pcVar1 = extraout_r1_17;
LAB_00191eac:
        iVar3 = DebugLevel;
        if ((&DAT_0029d384)[uVar7 * 0x10] == '\0') goto LAB_00191e50;
        if (0 < DebugLevel) {
          printk(&_LC405);
          iVar3 = DebugLevel;
        }
      }
      else {
        if (0 < iVar3) {
          printk("%s:%u",pcVar1,
                 ((&DAT_0029d37c)[uVar7 * 4] & uVar6) >> ((&DAT_0029d380)[uVar7 * 4] & 0xff));
          pcVar1 = extraout_r1_21;
          goto LAB_00191eac;
        }
LAB_00191e40:
        if ((&DAT_0029d384)[uVar7 * 0x10] == '\0') {
LAB_00191e50:
          if (0 < iVar3) {
            printk(&_LC406,pcVar1);
            iVar3 = DebugLevel;
          }
        }
      }
      uVar7 = uVar7 + 1 & 0xffff;
      pcVar1 = *(char **)(&UNK_0029d378 + uVar7 * 0x10);
    } while (pcVar1 != (char *)0x0);
  }
  if (0 < iVar3) {
    printk("\nUWTBL PN\n\t");
    iVar3 = DebugLevel;
  }
  uVar6 = local_e8;
  uVar7 = 0;
  puVar2 = &_LC395;
  do {
    if (0 < iVar3) {
      iVar4 = uVar7 * 0x10;
      printk("%s:%u",puVar2,
             (*(uint *)(&UNK_0029d3cc + iVar4) & uVar6) >> (*(uint *)(&UNK_0029d3d0 + iVar4) & 0xff)
            );
      iVar3 = DebugLevel;
      if ((&UNK_0029d3d4)[iVar4] == '\0') {
        if (0 < DebugLevel) {
          printk(&_LC406);
          iVar3 = DebugLevel;
        }
      }
      else if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    uVar8 = local_e4;
    uVar7 = uVar7 + 1 & 0xffff;
    puVar2 = *(undefined **)(&UNK_0029d3c8 + uVar7 * 0x10);
  } while (puVar2 != (undefined *)0x0);
  puVar2 = &_LC396;
  uVar6 = 0;
  do {
    if (0 < iVar3) {
      iVar4 = uVar6 * 0x10;
      printk("%s:%u",puVar2,
             (*(uint *)(&UNK_0029d41c + iVar4) & uVar8) >> (*(uint *)(&UNK_0029d420 + iVar4) & 0xff)
            );
      iVar3 = DebugLevel;
      if ((&UNK_0029d424)[iVar4] == '\0') {
        if (0 < DebugLevel) {
          printk(&_LC406);
          iVar3 = DebugLevel;
        }
      }
      else if (0 < DebugLevel) {
        printk(&_LC405);
        iVar3 = DebugLevel;
      }
    }
    uVar6 = uVar6 + 1 & 0xffff;
    puVar2 = *(undefined **)(&UNK_0029d418 + uVar6 * 0x10);
  } while (puVar2 != (undefined *)0x0);
  if (iVar3 < 1) {
LAB_00191f68:
    if (iVar3 < 1) goto LAB_00191f78;
    printk("\t%s:%u\n","TID1_AC1_SN",(local_e0 << 8) >> 0x14);
    iVar3 = DebugLevel;
    if ((DebugLevel < 1) ||
       (printk("\t%s:%u\n","TID2_AC2_SN",local_e0 >> 0x18 | (local_dc & 0xf) << 8),
       iVar3 = DebugLevel, DebugLevel < 1)) goto LAB_00191f78;
    printk("\t%s:%u\n","TID3_AC3_SN",(local_dc << 0x10) >> 0x14);
    iVar3 = DebugLevel;
    if ((DebugLevel < 1) ||
       (printk("\t%s:%u\n","TID4_SN",(local_dc << 4) >> 0x14), iVar3 = DebugLevel, DebugLevel < 1))
    goto LAB_00191f78;
    printk("\t%s:%u\n","TID5_SN",(local_d8 & 0xff) << 4 | local_dc >> 0x1c);
    iVar3 = DebugLevel;
    if ((DebugLevel < 1) ||
       (printk("\t%s:%u\n","TID6_SN",(local_d8 << 0xc) >> 0x14), iVar3 = DebugLevel, DebugLevel < 1)
       ) goto LAB_00191f78;
    printk("\t%s:%u\n","TID6_SN",local_d8 >> 0x14);
    iVar3 = DebugLevel;
    if ((DebugLevel < 1) ||
       ((((printk("\t%s:%u\n","COM_SN",(local_e4 << 4) >> 0x14), iVar3 = DebugLevel, DebugLevel < 1
          || (printk("\nUWTBL others\n"), uVar6 = local_d4, iVar3 = DebugLevel, DebugLevel < 1)) ||
         (printk("\t%s:%lu/%lu\n","Key Loc 1/2",local_d4 & 0x7ff,(local_d4 << 5) >> 0x15),
         iVar3 = DebugLevel, DebugLevel < 1)) ||
        ((printk("\t%s:%d\n","UWTBL_QOS",(uVar6 << 4) >> 0x1f), iVar3 = DebugLevel, DebugLevel < 1
         || (printk("\t%s:%d\n","UWTBL_HT_VHT_HE",(uVar6 << 3) >> 0x1f), uVar6 = local_d0,
            iVar3 = DebugLevel, DebugLevel < 1)))))) goto LAB_00191f78;
    printk("\t%s:%d\n","HW AMSDU Enable",(local_d0 << 0x16) >> 0x1f);
    uVar7 = uVar6 & 0x3f;
    iVar3 = DebugLevel;
    if (uVar7 != 0) goto LAB_00191f80;
    if (DebugLevel < 1) goto LAB_00191f90;
    printk("\t%s:invalid (WTBL value=0x%x)\n","HW AMSDU Len");
    goto LAB_001920c8;
  }
  printk("\nUWTBL SN\n");
  iVar3 = DebugLevel;
  if (0 < DebugLevel) {
    printk("\t%s:%u\n","TID0_AC0_SN",local_e0 & 0xfff);
    iVar3 = DebugLevel;
    goto LAB_00191f68;
  }
LAB_00191f78:
  uVar7 = local_d0 & 0x3f;
  uVar6 = local_d0;
  if (uVar7 == 0) {
LAB_00191f90:
    uVar8 = (local_d4 << 5) >> 0x15;
    uVar6 = local_d4 & 0xffff;
    uVar7 = local_d4 & 0x7ff;
LAB_00191fc4:
    local_ac = 0;
    local_b0 = 0;
    local_b4 = 0;
    local_b8 = 0;
    local_bc = 0;
    local_c0 = 0;
    local_c4 = 0;
    local_c8 = 0;
    if (uVar7 == 0x7ff) goto LAB_0019202c;
LAB_00191fd0:
    uVar10 = 8;
    puVar9 = &local_c8;
    halWtblReadRaw(param_1,uVar7,2,0,8,&local_c8);
    if (0 < DebugLevel) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c4000);
      printk("KEY WTBL Addr: group:0x%x=0x%x addr: 0x%x\n",0x820c4000,0,
             (uVar6 & 0x7f) << 6 | 0x820c6000);
    }
    iVar4 = 0;
    iVar3 = DebugLevel;
    puVar5 = &local_c8;
    do {
      if (0 < iVar3) {
        uVar10 = (uint)*(byte *)((int)puVar5 + 1);
        puVar9 = (undefined4 *)(uint)*(byte *)(&local_c8 + iVar4);
        printk("DW%02d: %02x %02x %02x %02x\n",iVar4,*(undefined1 *)((int)puVar5 + 3),
               *(undefined1 *)((int)puVar5 + 2),uVar10,puVar9);
        iVar3 = DebugLevel;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 != 8);
  }
  else {
LAB_00191f80:
    if (uVar7 == 1) {
      if (0 < iVar3) {
        printk("\t%s:%d~%d (WTBL value=0x%x)\n","HW AMSDU Len",1,0xff,1);
        uVar10 = uVar7;
        goto LAB_001920c8;
      }
      goto LAB_00191f90;
    }
    if (iVar3 < 1) goto LAB_00191f90;
    iVar3 = (uVar7 + 0xffffff) * 0x100;
    printk("\t%s:%d~%d (WTBL value=0x%x)\n","HW AMSDU Len",iVar3,iVar3 + 0xff,uVar7);
    uVar10 = uVar7;
LAB_001920c8:
    if (DebugLevel < 1) goto LAB_00191f90;
    uVar6 = (uVar6 << 0x17) >> 0x1d;
    printk("\t%s:%lu (WTBL value=0x%lx)\n","HW AMSDU Num",uVar6 + 1,uVar6,uVar10);
    local_c8 = 0;
    uVar8 = (local_d4 << 5) >> 0x15;
    local_c4 = 0;
    uVar6 = local_d4 & 0xffff;
    local_c0 = 0;
    uVar7 = local_d4 & 0x7ff;
    local_bc = 0;
    local_b8 = 0;
    local_b4 = 0;
    local_b0 = 0;
    local_ac = 0;
    if (DebugLevel < 1) goto LAB_00191fc4;
    printk("\n\t%s:%d\n","keyloc0",uVar7,0,uVar10);
    iVar3 = DebugLevel;
    if (uVar7 != 0x7ff) goto LAB_00191fd0;
  }
  if (0 < iVar3) {
    printk("\t%s:%d\n","keyloc1",uVar8,iVar3,uVar10,puVar9);
  }
LAB_0019202c:
  if (uVar8 != 0x7ff) {
    halWtblReadRaw(param_1,uVar8,2,0,8,&local_c8);
    if (0 < DebugLevel) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c4000);
      printk("KEY WTBL Addr: group:0x%x=0x%x addr: 0x%x\n",0x820c4000,0,
             (uVar8 & 0x7f) << 6 | 0x820c6000);
    }
    iVar3 = 0;
    puVar9 = &local_c8;
    do {
      if (0 < DebugLevel) {
        printk("DW%02d: %02x %02x %02x %02x\n",iVar3,*(undefined1 *)((int)puVar9 + 3),
               *(undefined1 *)((int)puVar9 + 2),*(undefined1 *)((int)puVar9 + 1),
               *(undefined1 *)(&local_c8 + iVar3));
      }
      iVar3 = iVar3 + 1;
      puVar9 = puVar9 + 1;
    } while (iVar3 != 8);
  }
  return;
}

