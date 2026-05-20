// module: mt7915.ko
// function: check_muru_glo @ 0x172cac
// size: 4284 bytes
//

void check_muru_glo(int param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  
  *(undefined4 *)(param_1 + 0x7959c0) = *param_2;
  iVar1 = DebugLevel;
  *(bool *)(param_1 + 0x7959c4) = param_2[1] != 0x164;
  if (iVar1 < 1) {
LAB_00172ce8:
    *(undefined4 *)(param_1 + 0x7959c8) = param_2[2];
    *(bool *)(param_1 + 0x7959cc) = param_2[3] != 0x30;
LAB_00172d00:
    *(undefined4 *)(param_1 + 0x7959d0) = param_2[4];
    *(bool *)(param_1 + 0x7959d4) = param_2[5] != 0x2c;
LAB_00172d18:
    *(undefined4 *)(param_1 + 0x7959d8) = param_2[6];
    *(bool *)(param_1 + 0x7959dc) = param_2[7] != 0xc;
LAB_00172d30:
    *(undefined4 *)(param_1 + 0x7959e0) = param_2[8];
    *(bool *)(param_1 + 0x7959e4) = param_2[9] != 4;
LAB_00172d48:
    *(undefined4 *)(param_1 + 0x7959e8) = param_2[10];
    *(bool *)(param_1 + 0x7959ec) = param_2[0xb] != 0xba0;
LAB_00172d60:
    *(undefined4 *)(param_1 + 0x7959f0) = param_2[0xc];
    *(bool *)(param_1 + 0x7959f4) = param_2[0xd] != 0x18;
LAB_00172d78:
    *(undefined4 *)(param_1 + 0x7959f8) = param_2[0xe];
    *(bool *)(param_1 + 0x7959fc) = param_2[0xf] != 0x8a;
LAB_00172d90:
    *(undefined4 *)(param_1 + 0x795a00) = param_2[0x10];
    *(bool *)(param_1 + 0x795a04) = param_2[0x11] != 0x82e;
LAB_00172dac:
    *(undefined4 *)(param_1 + 0x795a08) = param_2[0x12];
    *(bool *)(param_1 + 0x795a0c) = param_2[0x13] != 0x2cc;
LAB_00172dc4:
    *(undefined4 *)(param_1 + 0x795a10) = param_2[0x14];
    *(bool *)(param_1 + 0x795a14) = param_2[0x15] != 0x2de74;
LAB_00172de4:
    *(undefined4 *)(param_1 + 0x795a18) = param_2[0x16];
    *(bool *)(param_1 + 0x795a1c) = param_2[0x17] != 0x650;
LAB_00172dfc:
    *(undefined4 *)(param_1 + 0x795a20) = param_2[0x18];
    *(bool *)(param_1 + 0x795a24) = param_2[0x19] != 0x58;
LAB_00172e14:
    *(undefined4 *)(param_1 + 0x795a28) = param_2[0x1a];
    bVar2 = param_2[0x1b] != 0x260;
    *(bool *)(param_1 + 0x795a2c) = bVar2;
LAB_00172e2c:
    if (!bVar2) {
LAB_00172e34:
      if ((0 < iVar1) && (printk(&_LC43), iVar1 = DebugLevel, 0 < DebugLevel)) {
        printk("MURU_MAN_CFG_DATA\n");
        goto LAB_00173294;
      }
    }
LAB_00172e3c:
    *(undefined4 *)(param_1 + 0x795a30) = param_2[0x1c];
    *(bool *)(param_1 + 0x795a34) = param_2[0x1d] != 0x210;
LAB_00172e54:
    *(undefined4 *)(param_1 + 0x795a38) = param_2[0x1e];
    *(bool *)(param_1 + 0x795a3c) = param_2[0x1f] != 4;
LAB_00172e6c:
    *(undefined4 *)(param_1 + 0x795a40) = param_2[0x20];
    *(bool *)(param_1 + 0x795a44) = param_2[0x21] != 4;
LAB_00172e84:
    *(undefined4 *)(param_1 + 0x795a48) = param_2[0x22];
    *(bool *)(param_1 + 0x795a4c) = param_2[0x23] != 1;
LAB_00172e9c:
    *(undefined4 *)(param_1 + 0x795a50) = param_2[0x24];
    bVar2 = param_2[0x25] != 1;
    *(bool *)(param_1 + 0x795a54) = bVar2;
LAB_00172eb4:
    if (!bVar2) {
LAB_00172ebc:
      if ((0 < iVar1) && (printk(&_LC43), 0 < DebugLevel)) {
        printk("MURU_MUMIMO_DATA\n");
        goto LAB_00172f78;
      }
    }
LAB_00172ec4:
    *(undefined4 *)(param_1 + 0x795a58) = param_2[0x26];
    *(bool *)(param_1 + 0x795a5c) = param_2[0x27] != 0x10;
LAB_00172edc:
    *(undefined4 *)(param_1 + 0x795a60) = param_2[0x28];
    *(bool *)(param_1 + 0x795a64) = param_2[0x29] != 0x9f8;
LAB_00172ef8:
    *(undefined4 *)(param_1 + 0x795a68) = param_2[0x2a];
    *(bool *)(param_1 + 0x795a6c) = param_2[0x2b] != 0x18;
  }
  else {
    printk("MURU_LOCAL_DATA_T");
    if (*(char *)(param_1 + 0x7959c4) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172ce8;
      printk("Drive Size = %d, FW Size = %d",0x164,param_2[1]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172ce8;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959c8) = param_2[2];
    *(bool *)(param_1 + 0x7959cc) = param_2[3] != 0x30;
    if (iVar1 < 1) goto LAB_00172d00;
    printk("|-MURU_PARA_T");
    if (*(char *)(param_1 + 0x7959cc) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d00;
      printk("Drive Size = %d, FW Size = %d",0x30,param_2[3]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d00;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959d0) = param_2[4];
    *(bool *)(param_1 + 0x7959d4) = param_2[5] != 0x2c;
    if (iVar1 < 1) goto LAB_00172d18;
    printk("|-MURU_QLEN_INFO_T");
    if (*(char *)(param_1 + 0x7959d4) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d18;
      printk("Drive Size = %d, FW Size = %d",0x2c,param_2[5]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d18;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959d8) = param_2[6];
    *(bool *)(param_1 + 0x7959dc) = param_2[7] != 0xc;
    if (iVar1 < 1) goto LAB_00172d30;
    printk("|-CMD_MURU_BSRP_CTRL");
    if (*(char *)(param_1 + 0x7959dc) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d30;
      printk("Drive Size = %d, FW Size = %d",0xc,param_2[7]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d30;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959e0) = param_2[8];
    *(bool *)(param_1 + 0x7959e4) = param_2[9] != 4;
    if (iVar1 < 1) goto LAB_00172d48;
    printk("|-MURU_TXCMD_CTRL_T");
    if (*(char *)(param_1 + 0x7959e4) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC48), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d48;
      printk("Drive Size = %d, FW Size = %d",4,param_2[9]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d48;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959e8) = param_2[10];
    *(bool *)(param_1 + 0x7959ec) = param_2[0xb] != 0xba0;
    if (iVar1 < 1) goto LAB_00172d60;
    printk("MURU_TX_INFO_T");
    if (*(char *)(param_1 + 0x7959ec) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d60;
      printk("Drive Size = %d, FW Size = %d",0xba0,param_2[0xb]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d60;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959f0) = param_2[0xc];
    *(bool *)(param_1 + 0x7959f4) = param_2[0xd] != 0x18;
    if (iVar1 < 1) goto LAB_00172d78;
    printk("|-MURU_GLOBAL_INFO_T");
    if (*(char *)(param_1 + 0x7959f4) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d78;
      printk("Drive Size = %d, FW Size = %d",0x18,param_2[0xd]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d78;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x7959f8) = param_2[0xe];
    *(bool *)(param_1 + 0x7959fc) = param_2[0xf] != 0x8a;
    if (iVar1 < 1) goto LAB_00172d90;
    printk("|-MURU_PROTECT_INFO_T");
    if (*(char *)(param_1 + 0x7959fc) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172d90;
      printk("Drive Size = %d, FW Size = %d",0x8a,param_2[0xf]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172d90;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a00) = param_2[0x10];
    *(bool *)(param_1 + 0x795a04) = param_2[0x11] != 0x82e;
    if (iVar1 < 1) goto LAB_00172dac;
    printk("|-MURU_TX_DATA_T");
    if (*(char *)(param_1 + 0x795a04) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172dac;
      printk("Drive Size = %d, FW Size = %d",0x82e,param_2[0x11]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172dac;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a08) = param_2[0x12];
    *(bool *)(param_1 + 0x795a0c) = param_2[0x13] != 0x2cc;
    if (iVar1 < 1) goto LAB_00172dc4;
    printk("|-MURU_TX_TRIG_DATA_T");
    if (*(char *)(param_1 + 0x795a0c) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172dc4;
      printk("Drive Size = %d, FW Size = %d",0x2cc,param_2[0x13]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172dc4;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a10) = param_2[0x14];
    *(bool *)(param_1 + 0x795a14) = param_2[0x15] != 0x2de74;
    if (iVar1 < 1) goto LAB_00172de4;
    printk("MURU_SHARE_DATA_T");
    if (*(char *)(param_1 + 0x795a14) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172de4;
      printk("Drive Size = %d, FW Size = %d",0x2de74,param_2[0x15]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172de4;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a18) = param_2[0x16];
    *(bool *)(param_1 + 0x795a1c) = param_2[0x17] != 0x650;
    if (iVar1 < 1) goto LAB_00172dfc;
    printk("|-MURU_ALLOC_DATA_INFO_T");
    if (*(char *)(param_1 + 0x795a1c) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172dfc;
      printk("Drive Size = %d, FW Size = %d",0x650,param_2[0x17]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172dfc;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a20) = param_2[0x18];
    *(bool *)(param_1 + 0x795a24) = param_2[0x19] != 0x58;
    if (iVar1 < 1) goto LAB_00172e14;
    printk("|-PER_USER_INFO");
    if (*(char *)(param_1 + 0x795a24) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172e14;
      printk("Drive Size = %d, FW Size = %d",0x58,param_2[0x19]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172e14;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a28) = param_2[0x1a];
    bVar2 = param_2[0x1b] != 0x260;
    *(bool *)(param_1 + 0x795a2c) = bVar2;
    if (iVar1 < 1) goto LAB_00172e2c;
    printk("|-STA_MURU_RECORD_T");
    iVar1 = DebugLevel;
    if (*(char *)(param_1 + 0x795a2c) == '\0') goto LAB_00172e34;
    if (DebugLevel < 1) goto LAB_00172e3c;
    printk(&_LC40);
    if (0 < DebugLevel) {
      printk("Drive Size = %d, FW Size = %d",0x260,param_2[0x1b]);
      iVar1 = DebugLevel;
      goto LAB_00172e34;
    }
LAB_00173294:
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a30) = param_2[0x1c];
    *(bool *)(param_1 + 0x795a34) = param_2[0x1d] != 0x210;
    if (iVar1 < 1) goto LAB_00172e54;
    printk("|-CMD_MURU_MANCFG_INTERFACER");
    if (*(char *)(param_1 + 0x795a34) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172e54;
      printk("Drive Size = %d, FW Size = %d",0x210,param_2[0x1d]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172e54;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a38) = param_2[0x1e];
    *(bool *)(param_1 + 0x795a3c) = param_2[0x1f] != 4;
    if (iVar1 < 1) goto LAB_00172e6c;
    printk("|-rMuTxPktCnt");
    if (*(char *)(param_1 + 0x795a3c) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172e6c;
      printk("Drive Size = %d, FW Size = %d",4,param_2[0x1f]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172e6c;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a40) = param_2[0x20];
    *(bool *)(param_1 + 0x795a44) = param_2[0x21] != 4;
    if (iVar1 < 1) goto LAB_00172e84;
    printk("|-rMuTxPktCntDwn");
    if (*(char *)(param_1 + 0x795a44) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172e84;
      printk("Drive Size = %d, FW Size = %d",4,param_2[0x21]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172e84;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a48) = param_2[0x22];
    *(bool *)(param_1 + 0x795a4c) = param_2[0x23] != 1;
    if (iVar1 < 1) goto LAB_00172e9c;
    printk("|-rAggPolicy");
    if (*(char *)(param_1 + 0x795a4c) != '\0') {
      iVar1 = DebugLevel;
      if ((DebugLevel < 1) || (printk(&_LC40), iVar1 = DebugLevel, DebugLevel < 1))
      goto LAB_00172e9c;
      printk("Drive Size = %d, FW Size = %d",1,param_2[0x23]);
    }
    iVar1 = DebugLevel;
    if (DebugLevel < 1) goto LAB_00172e9c;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a50) = param_2[0x24];
    bVar2 = param_2[0x25] != 1;
    *(bool *)(param_1 + 0x795a54) = bVar2;
    if (iVar1 < 1) goto LAB_00172eb4;
    printk("|-rDurationComp");
    iVar1 = DebugLevel;
    if (*(char *)(param_1 + 0x795a54) == '\0') goto LAB_00172ebc;
    if (DebugLevel < 1) goto LAB_00172ec4;
    printk(&_LC40);
    if (0 < DebugLevel) {
      printk("Drive Size = %d, FW Size = %d",1,param_2[0x25]);
      iVar1 = DebugLevel;
      goto LAB_00172ebc;
    }
LAB_00172f78:
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a58) = param_2[0x26];
    *(bool *)(param_1 + 0x795a5c) = param_2[0x27] != 0x10;
    if (iVar1 < 1) goto LAB_00172edc;
    printk("|-MURU_MUM_GROUP_TBL_ENTRY");
    if (*(char *)(param_1 + 0x795a5c) != '\0') {
      if ((DebugLevel < 1) || (printk(&_LC40), DebugLevel < 1)) goto LAB_00172edc;
      printk("Drive Size = %d, FW Size = %d",0x10,param_2[0x27]);
    }
    if (DebugLevel < 1) goto LAB_00172edc;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a60) = param_2[0x28];
    *(bool *)(param_1 + 0x795a64) = param_2[0x29] != 0x9f8;
    if (iVar1 < 1) goto LAB_00172ef8;
    printk("|-MURU_MU_ALGORITHM_MONITOR");
    if (*(char *)(param_1 + 0x795a64) != '\0') {
      if ((DebugLevel < 1) || (printk(&_LC40), DebugLevel < 1)) goto LAB_00172ef8;
      printk("Drive Size = %d, FW Size = %d",0x9f8,param_2[0x29]);
    }
    if (DebugLevel < 1) goto LAB_00172ef8;
    printk(&_LC43);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x795a68) = param_2[0x2a];
    *(bool *)(param_1 + 0x795a6c) = param_2[0x2b] != 0x18;
    if (0 < iVar1) {
      printk("|-MURU_STACAP_INFO");
      if (*(char *)(param_1 + 0x795a6c) != '\0') {
        if ((DebugLevel < 1) || (printk(&_LC40), DebugLevel < 1)) goto LAB_00172f10;
        printk("Drive Size = %d, FW Size = %d",0x18,param_2[0x2b]);
      }
      if (0 < DebugLevel) {
        printk(&_LC43);
        iVar1 = DebugLevel;
        *(undefined4 *)(param_1 + 0x795a70) = param_2[0x2c];
        *(bool *)(param_1 + 0x795a74) = param_2[0x2d] != 0x180;
        if (0 < iVar1) {
          printk("|-MURU_TXSTAT_INFO");
          if (*(char *)(param_1 + 0x795a74) != '\0') {
            if (DebugLevel < 1) {
              *(undefined4 *)(param_1 + 0x795a78) = param_2[0x2e];
              *(bool *)(param_1 + 0x795a7c) = param_2[0x2f] != 0x1e;
              return;
            }
            printk(&_LC40);
            if (DebugLevel < 1) goto LAB_00172f28;
            printk("Drive Size = %d, FW Size = %d",0x180,param_2[0x2d]);
          }
          if (0 < DebugLevel) {
            printk(&_LC43);
            iVar1 = DebugLevel;
            *(undefined4 *)(param_1 + 0x795a78) = param_2[0x2e];
            *(bool *)(param_1 + 0x795a7c) = param_2[0x2f] != 0x1e;
            if (iVar1 < 1) {
              return;
            }
            printk("|-MURU_TXSTAT_INFO");
            if (*(char *)(param_1 + 0x795a7c) != '\0') {
              if (DebugLevel < 1) {
                return;
              }
              printk(&_LC40);
              if (DebugLevel < 1) {
                return;
              }
              printk("Drive Size = %d, FW Size = %d",0x1e,param_2[0x2f]);
            }
            if (DebugLevel < 1) {
              return;
            }
            printk(&_LC43);
            return;
          }
        }
        goto LAB_00172f28;
      }
    }
  }
LAB_00172f10:
  *(undefined4 *)(param_1 + 0x795a70) = param_2[0x2c];
  *(bool *)(param_1 + 0x795a74) = param_2[0x2d] != 0x180;
LAB_00172f28:
  *(undefined4 *)(param_1 + 0x795a78) = param_2[0x2e];
  *(bool *)(param_1 + 0x795a7c) = param_2[0x2f] != 0x1e;
  return;
}

