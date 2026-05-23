// module: mt7915.ko
// function: MtCmdSetTxRxPath @ 0x1afd2c
// size: 976 bytes
//

undefined4
MtCmdSetTxRxPath(int param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5,
                undefined4 param_6)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_cc;
  undefined1 local_c8;
  undefined1 local_c0;
  undefined1 local_bc;
  undefined1 local_84;
  char local_83;
  undefined1 local_82;
  undefined1 local_81;
  byte local_80;
  undefined1 local_7f;
  byte local_7e;
  undefined1 local_7d;
  undefined2 local_7c;
  undefined1 local_7a;
  char cStack_a;
  byte local_7;
  char local_5;
  byte local_4;
  
  local_7 = (byte)(param_3 >> 8);
  uVar9 = (uint)local_7;
  local_cc = param_3 & 0xff;
  local_4 = (byte)param_4;
  uVar6 = param_3 >> 0x10 & 0xff;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cStack_a = (char)(param_2 >> 0x10);
  if (cStack_a == '\0') {
    if (DebugLevel < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      printk("%s: central channel = 0 is invalid\n","MtCmdSetTxRxPath");
      uVar3 = 0xffffffff;
    }
  }
  else {
    uVar1 = param_2 >> 0x18;
    if (uVar1 == 3 || uVar1 == 6) {
      local_cc = 4;
      if (uVar9 < 2) {
        uVar8 = 5;
      }
      else {
        uVar8 = 0xf;
      }
    }
    else {
      uVar7 = 0;
      uVar8 = uVar9;
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
        uVar5 = uVar7;
        if (uVar9 != 0) {
          do {
            uVar8 = uVar7 & 0xff;
            uVar7 = uVar7 + 1;
            uVar8 = uVar5 | 1 << uVar8 & 0xffU;
            uVar5 = uVar8;
          } while (uVar9 != uVar7);
        }
      }
      else if (uVar9 != 0) {
        uVar8 = uVar7;
        do {
          uVar5 = uVar8 | 1 << (uVar7 & 0xff);
          if (((*(uint *)(iVar2 + 0x2c) & 0x400000) != 0) ||
             ((uVar5 = uVar8 | 1 << ((short)(ushort)local_4 * 2 + uVar7 & 0xff),
              (*(uint *)(param_1 + 0xa3ac14) & 1) == 0 &&
              ((*(int *)(param_1 + 0xa77bb4) != 1 ||
               ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))))) {
            uVar8 = uVar5 & 0xff;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 != uVar9);
      }
    }
    if (0 < DebugLevel) {
      printk("%s: control_chl = %d,control_ch2=%d, central_chl = %d, BW = %d,TXStream = %d, RXStream = %d,RXPath = %x, BandIdx =%d,  scan(%d), Channel_Band = %d\n"
             ,"MtCmdSetTxRxPath",param_2 & 0xff,param_2 >> 8 & 0xff,cStack_a,uVar1,local_cc,uVar9,
             uVar8,param_4 & 0xff,uVar6,param_4 >> 8 & 0xff);
    }
    iVar2 = AndesAllocCmdMsg(param_1,0x4c);
    if (iVar2 == 0) {
      uVar3 = 3;
    }
    else {
      AndesInitCmdMsg(iVar2,0x4eed0000,0x8000f,0,0,EventExtCmdResult);
      os_zero_mem(&local_84,0x4c);
      local_c8 = (undefined1)param_2;
      local_83 = cStack_a;
      local_84 = local_c8;
      local_c0 = (undefined1)(param_2 >> 8);
      local_81 = (undefined1)local_cc;
      local_7d = local_c0;
      if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
         ((*(int *)(param_1 + 0xa77bb4) != 1 ||
          ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
        local_80 = (byte)uVar8;
      }
      else {
        local_80 = local_7;
      }
      local_7e = local_4;
      uVar9 = uVar1 - 1 & 0xff;
      if (uVar9 < 6) {
        local_82 = (&DAT_0029ecd0)[uVar9];
      }
      else {
        local_82 = 0;
      }
      local_bc = (undefined1)(param_4 >> 8);
      local_7a = local_bc;
      local_7c = 0;
      local_7f = 0;
      if (uVar6 == 0) {
        local_5 = (char)(param_3 >> 0x18);
        if (local_5 != '\0') {
          local_7f = 5;
        }
        if (param_6._2_1_ != '\0') {
          local_7f = 0xe;
        }
      }
      else {
        iVar4 = RadarChannelCheck(param_1,param_2 & 0xff);
        if (iVar4 != 0) {
          local_7f = 5;
        }
      }
      AndesAppendCmdMsg(iVar2,&local_84,0x4c);
      uVar3 = chip_cmd_tx(param_1,iVar2);
    }
    if (3 < DebugLevel) {
      printk("%s:(ret = %d)\n","MtCmdSetTxRxPath",uVar3);
    }
  }
  return uVar3;
}

