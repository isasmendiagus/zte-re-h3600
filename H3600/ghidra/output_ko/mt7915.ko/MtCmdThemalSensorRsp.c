// module: mt7915.ko
// function: MtCmdThemalSensorRsp @ 0x1ac74c
// size: 64 bytes
//

void MtCmdThemalSensorRsp(int param_1,int param_2)

{
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 4),4);
  if (DebugLevel < 4) {
    return;
  }
  printk("ThemalSensor = 0x%x\n",*(undefined4 *)(param_2 + 4));
  return;
}

