// module: mt7915.ko
// function: muru_parse_cmd_param_muru_manual_config @ 0x23c3b8
// size: 5328 bytes
//

undefined4
muru_parse_cmd_param_muru_manual_config(int param_1,char *param_2,char *param_3,uint *param_4)

{
  bool bVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  short sVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  uint *puVar12;
  int iVar13;
  int iVar14;
  int local_38;
  char *local_2c [2];
  
  local_2c[0] = param_3;
  if (0 < DebugLevel) {
    printk(&_LC39,"muru_parse_cmd_param_muru_manual_config");
  }
  iVar6 = strcmp("global_comm_band",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)((int)param_4 + 0xe) = uVar3;
    if (0 < iVar6) {
      printk("cmd=global_comm_band: %u\n",uVar3);
    }
    uVar10 = 1;
    *param_4 = *param_4 | 4;
  }
  else {
    uVar10 = 0;
  }
  iVar6 = strcmp("global_comm_wmm",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)((int)param_4 + 0xf) = uVar3;
    if (0 < iVar6) {
      printk("cmd=global_comm_wmm: %u\n",uVar3);
    }
    uVar10 = 1;
    *param_4 = *param_4 | 8;
  }
  iVar6 = strcmp("dl_comm_bw",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)(param_4 + 5) = uVar3;
    if (0 < iVar6) {
      printk("cmd=dl_comm_bw: %u\n",uVar3);
    }
    uVar10 = 1;
    param_4[1] = param_4[1] | 1;
  }
  iVar6 = strcmp("dl_comm_user_cnt",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    iVar6 = *(int *)(param_1 + 0x7959b8);
    if (iVar6 == 0) {
      iVar6 = os_str_tol(pcVar7,0,10);
    }
    *param_4 = *param_4 | 3;
    iVar9 = DebugLevel;
    *(char *)((int)param_4 + 0x12) = (char)iVar6;
    *(byte *)(param_4 + 3) = (byte)param_4[3] | 8;
    *(byte *)((int)param_4 + 0xd) = *(byte *)((int)param_4 + 0xd) | 1;
    if (0 < iVar9) {
      printk("cmd=dl_comm_user_cnt: %u\n");
    }
    uVar10 = 1;
    param_4[1] = param_4[1] | 0x10;
  }
  iVar6 = strcmp("dl_user_wlan_idx",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[1];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=dl_user_wlan_idx: set dl_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    bVar2 = *(byte *)((int)param_4 + 0x12);
    if (bVar2 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar4 = os_str_tol(pcVar7,0,10);
        *(undefined2 *)(puVar12 + 9) = uVar4;
        if (0 < DebugLevel) {
          printk("cmd=dl_user_wlan_idx: user %u, value=%u\n",iVar6,uVar4);
        }
        puVar12 = puVar12 + 4;
        bVar1 = iVar6 < (int)(uint)bVar2;
        iVar6 = iVar6 + 1;
      } while (bVar1);
      uVar8 = param_4[1];
    }
    uVar10 = 1;
    param_4[1] = uVar8 | 0x10000;
  }
  iVar6 = strcmp("dl_comm_toneplan",param_2);
  if (iVar6 == 0) {
    if ((param_4[1] & 1) != 0) {
      uVar8 = (byte)param_4[5] - 1 & 0xff;
      if (uVar8 < 3) {
        iVar6 = *(int *)(&DAT_002a3b6c + uVar8 * 4);
        if (0 < iVar6) goto LAB_0023c4b0;
      }
      else {
        iVar6 = 1;
LAB_0023c4b0:
        iVar14 = 0;
        iVar9 = 0;
        uVar8 = 0;
        do {
          pcVar7 = strsep(local_2c,":");
          if (pcVar7 == (char *)0x0) {
            uVar10 = 0;
            iVar6 = DebugLevel;
            goto LAB_0023c700;
          }
          if (iVar14 % 5 == 4) {
            uVar3 = os_str_tol(pcVar7,0,10);
            *(undefined1 *)((int)param_4 + iVar9 + 0x22) = uVar3;
            iVar9 = iVar9 + 1;
            uVar11 = uVar8;
          }
          else {
            if (7 < uVar8) break;
            uVar3 = os_str_tol(pcVar7,0,10);
            uVar11 = uVar8 + 1;
            *(undefined1 *)((int)param_4 + uVar8 + 0x1a) = uVar3;
          }
          iVar14 = iVar14 + 1;
          uVar8 = uVar11;
        } while (iVar14 < iVar6);
      }
      if (0 < DebugLevel) {
        printk("cmd=dl_comm_toneplan: RU1=%u,RU2=%u,RU3=%u,RU4=%u,D26=%u,RU5=%u,RU6=%u,RU7=%u,RU8=%u,U26=%u\n"
               ,*(undefined1 *)((int)param_4 + 0x1a),*(undefined1 *)((int)param_4 + 0x1b),
               (char)param_4[7],*(undefined1 *)((int)param_4 + 0x1d),
               *(undefined1 *)((int)param_4 + 0x22),*(undefined1 *)((int)param_4 + 0x1e),
               *(undefined1 *)((int)param_4 + 0x1f),(char)param_4[8],
               *(undefined1 *)((int)param_4 + 0x21),*(undefined1 *)((int)param_4 + 0x23));
      }
      uVar10 = 1;
      param_4[1] = param_4[1] | 8;
      goto LAB_0023c608;
    }
LAB_0023c900:
    uVar10 = 0;
    if (DebugLevel < 1) {
      return 0;
    }
    printk("cmd=dl_comm_toneplan: set dl_comm_bw before config dl_comm_toneplan\n");
    iVar6 = DebugLevel;
    goto LAB_0023c700;
  }
