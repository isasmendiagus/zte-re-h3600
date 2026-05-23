// module: mt7915.ko
// function: cntl_scan_request @ 0x10d5e4
// size: 128 bytes
//

undefined4 cntl_scan_request(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 0) {
    printk(&_LC17,0x1e7);
    dump_stack();
    iVar1 = *(int *)(param_1 + 8);
  }
  MlmeEnqueueWithWdev(iVar1,5,8,0x29,param_2,0,param_1);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return 1;
}

