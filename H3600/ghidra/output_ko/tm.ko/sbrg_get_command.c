// module: tm.ko
// function: sbrg_get_command @ 0x227ac
// size: 420 bytes
//

undefined4 sbrg_get_command(void)

{
  printk("tmtst -g_sbrg_pt_transfer_en          port\n");
  printk("tmtst -s_sbrg_pt_transfer_en          port     en\n");
  printk("tmtst -g_sbrg_hash_collision_pktdeal\n");
  printk("tmtst -s_sbrg_hash_collision_pktdeal  sel\n");
  printk("tmtst -s_sbrg_pt_transfer_int_mask    en\n");
  printk("tmtst -g_sbrg_pt_transfer_int_mask\n");
  printk("tmtst -s_sbrg_macaddr_learn_int_mask  en\n");
  printk("tmtst -g_sbrg_macaddr_learn_int_mask\n");
  printk("tmtst -s_sbrg_hashcol_int_mask        en\n");
  printk("tmtst -g_sbrg_hashcol_int_mask\n");
  printk("tmtst -s_sbrg_macage_int_mask         en\n");
  printk("tmtst -g_sbrg_macage_int_mask\n");
  printk("tmtst -g_sbrg_pttransfer_state\n");
  printk("tmtst -g_sbrg_macaddrln_state\n");
  printk("tmtst -g_sbrg_macaddrcol_state\n");
  printk("tmtst -g_sbrg_macaddrage_state\n");
  printk("tmtst -g_sbrg_statistics\n");
  printk("tmtst -g_sbrg_state\n");
  printk("tmtst -s_sbrg_pttransfer_state_rdy   rdy\n");
  printk("tmtst -s_sbrg_macaddrln_state_rdy    rdy \n");
  printk("tmtst -s_sbrg_macaddrcol_state_rdy   rdy \n");
  printk("tmtst -s_sbrg_macaddrage_state_rdy   rdy\n");
  printk("tmtst -g_sbrg_hash_addr              mac[5-0]\n");
  printk("tmtst -g_sbrg_ptclr_bit\n");
  printk("tmtst -g_sbrg_broad_vltrans_failure_pktdeal  port\n");
  printk("tmtst -s_sbrg_broad_vltrans_failure_pktdeal  port deal\n");
  printk("tmtst -g_sbrg_multi_vltrans_failure_pktdeal  port\n");
  printk("tmtst -s_sbrg_multi_vltrans_failure_pktdeal  port deal\n");
  printk("tmtst -g_sbrg_uni_vltrans_failure_pktdeal    port\n");
  printk("tmtst -s_sbrg_uni_vltrans_failure_pktdeal    port deal\n");
  printk("tmtst -g_sbrg_uni_vltrans_success_pktdeal    port\n");
  printk("tmtst -s_sbrg_uni_vltrans_success_pktdeal    port  deal\n");
  printk("tmtst -g_sbrg_broad_vtrans_success_pktdeal   port\n");
  printk("tmtst -s_sbrg_broad_vtrans_success_pktdeal   port  deal\n");
  return 0;
}

