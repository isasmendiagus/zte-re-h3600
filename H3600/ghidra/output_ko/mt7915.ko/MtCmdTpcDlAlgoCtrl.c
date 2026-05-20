// module: mt7915.ko
// function: MtCmdTpcDlAlgoCtrl @ 0x1badbc
// size: 404 bytes
//

undefined4
MtCmdTpcDlAlgoCtrl(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  char param_5,undefined1 param_6,short param_7)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if ((-1 < DebugLevel) &&
     (printk("%s: u1TpcCmd: %d, fgCmdCtrl: %d\n","MtCmdTpcDlAlgoCtrl",param_2,param_3),
     -1 < DebugLevel)) {
    printk("u1DlTxType: %d, DlTxPwr: %d, u1EntryIdx: %d, DlTxpwrAlpha: %d\n",param_4,(int)param_5,
           param_6,(int)param_7);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_60);
    local_50 = CONCAT13(0xa1,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = local_40;
    local_60 = CONCAT13(param_6,CONCAT12((char)param_3,CONCAT11(param_5,(char)param_2 + '\x04')));
    local_5c = CONCAT22(local_5c._2_2_,param_7);
    local_58 = param_4;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,local_40);
    AndesAppendCmdMsg(iVar1,&local_60,0x10);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdTpcDlAlgoCtrl",uVar2);
  }
  return uVar2;
}

