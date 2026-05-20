// module: mt7915.ko
// function: MtCmdATETest @ 0x1b69a0
// size: 288 bytes
//

undefined4 MtCmdATETest(undefined4 param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 local_3c;
  
  if (2 < DebugLevel) {
    printk("%s:struct size %lu\n","MtCmdATETest",0x4c);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x4c);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    if (*(char *)(param_2 + 3) == '\x0f') {
      *(undefined1 *)(param_2 + 3) = 0;
      bVar2 = 0xf;
    }
    else {
      bVar2 = 8;
    }
    local_3c = CONCAT22(8,(ushort)bVar2);
    AndesInitCmdMsg(iVar1,0x3ded0000,local_3c,0,0,MtCmdATETestResp);
    AndesAppendCmdMsg(iVar1,param_2,0x4c);
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdATETest",uVar3);
  }
  return uVar3;
}

