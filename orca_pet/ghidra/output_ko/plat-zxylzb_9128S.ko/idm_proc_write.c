// module: plat-zxylzb_9128S.ko
// function: idm_proc_write @ 0x14e10
// size: 276 bytes
//

undefined4 idm_proc_write(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  uVar4 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
  uVar2 = param_2 + 1;
  uVar3 = uVar2;
  if (param_2 != -1) {
    uVar3 = uVar2 - (uVar4 + 1);
  }
  if (param_2 != -1 && uVar2 <= uVar4) {
    uVar4 = 0;
  }
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (uVar4 == 0) {
    iVar1 = __copy_from_user(&local_2c,param_2,1);
    if (iVar1 == 0) {
      iVar1 = simple_strtoul(&local_2c,0,10);
      if (iVar1 == 0) {
        return param_3;
      }
      printk("clean idm stat\n");
      iVar1 = 0;
      do {
        *(undefined4 *)(idm_pop_size_err + iVar1 * 4) = 0;
        *(undefined4 *)(idm_push_failed + iVar1 * 4) = 0;
        *(undefined4 *)(idm_push_cnt + iVar1 * 4) = 0;
        *(undefined4 *)(idm_pop_cnt + iVar1 * 4) = 0;
        *(undefined4 *)(idm_skb_stack_full + iVar1 * 4) = 0;
        *(undefined4 *)(idm_skb_stack_empty + iVar1 * 4) = 0;
        iVar1 = iVar1 + 1;
      } while (iVar1 != 3);
      idm_rx_arp_count = 0;
      idm_poll_cnt = 0;
      idm_txtq_err = 0;
      idm_tx_done_total = 0;
      idm_tx_full = 0;
      idm_sw_tx_full = 0;
      return param_3;
    }
  }
  else {
    __memzero(&local_2c,1,uVar3);
  }
  printk(&_LC33);
  return 0xffffffff;
}

