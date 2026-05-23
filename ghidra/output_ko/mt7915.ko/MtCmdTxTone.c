// module: mt7915.ko
// function: MtCmdTxTone @ 0x1aed30
// size: 268 bytes
//

void MtCmdTxTone(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,byte param_5,
                byte param_6,undefined4 param_7,undefined4 param_8,uint param_9)

{
  uint local_d0;
  uint local_cc;
  undefined4 local_88;
  undefined4 local_7c;
  uint local_78;
  undefined4 local_74;
  undefined4 local_70;
  uint local_6c;
  
  os_zero_mem(&local_7c,0x54);
  if (2 < DebugLevel) {
    local_d0 = (uint)param_5;
    local_cc = (uint)param_6;
    printk("%s, Control:%d, AntIndex:%d, ToneType:%d, ToneFreq:%d\n","MtCmdTxTone",param_3,param_4);
    if (2 < DebugLevel) {
      local_d0 = param_9;
      printk("BandIdx:%d, DcOffset_I:%d, DcOffset_Q:%d, Band:%d\n",param_2,param_7,param_8);
    }
  }
  if (param_3 == 0) {
    local_78 = param_9;
    local_7c = 4;
  }
  else {
    local_74 = param_7;
    local_70 = param_8;
    local_78 = CONCAT13((char)param_2,CONCAT12(param_6,CONCAT11(param_5,(char)param_4)));
    local_6c = param_9;
    local_7c = 3;
  }
  local_88 = 8;
  memcpy(&local_d0,&local_70,0x48);
  FUN_001ac150(param_1,local_7c,local_78,local_74);
  return;
}

