// module: mt7915.ko
// function: CmdTxContinous @ 0x1c4c08
// size: 508 bytes
//

undefined4
CmdTxContinous(undefined4 param_1,int param_2,int param_3,undefined4 param_4,uint param_5,
              undefined4 param_6,char param_7)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_78 [4];
  undefined4 local_74;
  char local_70;
  char local_6f;
  undefined1 local_6d;
  ushort local_6c;
  
  memset(local_78,0,0x58);
  if (2 < DebugLevel) {
    printk("%s, mode:0x%x, bw:0x%x, prich(Control CH):0x%x, mcs:0x%x, wfsel:0x%x, on/off:0x%x\n",
           "CmdTxContinous",param_2,param_3,param_4,param_5,param_6,param_7);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x58);
  if (iVar1 == 0) {
    uVar2 = 3;
    goto LAB_001c4d44;
  }
  AndesInitCmdMsg(iVar1,0x4ed0000,0x8000f,0,0,EventExtCmdResult);
  os_zero_mem(local_78,0x58);
  local_78[0] = 1;
  if (param_7 == '\0') {
    local_74 = 6;
  }
  else {
    local_74 = 5;
  }
  local_6f = (char)param_4;
  local_70 = local_6f;
  if (param_3 - 1U < 2) {
    local_70 = local_6f + '\x02';
  }
  local_6d = (undefined1)param_6;
  if (param_2 == 0) {
    local_6c = 0;
    if (param_5 - 1 < 0xb) {
      local_6c = (ushort)(byte)(&DAT_002a016b)[param_5];
    }
  }
  else if (param_2 == 1) {
    if (7 < param_5) goto LAB_001c4d98;
    local_6c = (ushort)(byte)(&DAT_002a0178)[param_5];
  }
  else if (param_2 - 2U < 3) {
    local_6c = (ushort)param_5 & 0xff;
  }
  else {
LAB_001c4d98:
    local_6c = 0;
  }
  local_6c = local_6c | (ushort)(param_5 << 6);
  AndesAppendCmdMsg(iVar1,local_78,0x58);
  uVar2 = AndesSendCmdMsg(param_1,iVar1);
LAB_001c4d44:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdTxContinous",uVar2);
  }
  return uVar2;
}

