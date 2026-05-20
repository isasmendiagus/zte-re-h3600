// module: mt7915.ko
// function: sae_auth_retransmit @ 0x20a59c
// size: 260 bytes
//

void sae_auth_retransmit(undefined4 param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = *(undefined4 *)(param_4 + 0x28);
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_auth_retransmit");
  }
  iVar1 = wdev_search_by_address(uVar3,param_2 + 0x58);
  iVar2 = sae_check_big_sync(param_2);
  if (iVar2 != 0) {
    if (iVar1 == 0) {
      return;
    }
    MlmeEnqueueWithWdev(uVar3,2,3,0,0,0,iVar1);
    return;
  }
  if (*param_2 == 1) {
    iVar1 = sae_send_auth_commit(uVar3,param_2);
    sae_set_retransmit_timer(param_2);
  }
  else {
    if (*param_2 != 2) goto LAB_0020a644;
    iVar1 = sae_send_auth_confirm(uVar3,param_2);
    sae_set_retransmit_timer(param_2);
  }
  if (iVar1 != 0) {
    return;
  }
LAB_0020a644:
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): retransemit fail (state = %d, sync = %d)\n","sae_auth_retransmit",*param_2,
         (int)*(char *)((int)param_2 + 0x2e));
  return;
}

