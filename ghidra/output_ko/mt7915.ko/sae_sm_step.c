// module: mt7915.ko
// function: sae_sm_step @ 0x20ac70
// size: 556 bytes
//

uint sae_sm_step(undefined4 param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_sm_step");
  }
  if (param_2 != (int *)0x0) {
    switch(param_3 | *param_2 << 2) {
    case 1:
      uVar1 = sae_prepare_commit(param_2);
      if (uVar1 != 0) {
        return uVar1;
      }
      iVar2 = sae_send_auth_commit(param_1,param_2);
      if (iVar2 == 0) {
        return 0xffff;
      }
    case 5:
      uVar1 = sae_process_commit(param_2);
      if (uVar1 != 0) {
        return uVar1;
      }
      iVar2 = sae_send_auth_confirm(param_1,param_2);
      if (iVar2 != 0) {
        iVar2 = param_2[0x60];
        if ((iVar2 != 0) && (*param_2 == 0 || *param_2 == 3)) {
          *(int *)(iVar2 + 0x1b904) = *(int *)(iVar2 + 0x1b904) + 1;
        }
        *param_2 = 2;
        *(undefined1 *)((int)param_2 + 0x2e) = 0;
        sae_set_retransmit_timer(param_2);
        return 0;
      }
      return 0xffff;
    case 6:
      iVar2 = sae_send_auth_commit(param_1,param_2);
joined_r0x0020adfc:
      if (iVar2 != 0) {
        sae_set_retransmit_timer(param_2);
        return 0;
      }
      return 0xffff;
    case 9:
      iVar2 = sae_check_big_sync(param_2);
      if (iVar2 == 0) {
        if (*(char *)((int)param_2 + 0x86) != '\0') {
          uVar1 = sae_process_commit(param_2);
          if (uVar1 != 0) {
            return uVar1;
          }
          *(undefined1 *)((int)param_2 + 0x86) = 0;
        }
        iVar2 = sae_send_auth_commit(param_1,param_2);
        if (iVar2 == 0) {
          return 0xffff;
        }
        iVar2 = sae_send_auth_confirm(param_1,param_2);
        goto joined_r0x0020adfc;
      }
      break;
    case 10:
      *(undefined2 *)(param_2 + 1) = 0xffff;
      *(short *)((int)param_2 + 6) = (short)param_2[0x21];
      if (param_2[0x5f] != 0) {
        delete_sae_instance();
        param_2[0x5f] = 0;
      }
      iVar2 = param_2[0x60];
      if ((iVar2 != 0) && (*param_2 - 1U < 2)) {
        *(int *)(iVar2 + 0x1b904) = *(int *)(iVar2 + 0x1b904) + -1;
      }
      *param_2 = 3;
      return 0;
    case 0xe:
      iVar2 = sae_check_big_sync(param_2);
      if (iVar2 == 0) {
        *(short *)((int)param_2 + 6) = (short)param_2[0x21];
        *(char *)((int)param_2 + 0x2e) = *(char *)((int)param_2 + 0x2e) + '\x01';
        iVar2 = sae_send_auth_confirm(param_1,param_2);
        return -(uint)(iVar2 == 0) & 0xffff;
      }
    }
  }
  return 0;
}

