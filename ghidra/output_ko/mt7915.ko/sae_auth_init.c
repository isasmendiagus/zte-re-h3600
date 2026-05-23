// module: mt7915.ko
// function: sae_auth_init @ 0x20b128
// size: 396 bytes
//

undefined4
sae_auth_init(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = (int *)search_sae_instance(param_2,param_3,param_4);
  if (2 < DebugLevel) {
    if (piVar1 == (int *)0x0) {
      iVar3 = -1;
    }
    else {
      iVar3 = *piVar1;
    }
    printk("==>%s(): pSaeIns = %p, pSaeIns->state = %d\n","sae_auth_init",piVar1,iVar3);
  }
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)create_sae_instance(param_1,param_2,param_3,param_4,param_5,param_6,0,0);
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    piVar2[0x5f] = 0;
  }
  else {
    if (*piVar1 - 1U < 2) {
      return 0;
    }
    piVar2 = (int *)create_sae_instance(param_1,param_2,param_3,param_4,param_5,param_6,0,0);
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    piVar2[0x5f] = (int)piVar1;
    piVar1[0x5f] = (int)piVar2;
  }
  iVar3 = sae_group_allowed(piVar2,param_2 + 0x1b900,param_7);
  if (((iVar3 == 0) && (iVar3 = sae_prepare_commit(piVar2), iVar3 == 0)) &&
     (iVar3 = sae_send_auth_commit(param_1,piVar2), iVar3 != 0)) {
    iVar3 = piVar2[0x60];
    if ((iVar3 != 0) && (*piVar2 == 0 || *piVar2 == 3)) {
      *(int *)(iVar3 + 0x1b904) = *(int *)(iVar3 + 0x1b904) + 1;
    }
    *piVar2 = 1;
    sae_set_retransmit_timer(piVar2);
    return 1;
  }
  delete_sae_instance(piVar2);
  return 0;
}

