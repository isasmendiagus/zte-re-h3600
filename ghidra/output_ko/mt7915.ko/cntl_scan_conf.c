// module: mt7915.ko
// function: cntl_scan_conf @ 0x10d664
// size: 120 bytes
//

undefined4 cntl_scan_conf(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined2 local_12 [3];
  
  iVar1 = *(int *)(param_1 + 8);
  local_12[0] = param_2;
  if (iVar1 == 0) {
    printk(&_LC17,0x1fa);
    dump_stack();
    iVar1 = *(int *)(param_1 + 8);
  }
  MlmeEnqueueWithWdev(iVar1,5,9,2,local_12,0,param_1);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return 1;
}

