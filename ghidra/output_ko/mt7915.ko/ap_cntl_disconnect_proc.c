// module: mt7915.ko
// function: ap_cntl_disconnect_proc @ 0x4aed0
// size: 196 bytes
//

void ap_cntl_disconnect_proc(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_18 [6];
  undefined2 local_12;
  
  iVar2 = param_1[0x24b];
  local_12 = *(undefined2 *)((int)param_1 + 10);
  iVar3 = *(int *)(iVar2 + 8);
  os_move_mem(auStack_18,param_1 + 1,6);
  if (*param_1 == 0) {
    MlmeEnqueueWithWdev(iVar3,2,5,8,auStack_18,0,iVar2);
    uVar1 = 4;
  }
  else {
    if (*param_1 != 1) {
      return;
    }
    MlmeEnqueueWithWdev(iVar3,1,2,8,auStack_18,0,iVar2);
    uVar1 = 6;
  }
  cntl_fsm_state_transition(iVar2,uVar1,"ap_cntl_disconnect_proc");
  RtmpOsMlmeUp(iVar3 + 0x286298);
  return;
}

