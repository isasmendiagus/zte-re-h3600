// module: mt7915.ko
// function: MtCmdTxContinous @ 0x1aebb0
// size: 380 bytes
//

void MtCmdTxContinous(undefined4 param_1,int param_2,undefined4 param_3,uint param_4,
                     undefined1 param_5,uint param_6,undefined4 param_7,undefined4 param_8,
                     byte param_9,byte param_10)

{
  ushort uVar1;
  uint local_d0;
  uint local_cc;
  undefined4 local_88;
  undefined4 local_7c;
  uint local_78;
  undefined4 local_74;
  undefined1 auStack_70 [76];
  
  os_zero_mem(&local_7c,0x54);
  if (2 < DebugLevel) {
    local_cc = param_6;
    local_d0 = param_4;
    printk("%s, mode:0x%x, bw:0x%x, prich(Control CH):0x%x, mcs:0x%x\n","MtCmdTxContinous",param_2,
           param_3);
    if (2 < DebugLevel) {
      local_d0 = (uint)param_10;
      printk("wfsel:0x%x, TxfdMode:0x%x, Band:0x%xon/off:0x%x\n",param_7,param_8,(uint)param_9);
    }
  }
  if (param_10 == 0) {
    local_7c = 6;
    local_78 = (uint)param_9;
    goto LAB_001aec50;
  }
  local_7c = 5;
  if (param_2 == 0) {
    if (param_6 - 1 < 0xb) {
      uVar1 = (ushort)(byte)(&DAT_0029ebf7)[param_6];
    }
    else {
      uVar1 = 0;
    }
  }
  else if (param_2 == 1) {
    if (7 < param_6) goto LAB_001aecbc;
    uVar1 = (ushort)(byte)(&DAT_0029ec04)[param_6];
  }
  else if (param_2 - 2U < 3) {
    uVar1 = (ushort)(byte)param_6;
  }
  else {
LAB_001aecbc:
    uVar1 = 0;
  }
  local_74 = CONCAT13((undefined1)param_8,CONCAT12(param_9,uVar1 | (ushort)(param_2 << 6)));
  local_78 = CONCAT13((undefined1)param_7,CONCAT12((char)param_3,CONCAT11(param_5,(char)param_4)));
LAB_001aec50:
  local_88 = 8;
  memcpy(&local_d0,auStack_70,0x48);
  FUN_001ac150(param_1,local_7c,local_78,local_74);
  return;
}

