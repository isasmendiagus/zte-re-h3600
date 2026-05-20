// module: mt7915.ko
// function: CmdTxBfModuleEnCtrl @ 0x1b423c
// size: 332 bytes
//

undefined4
CmdTxBfModuleEnCtrl(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 auStack_55 [13];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (2 < DebugLevel) {
    printk("%s: u1BfNum = %d, u1BfBitmap = %d, u1BfSelBand[0] = %d, u1BfSelBand[1] = %d\n",
           "CmdTxBfModuleEnCtrl",param_2,param_3,*param_4,param_4[1]);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_57 = (undefined1)param_2;
    local_58 = 0x19;
    local_56 = (undefined1)param_3;
    os_move_mem(auStack_55,param_4,8);
    local_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    AndesAppendCmdMsg(iVar1,&local_58,0x10);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdTxBfModuleEnCtrl",uVar2);
  }
  return uVar2;
}

