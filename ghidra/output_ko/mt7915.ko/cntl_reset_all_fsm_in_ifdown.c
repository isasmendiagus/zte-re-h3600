// module: mt7915.ko
// function: cntl_reset_all_fsm_in_ifdown @ 0x10d898
// size: 124 bytes
//

undefined4 cntl_reset_all_fsm_in_ifdown(int param_1)

{
  int iVar1;
  undefined2 local_12 [3];
  
  iVar1 = *(int *)(param_1 + 8);
  local_12[0] = 0;
  if (iVar1 == 0) {
    printk(&_LC17,0x252);
    dump_stack();
    iVar1 = *(int *)(param_1 + 8);
  }
  MlmeEnqueueWithWdev(iVar1,5,0xc,2,local_12,0,param_1);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return 1;
}

