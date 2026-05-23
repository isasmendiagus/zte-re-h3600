// module: mt7915.ko
// function: BackgroundSwitchChannelAction @ 0x22ce78
// size: 72 bytes
//

void BackgroundSwitchChannelAction(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0xa79184) = 3;
  printk("Switch to channel to %d\n",*(undefined1 *)(param_1 + 0xa795e5));
  rtmp_set_channel(param_1,uVar1,*(undefined1 *)(param_1 + 0xa795e5));
  *(undefined4 *)(param_1 + 0xa79184) = 0;
  return;
}

