// module: mt7915.ko
// function: MtCmdSetRxvIndex @ 0x1b7318
// size: 184 bytes
//

void MtCmdSetRxvIndex(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte local_64 [4];
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  
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
    printk("%s, Group_1:%d Group_2:%d Band:%d\n","MtCmdSetRxvIndex",param_2,param_3,param_4);
  }
  local_60 = (undefined1)param_2;
  local_5f = (undefined1)param_3;
  local_5e = (undefined1)param_4;
  local_64[1] = 0xf;
  local_64[0] = bVar1;
  MtCmdATETest(param_1,local_64);
  return;
}

