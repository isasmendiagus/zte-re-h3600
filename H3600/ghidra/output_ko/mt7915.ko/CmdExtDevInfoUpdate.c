// module: mt7915.ko
// function: CmdExtDevInfoUpdate @ 0x1c6454
// size: 568 bytes
//

undefined4
CmdExtDevInfoUpdate(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4,
                   undefined1 param_5,ushort param_6)

{
  int iVar1;
  undefined4 uVar2;
  uint local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  code *local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (2 < DebugLevel) {
      printk("%s(): Active = %d, OwnMacIdx = %d, band = %d (%02x:%02x:%02x:%02x:%02x:%02x), TLV Num = %d\n"
             ,"CmdExtDevInfoUpdate",param_5,param_2,param_4,*param_3,param_3[1],param_3[2],
             param_3[3],param_3[4],param_3[5],param_6 & 1);
    }
    local_2c = CmdExtDevInfoUpdateRsp;
    local_38 = CONCAT31(local_38._1_3_,0x27);
    local_3c = CONCAT13(0x2a,CONCAT12(0xed,(undefined2)local_3c));
    local_38 = CONCAT22(0x10,(undefined2)local_38);
    AndesInitCmdMsg(iVar1,local_3c,local_38,local_34,local_30,CmdExtDevInfoUpdateRsp);
    local_50 = CONCAT22(param_6,CONCAT11((char)param_4,(char)param_2)) & 0x1ffff;
    local_4c = CONCAT31(local_4c._1_3_,1);
    AndesAppendCmdMsg(iVar1,&local_50,8);
    if ((param_6 & 1) != 0) {
      local_40 = 0;
      local_48 = 0xc0000;
      local_44 = (uint)CONCAT11((char)param_4,param_5);
      os_move_mem((void *)((int)&local_44 + 2),param_3,6);
      if (2 < DebugLevel) {
        printk("%s(CMD_DEVINFO_BASIC_T), OwnMacIdx = %d, ucActive = %d, aucOwnMAC = %02x:%02x:%02x:%02x:%02x:%02x\n"
               ,"CmdExtDevInfoUpdate",param_2,local_44 & 0xff,local_44 >> 0x10 & 0xff,
               local_44 >> 0x18,local_40 & 0xff,local_40 >> 8 & 0xff,local_40 >> 0x10 & 0xff,
               local_40 >> 0x18);
      }
      AndesAppendCmdMsg(iVar1,&local_48,0xc);
    }
    call_fw_cmd_notifieriers(3,param_1,*(undefined4 *)(iVar1 + 0x20));
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtDevInfoUpdate",uVar2);
  }
  return uVar2;
}

