// module: mt7915.ko
// function: bssUpdateRssiRmDetParams @ 0x1c26c8
// size: 148 bytes
//

void bssUpdateRssiRmDetParams(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined2 local_14;
  undefined2 local_12;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  byte local_d;
  int local_c;
  
  local_d = *(byte *)(param_2 + 0x68);
  local_14 = 5;
  local_12 = 0xc;
  local_c = (uint)local_d << 8;
  local_10 = 1;
  local_f = 2;
  local_e = 2;
  if (2 < DebugLevel) {
    printk("%s, fgEnable = %d, ucPktSource = %d, ucPktMAPara = %d, cRssiCCKLowThr = %d, cRssiOFDMLowThr = %d\n"
           ,"bssUpdateRssiRmDetParams",1,2,2,(int)(char)local_d,(int)(char)local_d);
  }
  AndesAppendCmdMsg(param_3,&local_14,0xc);
  return;
}

