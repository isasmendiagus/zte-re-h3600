// module: mt7915.ko
// function: cntl_join_start_conf @ 0x10d6dc
// size: 120 bytes
//

undefined4 cntl_join_start_conf(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined2 local_12 [3];
  
  iVar1 = *(int *)(param_1 + 8);
  local_12[0] = param_2;
  if (iVar1 == 0) {
    printk(&_LC17,0x20d);
    dump_stack();
    iVar1 = *(int *)(param_1 + 8);
  }
  MlmeEnqueueWithWdev(iVar1,5,1,2,local_12,0,param_1);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return 1;
}

