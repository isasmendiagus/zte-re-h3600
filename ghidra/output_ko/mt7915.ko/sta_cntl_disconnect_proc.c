// module: mt7915.ko
// function: sta_cntl_disconnect_proc @ 0x7065c
// size: 264 bytes
//

void sta_cntl_disconnect_proc(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_20 [6];
  undefined2 local_1a;
  
  iVar3 = param_1[0x24b];
  iVar4 = *(int *)(iVar3 + 8);
  iVar1 = GetStaCfgByWdev(iVar4,iVar3);
  if (iVar1 == 0) {
    printk(&_LC1,0x46c);
    dump_stack();
    return;
  }
  local_1a = *(undefined2 *)((int)param_1 + 10);
  os_move_mem(auStack_20,param_1 + 1,6);
  if (*param_1 == 0) {
    MlmeEnqueueWithWdev(iVar4,2,5,8,auStack_20,0,iVar3);
    uVar2 = 4;
  }
  else {
    if (*param_1 != 1) goto LAB_000706b0;
    MlmeEnqueueWithWdev(iVar4,1,2,8,auStack_20,0,iVar3);
    uVar2 = 6;
  }
  cntl_fsm_state_transition(iVar3,uVar2,"sta_cntl_disconnect_proc");
  RtmpOsMlmeUp(iVar4 + 0x286298);
LAB_000706b0:
  *(undefined1 *)(iVar1 + 0x4160) = 0x20;
  os_zero_mem(iVar1 + 0x4140);
  return;
}

