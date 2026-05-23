// module: mt7915.ko
// function: remove_vlan_tag @ 0xc5820
// size: 108 bytes
//

void remove_vlan_tag(undefined4 param_1,int param_2)

{
  void *__src;
  
  __src = *(void **)(param_2 + 0xcc);
  if (__src == (void *)0x0) {
    printk(&_LC10,0x88);
    dump_stack();
    __src = *(void **)(param_2 + 0xcc);
  }
  memmove((void *)((int)__src + 4),__src,0xc);
  RtmpOsSkbPullRcsum(param_2,4);
  RtmpOsSkbResetMacHeader(param_2);
  RtmpOsSkbResetNetworkHeader(param_2);
  RtmpOsSkbResetTransportHeader(param_2);
  RtmpOsSkbResetMacLen(param_2);
  return;
}

