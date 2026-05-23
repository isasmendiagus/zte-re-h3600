// module: mt7915.ko
// function: WscApCliLinkDown @ 0x1e9dcc
// size: 108 bytes
//

void WscApCliLinkDown(undefined4 param_1,int param_2)

{
  byte local_9;
  
  local_9 = *(byte *)(param_2 + 0x1c54) & 0xf;
  if (2 < DebugLevel) {
    printk("-----> WscApCliLinkDown, apidx=%u\n");
  }
  if (local_9 < 2) {
    RTEnqueueInternalCmd(param_1,9,&local_9,1);
  }
  return;
}

