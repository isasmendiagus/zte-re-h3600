// module: mt7915.ko
// function: set_muru_cert_muedca_override @ 0x23e0d0
// size: 272 bytes
//

bool set_muru_cert_muedca_override(undefined4 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  undefined1 local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_31 = param_2 != 0;
  local_30 = 0xcd;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (-1 < DebugLevel) {
    printk("%s: override = %d\n","set_muru_cert_muedca_override",local_31);
  }
  iVar1 = AndesAllocCmdMsg(param_1,5);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesAppendCmdMsg(iVar1,&local_31,1);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_muru_cert_muedca_override",bVar2);
  }
  return bVar2;
}

