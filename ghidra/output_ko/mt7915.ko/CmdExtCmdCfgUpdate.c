// module: mt7915.ko
// function: CmdExtCmdCfgUpdate @ 0x1c7fd8
// size: 512 bytes
//

undefined4 CmdExtCmdCfgUpdate(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_50 [4];
  uint local_4c;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar4 = param_2 & 1;
  if (uVar4 != 0) {
    iVar2 = 0x10;
  }
  else {
    iVar2 = 8;
  }
  uVar3 = (uint)(uVar4 != 0);
  if ((param_2 & 2) != 0) {
    uVar3 = uVar3 + 1;
  }
  local_3c = 0;
  if ((param_2 & 4) != 0) {
    iVar2 = iVar2 + 0xc;
    uVar3 = uVar3 + 1;
  }
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar2 = AndesAllocCmdMsg(param_1,iVar2);
  if (iVar2 == 0) {
    if (DebugLevel < 4) {
      uVar1 = 3;
    }
    else {
      printk("%s:(Ret = %d)\n","CmdExtCmdCfgUpdate",3);
      uVar1 = 3;
    }
  }
  else {
    local_38 = CONCAT31(local_38._1_3_,8);
    local_3c = CONCAT13(0xb7,CONCAT12(0xed,(undefined2)local_3c));
    AndesInitCmdMsg(iVar2,local_3c,local_38,local_34,local_30,local_2c);
    local_4c = uVar3;
    AndesAppendCmdMsg(iVar2,auStack_50,8);
    if (uVar4 != 0) {
      local_48 = 0x80000;
      local_44 = param_4 & 0xff;
      if (0 < DebugLevel) {
        printk("%s: u2Tag=%d ucActive=%d\n","CmdExtCmdCfgUpdate",0,param_4);
      }
      AndesAppendCmdMsg(iVar2,&local_48,8);
    }
    if ((param_2 & 4) != 0) {
      local_40 = 0;
      local_48 = 0xc0002;
      local_44 = CONCAT13((byte)((param_4 << 0x1d) >> 0x1f),
                          CONCAT12((byte)((param_4 << 0x1e) >> 0x1f),
                                   CONCAT11((char)param_4,(char)param_3))) & 0xffff01ff;
      if (0 < DebugLevel) {
        printk("%s: u2Tag=%d ucBand=%d ucAction=%d\n","CmdExtCmdCfgUpdate",2,param_3,param_4);
      }
      AndesAppendCmdMsg(iVar2,&local_48,0xc);
    }
    uVar1 = AndesSendCmdMsg(param_1,iVar2);
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d)\n","CmdExtCmdCfgUpdate",uVar1);
    }
  }
  return uVar1;
}

