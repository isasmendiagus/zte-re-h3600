// module: mt7915.ko
// function: MtCmdFwLog2Host @ 0x1b0f3c
// size: 324 bytes
//

undefined4 MtCmdFwLog2Host(undefined4 param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  char *pcVar4;
  undefined1 local_4c [4];
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
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (0 < DebugLevel) {
    pcVar4 = "HOST2CR4";
    if (param_2 == 0) {
      pcVar4 = "HOST2N9";
    }
    printk(":%s: McuDest(%d):%s\n","MtCmdFwLog2Host",param_2,pcVar4);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x13,CONCAT12(0xed,(short)param_2));
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    os_zero_mem(local_4c,4);
    local_4c[0] = param_3;
    AndesAppendCmdMsg(iVar1,local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (3 < DebugLevel) {
      puVar3 = &_LC123;
      if (param_2 != 0) {
        puVar3 = &_LC124;
      }
      printk("%s: %s (ret = %d)\n","MtCmdFwLog2Host",puVar3,uVar2);
    }
  }
  return uVar2;
}

