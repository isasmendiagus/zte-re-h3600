// module: mt7915.ko
// function: ShowCpuUtilSum @ 0x192ea0
// size: 224 bytes
//

void ShowCpuUtilSum(int param_1)

{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f030,&local_20);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f034,&local_1c);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f038,&local_18);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f03c,local_14);
  if (0 < DebugLevel) {
    printk("\n\n       cpu ultility\n");
    if (0 < DebugLevel) {
      printk("       Busy:%d%% Peak:%d%%\n",local_20,local_1c);
      if (0 < DebugLevel) {
        printk("       IDLE:%d Peak_ILDE:%d\n",local_18,local_14[0]);
      }
    }
  }
  return;
}

