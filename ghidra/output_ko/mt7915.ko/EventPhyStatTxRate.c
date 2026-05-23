// module: mt7915.ko
// function: EventPhyStatTxRate @ 0x153354
// size: 120 bytes
//

void EventPhyStatTxRate(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 auStack_9c [20];
  undefined1 auStack_88 [124];
  
  memcpy(auStack_88,&DAT_0029a44c,0x78);
  uVar1 = *(undefined1 *)(param_2 + 1);
  uVar2 = *(undefined1 *)(param_2 + 3);
  os_move_mem(auStack_9c,auStack_88 + (uint)*(byte *)(param_2 + 2) * 0x14,0x14);
  if (0 < DebugLevel) {
    printk("tx rate: %s(%dNss M%d)\n",auStack_9c,uVar2,uVar1);
  }
  return;
}

