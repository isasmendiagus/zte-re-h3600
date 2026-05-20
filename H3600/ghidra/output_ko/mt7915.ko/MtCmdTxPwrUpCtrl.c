// module: mt7915.ko
// function: MtCmdTxPwrUpCtrl @ 0x150b10
// size: 460 bytes
//

undefined4 MtCmdTxPwrUpCtrl(int param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 auStack_49 [13];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((3 < DebugLevel) &&
     (printk("%s: ucBandIdx: %d, cPwrUpCat: %d\n","MtCmdTxPwrUpCtrl",param_2,param_3),
     3 < DebugLevel)) {
    printk("%s: cPwrUpValue: (%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)\n",
           "MtCmdTxPwrUpCtrl",(int)*param_4,(int)param_4[1],(int)param_4[2],(int)param_4[3],
           (int)param_4[4],(int)param_4[5],(int)param_4[6],(int)param_4[7],(int)param_4[8],
           (int)param_4[9],(int)param_4[10],(int)param_4[0xb]);
  }
  iVar2 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_4c,0x10);
    if (*(char *)(iVar1 + 0x210) == '\0') {
      local_4c = 0xf;
    }
    else {
      local_4c = 0xe;
    }
    local_4b = (undefined1)param_2;
    local_4a = (undefined1)param_3;
    os_move_mem(auStack_49,param_4,0xc);
    local_3c = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_3c));
    local_38 = CONCAT31(local_38._1_3_,8);
    local_38 = CONCAT22(0xffff,(undefined2)local_38);
    AndesInitCmdMsg(iVar2,local_3c,local_38,local_34,local_30,local_2c);
    AndesAppendCmdMsg(iVar2,&local_4c,0x10);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdTxPwrUpCtrl",uVar3);
  }
  return uVar3;
}

