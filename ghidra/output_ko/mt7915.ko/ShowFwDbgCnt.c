// module: mt7915.ko
// function: ShowFwDbgCnt @ 0x192d84
// size: 284 bytes
//

void ShowFwDbgCnt(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint local_20;
  undefined4 local_1c [2];
  
  local_20 = 0;
  local_1c[0] = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f2b8,&local_20);
  uVar1 = local_20;
  local_20 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f2bc,&local_20);
  uVar2 = local_20;
  if (0 < DebugLevel) {
    printk("\n\n       fw dbg counter\n");
  }
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x58000204,local_1c);
  if (0 < DebugLevel) {
    printk("       inrt enable = 0x%x\n",local_1c[0]);
    if (0 < DebugLevel) {
      printk("       CMD:%d EVENT:%d\n",(uVar1 << 0x10) >> 0x18,uVar1 & 0xff);
      if (0 < DebugLevel) {
        printk("       Msdu_Miss:%d Alloc_Fail:%d\n",0,0);
        if (0 < DebugLevel) {
          printk("       Intr:%d Dequeue:%d\n",(uVar2 << 0x10) >> 0x18,uVar2 & 0xff);
        }
      }
    }
  }
  return;
}

