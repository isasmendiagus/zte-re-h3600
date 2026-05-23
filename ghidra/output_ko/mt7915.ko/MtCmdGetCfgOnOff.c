// module: mt7915.ko
// function: MtCmdGetCfgOnOff @ 0x1b70e8
// size: 416 bytes
//

undefined4 MtCmdGetCfgOnOff(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  byte local_6c [4];
  undefined4 local_68;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x4c);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (2 < DebugLevel) {
      printk(&_LC0,"MtCmdGetCfgOnOff");
    }
    AndesInitCmdMsg(iVar1,0x3ded0000,0x80007,0,param_4,MtCmdGetCfgStatRsp);
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
      bVar3 = 0;
      if (*(int *)(param_1 + 0xa77bb4) == 1) {
        bVar3 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
      }
    }
    else {
      bVar3 = 1;
    }
    __memzero(local_6c,0x4c);
    switch(param_2) {
    case 0:
      local_6c[1] = 0xc;
      break;
    case 1:
      local_6c[1] = 0xd;
      break;
    case 2:
      local_6c[1] = 0x16;
      break;
    case 3:
      local_6c[1] = 0xe;
    }
    local_6c[0] = bVar3;
    local_68 = param_3;
    AndesAppendCmdMsg(iVar1,local_6c,0x4c);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetCfgOnOff",uVar2);
  }
  return uVar2;
}

