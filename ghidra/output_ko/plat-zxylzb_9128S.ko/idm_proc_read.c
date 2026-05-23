// module: plat-zxylzb_9128S.ko
// function: idm_proc_read @ 0x14e0c
// size: 1008 bytes
//

int idm_proc_read(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = seq_printf(param_1,"idm_pop_size_err[0]: %u\n",idm_pop_size_err._0_4_,param_4,param_4);
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_size_err[1]: %u\n",idm_pop_size_err._4_4_);
  iVar3 = seq_printf(param_1 + (iVar1 + iVar2) * 0x58,"idm_pop_size_err[2]: %u\n",
                     idm_pop_size_err._8_4_);
  iVar3 = iVar3 + iVar1 + iVar2;
  iVar1 = seq_printf(param_1 + iVar3 * 0x58,"idm_push_failed[0]: %u\n",idm_push_failed._0_4_);
  iVar1 = iVar1 + iVar3;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed[1]: %u\n",idm_push_failed._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed[2]: %u\n",idm_push_failed._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[0]: %u\n",idm_push_failed_res._0_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[1]: %u\n",idm_push_failed_res._4_4_
                    );
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[2]: %u\n",idm_push_failed_res._8_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[3]: %u\n",
                     idm_push_failed_res._12_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[4]: %u\n",
                     idm_push_failed_res._16_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[5]: %u\n",
                     idm_push_failed_res._20_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[6]: %u\n",
                     idm_push_failed_res._24_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_cnt[0]: %u\n",idm_push_cnt._0_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_cnt[1]: %u\n",idm_push_cnt._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_cnt[2]: %u\n",idm_push_cnt._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_cnt[0]: %u\n",idm_pop_cnt._0_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_pop_cnt[1]: %u\n",idm_pop_cnt._4_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_cnt[2]: %u\n",idm_pop_cnt._8_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_full[0]: %u\n",idm_skb_stack_full._0_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_full[1]: %u\n",idm_skb_stack_full._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_full[2]: %u\n",idm_skb_stack_full._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_empty[0]: %u\n",idm_skb_stack_empty._0_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_empty[1]: %u\n",idm_skb_stack_empty._4_4_
                    );
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_empty[2]: %u\n",idm_skb_stack_empty._8_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_rx_arp_count: %u\n",idm_rx_arp_count);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_poll_cnt: %u\n",idm_poll_cnt);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_txtq_err: %u\n",idm_txtq_err);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_tx_done_total: %u\n",idm_tx_done_total);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_tx_full: %u\n",idm_tx_full);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_sw_tx_full: %u\n",idm_sw_tx_full);
  return iVar2 + iVar1;
}

