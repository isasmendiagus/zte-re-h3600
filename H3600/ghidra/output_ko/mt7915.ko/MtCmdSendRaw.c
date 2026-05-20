// module: mt7915.ko
// function: MtCmdSendRaw @ 0x1b93a4
// size: 244 bytes
//

undefined1
MtCmdSendRaw(undefined4 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
            char param_5)

{
  undefined1 uVar1;
  int iVar2;
  byte bVar3;
  undefined4 local_48;
  undefined4 local_44;
  
  iVar2 = AndesAllocCmdMsg(param_1,param_4);
  if (iVar2 == 0) {
    if (DebugLevel < 0) {
      uVar1 = 3;
    }
    else {
      printk("%s AndesAllocCmdMsg error !!!\n","MtCmdSendRaw");
      uVar1 = 3;
    }
  }
  else {
    if (param_5 == '\0') {
      bVar3 = 5;
    }
    else {
      bVar3 = 0xd;
    }
    local_48 = CONCAT13(param_2,0xed0000);
    local_44 = CONCAT22(0xffff,(ushort)bVar3);
    AndesInitCmdMsg(iVar2,local_48,local_44,0,0,CmdExtEventRsp);
    AndesAppendCmdMsg(iVar2,param_3,param_4);
    uVar1 = chip_cmd_tx(param_1,iVar2);
  }
  return uVar1;
}

