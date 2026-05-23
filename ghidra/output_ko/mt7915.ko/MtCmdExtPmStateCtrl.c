// module: mt7915.ko
// function: MtCmdExtPmStateCtrl @ 0x1af544
// size: 576 bytes
//

undefined4
MtCmdExtPmStateCtrl(undefined4 param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5,
                   undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_c;
  uint local_8;
  undefined4 local_4;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_c = param_2;
  local_8 = param_3;
  local_4 = param_4;
  iVar1 = AndesAllocCmdMsg(param_1,0x20);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_44._0_2_ = (ushort)param_6._2_1_;
    local_50._0_2_ = CONCAT11(local_4._1_1_,(undefined1)local_50);
    local_3c = CONCAT31(local_3c._1_3_,(undefined1)param_6);
    local_58._0_2_ = (undefined2)local_c;
    os_move_mem((void *)((int)&local_58 + 2),(void *)((int)&local_c + 2),6);
    if ((local_c & 0xffff) == 0x104) {
      local_4c = param_5;
      local_48 = 0;
      local_50 = CONCAT31(local_50._1_3_,(undefined1)local_4);
      local_50 = CONCAT22(local_4._2_2_,(undefined2)local_50);
      local_3c = (uint)CONCAT12(param_6._1_1_,CONCAT11(param_6._3_1_,(char)local_3c));
      local_40 = 0xf;
    }
    else if ((local_c & 0xffff) == 0x204) {
      local_48 = 0;
      local_40 = 0xf;
    }
    if (2 < DebugLevel) {
      printk("%s::Dbdc(%d),Wcid(%d),OwnMac(%d),BSSID(%02x:%02x:%02x:%02x:%02x:%02x),BcnPrd(%d),DtimPrd(%d),AID(%d),Feature(0x%x)\n"
             ,"MtCmdExtPmStateCtrl",local_44 & 0xff,CONCAT11(local_44._1_1_,local_50._1_1_) & 0x3ff,
             local_3c & 0xff,local_c >> 0x10 & 0xff,local_c >> 0x18,local_8 & 0xff,
             local_8 >> 8 & 0xff,local_8 >> 0x10 & 0xff,local_8 >> 0x18,local_4._2_2_,local_4 & 0xff
             ,param_5,local_40);
    }
    AndesInitCmdMsg(iVar1,0x7ed0000,0x8000f,0,0,CmdExtPmStateCtrlRsp);
    AndesAppendCmdMsg(iVar1,&local_58,0x20);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","MtCmdExtPmStateCtrl",uVar2);
  }
  return uVar2;
}

