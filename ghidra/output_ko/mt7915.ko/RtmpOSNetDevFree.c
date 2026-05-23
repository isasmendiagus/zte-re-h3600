// module: mt7915.ko
// function: RtmpOSNetDevFree @ 0x244184
// size: 56 bytes
//

void RtmpOSNetDevFree(int param_1)

{
  if (param_1 != 0) {
    free_netdev(param_1);
    return;
  }
  printk(&_LC16,0x672);
  dump_stack();
  free_netdev(0);
  return;
}

