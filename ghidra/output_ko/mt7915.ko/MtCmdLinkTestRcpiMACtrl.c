// module: mt7915.ko
// function: MtCmdLinkTestRcpiMACtrl @ 0x1bdd50
// size: 332 bytes
//

undefined4 MtCmdLinkTestRcpiMACtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_44;
  undefined1 local_43;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (2 < DebugLevel) {
    printk("%s: ucMAParameter = %d\n","MtCmdLinkTestRcpiMACtrl",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 != 0) {
    os_zero_mem(&local_44,4);
    switch(param_2) {
    case 1:
      param_2 = 3;
      break;
    case 4:
      param_2 = 1;
      break;
    case 8:
      param_2 = 0;
    }
    local_40 = CONCAT13(0x78,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,8);
    local_3c = CONCAT22(0xffff,(undefined2)local_3c);
    local_43 = (undefined1)param_2;
    local_44 = 7;
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,local_30);
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdLinkTestRcpiMACtrl",3);
  }
  return 3;
}