LAB_0023c608:
  iVar6 = strcmp("dl_user_ack_policy",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[1];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=dl_user_ack_policy: set dl_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    bVar2 = *(byte *)((int)param_4 + 0x12);
    if (bVar2 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)(puVar12 + 0xc) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=dl_user_ack_policy: user %u, value=%u\n",iVar6,uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 4;
      } while (iVar6 != bVar2 + 1);
      uVar8 = param_4[1];
    }
    uVar10 = 1;
    param_4[1] = uVar8 | 0x800000;
  }
  iVar6 = strcmp("dl_user_ru_alloc",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[1];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=dl_user_ru_alloc: set dl_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    bVar2 = *(byte *)((int)param_4 + 0x12);
    if (bVar2 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x26) = uVar3;
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x27) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=dl_user_ru_alloc:[RBN]:[RU alloc]= user %u, RBN=%u, RU alloc idx=%u\n",iVar6,
                 *(undefined1 *)((int)puVar12 + 0x26),uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 4;
      } while (iVar6 != bVar2 + 1);
      uVar8 = param_4[1];
    }
    uVar10 = 1;
    param_4[1] = uVar8 | 0x100000;
  }
  iVar6 = strcmp("ul_comm_user_cnt",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    iVar6 = *(int *)(param_1 + 0x7959b8);
    if (iVar6 == 0) {
      iVar6 = os_str_tol(pcVar7,0,10);
    }
    *param_4 = *param_4 | 3;
    iVar9 = DebugLevel;
    *(char *)(param_4 + 0x49) = (char)iVar6;
    *(byte *)(param_4 + 3) = (byte)param_4[3] | 4;
    *(byte *)((int)param_4 + 0xd) = *(byte *)((int)param_4 + 0xd) | 2;
    if (0 < iVar9) {
      printk("cmd=ul_comm_user_cnt: %u\n");
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x10;
  }
  iVar6 = strcmp("ul_comm_ack_type",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)(param_4 + 0x83) = uVar3;
    if (0 < iVar6) {
      printk("cmd=ul_comm_ack_type: %u\n",uVar3);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x200;
  }
  iVar6 = strcmp("ul_comm_trig_intv",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    if (pcVar7 == (char *)0x0) {
      sVar5 = (short)param_4[0x4a];
    }
    else {
      sVar5 = os_str_tol(pcVar7,0,10);
      *(short *)(param_4 + 0x4a) = sVar5;
    }
    iVar6 = DebugLevel;
    if (sVar5 == 0) {
      uVar10 = 0;
      goto LAB_0023c700;
    }
    if (DebugLevel < 1) {
      uVar10 = 1;
    }
    param_4[2] = param_4[2] | 4;
    if (0 < iVar6) {
      uVar10 = 1;
      printk("cmd=ul_comm_trig_intv: %u\n");
    }
  }
  iVar6 = strcmp("ul_comm_trig_cnt",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    if (pcVar7 != (char *)0x0) {
      uVar4 = os_str_tol(pcVar7,0,10);
      *(undefined2 *)((int)param_4 + 0x126) = uVar4;
    }
    iVar6 = DebugLevel;
    uVar10 = 0;
    if ((short)param_4[0x4a] == 0) goto LAB_0023c700;
    param_4[2] = param_4[2] | 2;
    if (iVar6 < 1) {
      uVar10 = 1;
    }
    else {
      uVar10 = 1;
      printk("cmd=ul_comm_trig_cnt: %u\n",*(undefined2 *)((int)param_4 + 0x126));
    }
  }
  iVar6 = strcmp("ul_comm_trig_type",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)((int)param_4 + 0x125) = uVar3;
    if (0 < iVar6) {
      printk("cmd=ul_comm_trig_type: %u\n",uVar3);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 1;
  }
  iVar6 = strcmp("ul_comm_ta",param_2);
  if (iVar6 == 0) {
    puVar12 = (uint *)((int)param_4 + 0x12e);
    do {
      pcVar7 = strsep(local_2c,":");
      if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
      uVar3 = os_str_tol(pcVar7,0,0x10);
      puVar12 = (uint *)((int)puVar12 + 1);
      *(undefined1 *)puVar12 = uVar3;
    } while (puVar12 != param_4 + 0x4d);
    if (0 < DebugLevel) {
      printk("%s:cmd=comm_ta:%02x:%02x:%02x:%02x:%02x:%02x\n",
             "muru_parse_cmd_param_muru_manual_config",*(undefined1 *)((int)param_4 + 0x12f),
             (char)param_4[0x4c],*(undefined1 *)((int)param_4 + 0x131),
             *(undefined1 *)((int)param_4 + 0x132),*(undefined1 *)((int)param_4 + 0x133),
             (char)param_4[0x4d]);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x2000;
  }
  iVar6 = strcmp("ul_comm_bw",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)((int)param_4 + 0x12a) = uVar3;
    if (0 < iVar6) {
      printk("cmd=ul_comm_bw: %u\n",uVar3);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x20;
  }
  iVar6 = strcmp("ul_comm_gi_ltf",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar3 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined1 *)((int)param_4 + 299) = uVar3;
    if (0 < iVar6) {
      printk("cmd=ul_comm_gi_ltf: %u\n",uVar3);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x40;
  }
  iVar6 = strcmp("ul_comm_length",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar4 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    *(undefined2 *)(param_4 + 0x4b) = uVar4;
    if (0 < iVar6) {
      printk("cmd=ul_comm_length: %u\n",uVar4);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x80;
  }
  iVar6 = strcmp("ul_comm_tf_pad",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    if (*(int *)(param_1 + 0x7959bc) == 0) {
      uVar3 = os_str_tol(pcVar7,0,10);
      *(undefined1 *)((int)param_4 + 0x12e) = uVar3;
    }
    else {
      if (*(int *)(param_1 + 0x7959bc) == 8) {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      *(undefined1 *)((int)param_4 + 0x12e) = uVar3;
    }
    if (0 < DebugLevel) {
      printk("cmd=ul_comm_tf_pad: %u\n",*(undefined1 *)((int)param_4 + 0x12e));
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x100;
  }
  iVar6 = strcmp("ul_comm_rx_hetb_cfg1",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar8 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    param_4[0x81] = uVar8;
    if (0 < iVar6) {
      printk("cmd=ul_comm_rx_hetb_cfg1: %u\n",uVar8);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x400;
  }
  iVar6 = strcmp("ul_comm_rx_hetb_cfg2",param_2);
  if (iVar6 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 == (char *)0x0) goto LAB_0023c700;
    uVar8 = os_str_tol(pcVar7,0,10);
    iVar6 = DebugLevel;
    param_4[0x82] = uVar8;
    if (0 < iVar6) {
      printk("cmd=ul_comm_rx_hetb_cfg2: %u\n",uVar8);
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 0x800;
  }
  iVar6 = strcmp("ul_user_wlan_idx",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_wlan_idx: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4 + 0x50;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar4 = os_str_tol(pcVar7,0,10);
        *(undefined2 *)puVar12 = uVar4;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_wlan_idx: user %u, value=%u\n",iVar6,uVar4);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x10000;
  }
  iVar6 = strcmp("ul_user_cod",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_cod: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)(puVar12 + 0x51) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_cod: user %u, value=%u\n",iVar6,uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x40000;
  }
  iVar6 = strcmp("ul_user_mcs",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_mcs: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x146) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_mcs: user %u, value=%u\n",iVar6,uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x80000;
  }
  iVar6 = strcmp("ul_user_ssAlloc_raru",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_ssAlloc_raru: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x145) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_ssAlloc_raru: user %u, value=%u\n",iVar6,uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x100000;
  }
  iVar6 = strcmp("ul_user_rssi",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_rssi: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x147) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_rssi: user %u, value=%u\n",iVar6,uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x20000;
  }
  iVar6 = strcmp("ul_comm_toneplan",param_2);
  if (iVar6 == 0) {
    if ((param_4[2] & 0x20) == 0) goto LAB_0023c900;
    uVar8 = *(byte *)((int)param_4 + 0x12a) - 1 & 0xff;
    if (uVar8 < 3) {
      iVar6 = *(int *)(&DAT_002a3b78 + uVar8 * 4);
      if (0 < iVar6) goto LAB_0023d314;
    }
    else {
      iVar6 = 1;
LAB_0023d314:
      local_38 = 0;
      iVar14 = 0;
      iVar9 = 0;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        if (iVar14 % 5 == 4) {
          uVar3 = os_str_tol(pcVar7,0,10);
          *(undefined1 *)((int)param_4 + local_38 + 0x13d) = uVar3;
          local_38 = local_38 + 1;
          iVar13 = iVar9;
        }
        else {
          uVar3 = os_str_tol(pcVar7,0,10);
          iVar13 = iVar9 + 1;
          *(undefined1 *)((int)param_4 + iVar9 + 0x135) = uVar3;
        }
        iVar14 = iVar14 + 1;
        iVar9 = iVar13;
      } while (iVar14 < iVar6);
    }
    if (0 < DebugLevel) {
      printk("cmd=ul_comm_toneplan: RU1=%u,RU2=%u,RU3=%u,RU4=%u,D26=%u,RU5=%u,RU6=%u,RU7=%u,RU8=%u,U26=%u\n"
             ,*(undefined1 *)((int)param_4 + 0x135),*(undefined1 *)((int)param_4 + 0x136),
             *(undefined1 *)((int)param_4 + 0x137),(char)param_4[0x4e],
             *(undefined1 *)((int)param_4 + 0x13d),*(undefined1 *)((int)param_4 + 0x139),
             *(undefined1 *)((int)param_4 + 0x13a),*(undefined1 *)((int)param_4 + 0x13b),
             (char)param_4[0x4f],*(undefined1 *)((int)param_4 + 0x13e));
    }
    uVar10 = 1;
    param_4[2] = param_4[2] | 8;
  }
  iVar6 = strcmp("ul_user_ru_alloc",param_2);
  if (iVar6 == 0) {
    uVar8 = param_4[2];
    if ((uVar8 & 0x10) == 0) {
      uVar10 = 0;
      if (DebugLevel < 1) {
        return 0;
      }
      printk("cmd=ul_user_ru_alloc: set ul_comm_user_cnt before user specific config\n");
      iVar6 = DebugLevel;
      goto LAB_0023c700;
    }
    uVar11 = param_4[0x49];
    if ((byte)uVar11 != 0) {
      iVar6 = 1;
      puVar12 = param_4;
      do {
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x142) = uVar3;
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 == (char *)0x0) goto LAB_0023c5d4;
        uVar3 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)((int)puVar12 + 0x143) = uVar3;
        if (0 < DebugLevel) {
          printk("cmd=ul_user_ru_alloc:[RBN]:[RU alloc]= user %u, RBN=%u, RU alloc idx=%u\n",iVar6,
                 *(undefined1 *)((int)puVar12 + 0x142),uVar3);
        }
        iVar6 = iVar6 + 1;
        puVar12 = puVar12 + 3;
      } while (iVar6 != (byte)uVar11 + 1);
      uVar8 = param_4[2];
    }
    uVar10 = 1;
    param_4[2] = uVar8 | 0x200000;
  }
  iVar9 = strcmp("ul_user_rx_nonsf_en_bitmap",param_2);
  iVar6 = DebugLevel;
  if (iVar9 == 0) {
    pcVar7 = strsep(local_2c,":");
    uVar10 = 0;
    iVar6 = DebugLevel;
    if (pcVar7 != (char *)0x0) {
      uVar8 = os_str_tol(pcVar7,0,10);
      iVar6 = DebugLevel;
      param_4[0x80] = uVar8;
      if (0 < iVar6) {
        printk("cmd=ul_user_rx_nonsf_en_bitmap: value=0x%x\n",uVar8);
      }
      iVar6 = DebugLevel;
      uVar10 = 1;
      param_4[2] = param_4[2] | 0x1000;
    }
  }
LAB_0023c700:
  if (3 < iVar6) {
    printk("%s:(status = %d\n","muru_parse_cmd_param_muru_manual_config",uVar10);
  }
  return uVar10;
LAB_0023c5d4:
  uVar10 = 0;
  iVar6 = DebugLevel;
  goto LAB_0023c700;
}

