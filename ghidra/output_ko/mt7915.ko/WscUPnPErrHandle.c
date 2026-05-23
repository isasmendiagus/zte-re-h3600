// module: mt7915.ko
// function: WscUPnPErrHandle @ 0x1e2058
// size: 124 bytes
//

void WscUPnPErrHandle(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_14 [2];
  
  if (2 < DebugLevel) {
    printk("Into WscUPnPErrHandle, send WSC_OPCODE_UPNP_CTRL with eventID=0x%x!\n",param_3);
  }
  os_alloc_mem(0,local_14,0x400);
  if (local_14[0] != 0) {
    __memzero(local_14[0],0x400);
    BuildMessageNACK(param_1,param_2,local_14[0]);
    os_free_mem(local_14[0]);
  }
  return;
}

