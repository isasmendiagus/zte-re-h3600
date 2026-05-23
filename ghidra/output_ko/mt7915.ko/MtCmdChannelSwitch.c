// module: mt7915.ko
// function: MtCmdChannelSwitch @ 0x1af7ac
// size: 1404 bytes
//

undefined4
MtCmdChannelSwitch(int param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5,
                  uint param_6)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined1 *__dest;
  uint uVar4;
  char cVar5;
  byte bVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined1 local_84;
  undefined1 local_83;
  undefined1 local_82;
  undefined1 local_81;
  byte local_80;
  undefined1 local_7f;
  undefined1 local_7e;
  undefined1 local_7d;
  char local_7a;
  undefined4 local_78;
  undefined1 local_74;
  char local_73;
  char cStack_71;
  char local_70 [53];
  char acStack_3b [7];
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  bVar1 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  local_c = param_2;
  local_8 = param_3;
  local_4 = param_4;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar4 = local_c >> 0x10 & 0xff;
  if (uVar4 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: central channel = 0 is invalid\n","MtCmdChannelSwitch");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if (0 < DebugLevel) {
    uVar11 = local_4 & 0xff;
    uVar7 = local_4 >> 8 & 0xff;
    printk("%s: control_chl = %d,control_ch2=%d, central_chl = %d DBDCIdx= %d, Band= %d\n",
           "MtCmdChannelSwitch",local_c & 0xff,local_c._1_1_,uVar4,uVar11,uVar7);
    if (0 < DebugLevel) {
      uVar4 = local_8 >> 0x10 & 0xff;
      printk("BW = %d,TXStream = %d, RXStream = %d, scan(%d)\n",local_c._3_1_,local_8 & 0xff,
             local_8._1_1_,uVar4,uVar11,uVar7);
      if (((char)param_6 != '\0') && (0 < DebugLevel)) {
        printk("AP BW = %d, AP central_chn = %d\n",(char)param_6,param_6._1_1_,DebugLevel,uVar4,
               uVar11,uVar7);
      }
    }
  }
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    if ((local_4 & 0xff) == 0) {
      bVar1 = "SetPartProfileParameters"[param_1 + 0x1a];
      cVar5 = "SetPartProfileParameters"[param_1 + 0x1b];
    }
    else {
      bVar1 = "rtmp_read_vow_parms_from_file"[param_1];
      cVar5 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
    }
    local_8._0_2_ = CONCAT11(cVar5,bVar1);
  }
  iVar3 = AndesAllocCmdMsg(param_1,0x4c);
  if (iVar3 == 0) {
    uVar10 = 3;
    goto LAB_001afb8c;
  }
  AndesInitCmdMsg(iVar3,0x8ed0000,0x8000f,5000,0,EventExtCmdResult);
  os_zero_mem(&local_84,0x4c);
  local_84 = (undefined1)local_c;
  local_83 = local_c._2_1_;
  local_7d = local_c._1_1_;
  local_81 = (undefined1)local_8;
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    local_80 = local_8._1_1_;
  }
  else if (*(byte *)(iVar2 + 0x6d) == 0) {
    local_80 = 0;
  }
  else {
    bVar6 = 0;
    local_80 = 0;
    do {
      uVar4 = (uint)bVar6;
      bVar6 = bVar6 + 1;
      if (((int)(uint)local_8._1_1_ >> uVar4 & 1U) != 0) {
        local_80 = local_80 + 1;
      }
    } while (bVar6 < *(byte *)(iVar2 + 0x6d));
  }
  uVar4 = local_4 & 0xff;
  uVar7 = (local_c >> 0x18) - 1 & 0xff;
  local_7a = local_4._1_1_;
  local_7e = (undefined1)local_4;
  if (uVar7 < 6) {
    local_82 = (&DAT_0029ecd0)[uVar7];
  }
  else {
    local_82 = 0;
  }
  local_78 = param_5;
  pcVar8 = (char *)((param_6 & 0xff) - 1 & 0xff);
  if (pcVar8 < (char *)0x6) {
    pcVar9 = "CmdEfuseFreeBlockCountCb" + (int)pcVar8;
    local_73 = local_4._1_1_;
  }
  else {
    pcVar9 = pcVar8;
    local_73 = '\0';
  }
  local_7f = 0;
  if (pcVar8 < (char *)0x6) {
    local_73 = pcVar9[0x5ec];
  }
  if (local_8._2_1_ == '\0') {
    if (local_8._3_1_ != '\0') {
      local_7f = 5;
    }
    if (param_6._2_1_ != '\0') {
      local_7f = 0xe;
    }
  }
  else {
    iVar2 = RadarChannelCheck(param_1);
    if (iVar2 != 0) {
      local_7f = 5;
    }
    uVar4 = local_4 & 0xff;
  }
  uVar4 = (uint)*(byte *)(param_1 + uVar4 + 0x794cd8);
  if (uVar4 - 0x5b < 9) {
LAB_001afa7c:
    local_74 = 0;
  }
  else if (uVar4 - 0x3d < 0x1e) {
    local_74 = 1;
  }
  else if (uVar4 - 0x1f < 0x1e) {
    local_74 = 3;
  }
  else if (uVar4 - 0x10 < 0xf) {
    local_74 = 6;
  }
  else if (uVar4 - 10 < 6) {
    local_74 = 9;
  }
  else {
    if (8 < uVar4 - 1) goto LAB_001afa7c;
    local_74 = 0xc;
  }
  if (3 < DebugLevel) {
    printk(" TxPowerDrop = 0x%x, ucTxPath:%u\n",local_74,bVar1);
  }
  pcVar8 = &cStack_71;
  do {
    pcVar8 = pcVar8 + 1;
    *pcVar8 = '?';
  } while (pcVar8 != local_70 + 0x30);
  if (local_4._1_1_ == '\0') {
    if ((local_c & 0xff) < 0xf) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
  }
  else {
    uVar10 = 1;
  }
  if (3 < DebugLevel) {
    printk(" fg5Gband = 0x%x\n",uVar10);
  }
  pcVar8 = local_70;
  do {
    if (3 < DebugLevel) {
      printk("%s: CmdChanSwitch.aucTxPowerSKU[%d]: 0x%x\n","MtCmdChannelSwitch",
             pcVar8 + (-0x14 - (int)&local_84),(int)*pcVar8);
    }
    pcVar8 = pcVar8 + 1;
  } while (pcVar8 != acStack_3b);
  __dest = (undefined1 *)(param_1 + 0x285a2d);
  iVar2 = 0;
  os_move_mem(__dest,local_70,0x31);
  do {
    if (3 < DebugLevel) {
      printk("%s: pAd->TxPowerSKU[%d]: 0x%x\n","MtCmdChannelSwitch",iVar2,*__dest);
    }
    iVar2 = iVar2 + 1;
    __dest = __dest + 1;
  } while (iVar2 != 0x31);
  AndesAppendCmdMsg(iVar3,&local_84,0x4c);
  os_move_mem((void *)(param_1 + (local_4 & 0xff) * 0x14 + 0xa795e8),&local_c,0x14);
  uVar10 = chip_cmd_tx(param_1,iVar3);
LAB_001afb8c:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdChannelSwitch",uVar10);
  }
  return uVar10;
}

