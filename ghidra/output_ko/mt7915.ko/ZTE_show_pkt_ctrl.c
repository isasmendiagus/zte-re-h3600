// module: mt7915.ko
// function: ZTE_show_pkt_ctrl @ 0x15a938
// size: 744 bytes
//

undefined4 ZTE_show_pkt_ctrl(int *param_1)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(*param_1 + 0x3c);
  if (DebugLevel < 0) {
    return 1;
  }
  printk("per_pkt_ctrl_enable=%d\n",(char)param_1[uVar1 * 0x160d + 0xaf291]);
  if (DebugLevel < 0) {
LAB_0015a9f0:
    if (-1 < DebugLevel) {
      printk("apply_power=%d\n",*(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca49));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("apply_txs=%d\n",*(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca4a));
      goto LAB_0015aa3c;
    }
LAB_0015aa90:
    if (-1 < DebugLevel) {
      printk("max_tx_time=%d\n",param_1[uVar1 * 0x160d + 0xaf295]);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("transmit_mode=%d\n",param_1[uVar1 * 0x160d + 0xaf296]);
      goto LAB_0015aadc;
    }
LAB_0015ab30:
    if (DebugLevel < 0) goto LAB_0015abd0;
    printk("transmit_bw=%d\n",param_1[uVar1 * 0x160d + 0xaf299]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("transmit_ldpc=%d\n",param_1[uVar1 * 0x160d + 0xaf29a]);
  }
  else {
    printk("apply_tid_enable=%d\n",*(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca45));
    if (DebugLevel < 0) {
      return 1;
    }
    printk("apply_retry_limit=%d\n",*(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca46));
    if (-1 < DebugLevel) {
      printk("apply_fix_rate=%d\n",*(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca47));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("apply_ba=%d\n",(char)param_1[uVar1 * 0x160d + 0xaf292]);
      goto LAB_0015a9f0;
    }
LAB_0015aa3c:
    if (-1 < DebugLevel) {
      printk("tid_by_host=%d\n",param_1[uVar1 * 0x160d + 0xaf293]);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("retry_limit_by_host=%d\n",param_1[uVar1 * 0x160d + 0xaf294]);
      goto LAB_0015aa90;
    }
LAB_0015aadc:
    if (-1 < DebugLevel) {
      printk("transmit_stbc=%d\n",param_1[uVar1 * 0x160d + 0xaf297]);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("transmit_sgi=%d\n",param_1[uVar1 * 0x160d + 0xaf298]);
      goto LAB_0015ab30;
    }
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("transmit_nss=%d\n",param_1[uVar1 * 0x160d + 0xaf29b]);
  if (DebugLevel < 0) {
    return 1;
  }
  printk("transmit_mcs=%d\n",param_1[uVar1 * 0x160d + 0xaf29c]);
LAB_0015abd0:
  if (-1 < DebugLevel) {
    printk("BA_disable=%d\n",(char)param_1[uVar1 * 0x160d + 0xaf29d]);
    if (-1 < DebugLevel) {
      printk("power_offset=%d\n",param_1[uVar1 * 0x160d + 0xaf29e]);
    }
  }
  return 1;
}

