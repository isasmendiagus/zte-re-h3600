// module: mt7915.ko
// function: CmdExtTlvBufferSend @ 0x1c58a8
// size: 220 bytes
//

undefined4
CmdExtTlvBufferSend(undefined4 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_2c;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_2c = CONCAT13(param_2,0xed0000);
    AndesInitCmdMsg(iVar1,local_2c,0x8000f,0,0,CmdExtTlvUpdateRsp);
    AndesAppendCmdMsg(iVar1,param_3,param_4);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtTlvBufferSend",uVar2);
  }
  return uVar2;
}

