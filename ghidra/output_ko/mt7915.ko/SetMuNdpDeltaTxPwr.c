// module: mt7915.ko
// function: SetMuNdpDeltaTxPwr @ 0x8e2f0
// size: 344 bytes
//

undefined4 SetMuNdpDeltaTxPwr(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  char local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_31 = '\0';
  local_30 = 0x25;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (param_2 == 0) {
    uVar2 = 0;
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: arg is NULL\n","SetMuNdpDeltaTxPwr");
  }
  else {
    local_31 = simple_strtol(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: NdpDeltaTxPwr = %d\n","SetMuNdpDeltaTxPwr",(int)local_31);
    }
    iVar1 = AndesAllocCmdMsg(param_1,5);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      uVar2 = 1;
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_31,1);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetMuNdpDeltaTxPwr",uVar2);
  }
  return uVar2;
}

