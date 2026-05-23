// module: mt7915.ko
// function: MtCmdSetFreqOffset @ 0x1b6ef0
// size: 172 bytes
//

void MtCmdSetFreqOffset(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  byte local_64 [4];
  undefined1 local_60;
  undefined4 local_5c;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
    bVar1 = 0;
    if (*(int *)(param_1 + 0xa77bb4) == 1) {
      bVar1 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
    }
  }
  else {
    bVar1 = 1;
  }
  os_zero_mem(local_64,0x4c);
  if (2 < DebugLevel) {
    printk("%s, BandIdx:%d, FreqOffset:%d\n","MtCmdSetFreqOffset",param_3,param_2);
  }
  local_60 = (undefined1)param_3;
  local_64[1] = 10;
  local_64[0] = bVar1;
  local_5c = param_2;
  MtCmdATETest(param_1,local_64);
  return;
}

