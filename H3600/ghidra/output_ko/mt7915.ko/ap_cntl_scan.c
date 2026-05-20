// module: mt7915.ko
// function: ap_cntl_scan @ 0x4ae1c
// size: 176 bytes
//

void ap_cntl_scan(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x92c);
  iVar1 = *(int *)(iVar2 + 8);
  if (iVar1 == 0) {
    printk(&_LC0,0x24);
    dump_stack();
  }
  if (((*(uint *)(iVar1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(iVar1 + 0xa77bb4) != 1 || ((*(uint *)(*(int *)(iVar1 + 0xa77bb8) + 0x4e0) & 1) == 0)
      ))) {
    MlmeEnqueueWithWdev(iVar1,4,2,*(undefined4 *)(param_1 + 0x908),param_1,0,iVar2);
    cntl_fsm_state_transition(iVar2,1,"ap_cntl_scan");
    return;
  }
  return;
}

