// module: mt7915.ko
// function: CmdChPrivilege @ 0x1c45d0
// size: 632 bytes
//

undefined4
CmdChPrivilege(int param_1,undefined1 param_2,uint param_3,uint param_4,char param_5,
              undefined1 param_6,undefined1 param_7)

{
  undefined1 auVar1 [4];
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  uint uVar5;
  undefined4 uVar6;
  bool bVar7;
  bool bVar8;
  uint local_48;
  undefined4 local_44;
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_44 = 0;
  local_40 = (undefined1  [4])0x0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (param_4 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: central channel = 0 is invalid\n","CmdChPrivilege");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if (3 < DebugLevel) {
    printk("%s: control_chl = %d, central_chl = %d, BW = %d, TXStream = %d, RXStream = %d\n",
           "CmdChPrivilege",param_3,param_4,param_5,param_6,param_7);
  }
  iVar2 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar2 == 0) {
    uVar6 = 3;
    goto LAB_001c474c;
  }
  local_34._0_3_ = CONCAT12(0x20,(undefined2)local_34);
  local_30 = CONCAT31(local_30._1_3_,8);
  AndesInitCmdMsg(iVar2,local_34,local_30,local_2c,local_28,local_24);
  os_zero_mem(&local_44,0x10);
  local_44 = CONCAT13((char)param_3,CONCAT12(param_2,(undefined2)local_44));
  if (param_5 == '\0') {
LAB_001c46b4:
    local_40[0] = param_5;
  }
  else if (param_5 == '\x01') {
    if (param_3 < param_4) goto LAB_001c46b4;
    local_40[0] = 3;
  }
  else if (-1 < DebugLevel) {
    printk("unknown bandwidth = %d\n",param_5);
  }
  auVar1 = local_40;
  if (param_4 < 0xf) {
    uVar4 = 1;
  }
  else {
    uVar4 = 2;
  }
  local_40[1] = uVar4;
  local_40[3] = auVar1[3];
  local_40[2] = 0;
  local_3c._0_2_ = (ushort)(byte)local_3c;
  AndesAppendCmdMsg(iVar2,&local_44,0x10);
  uVar5 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar5 == 0x7628 || uVar5 == 0x7603) {
LAB_001c47a0:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5020,&local_48);
    if ((local_48 & 0x400000) != 0) {
      *(undefined1 *)(param_1 + 0xa7851a) = 1;
    }
    if ((local_48 & 0x800000) != 0) {
      *(undefined1 *)(param_1 + 0xa7851b) = 1;
    }
    local_48 = local_48 | 0xc00000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5020,local_48);
  }
  else {
    uVar3 = 0x7606;
    bVar8 = 0x7605 < uVar5;
    bVar7 = uVar5 == 0x7606;
    if (!bVar7) {
      bVar8 = uVar5 != 0x7636;
    }
    if (!bVar8 || (bVar7 || uVar5 == 0x7637)) {
      uVar3 = 1;
    }
    if (bVar8 && (!bVar7 && uVar5 != 0x7637)) {
      uVar3 = 0;
    }
    if (uVar5 == 0x7611) {
      uVar3 = uVar3 | 1;
    }
    if (uVar3 != 0) goto LAB_001c47a0;
  }
  uVar6 = AndesSendCmdMsg(param_1,iVar2);
LAB_001c474c:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdChPrivilege",uVar6);
  }
  return uVar6;
}

