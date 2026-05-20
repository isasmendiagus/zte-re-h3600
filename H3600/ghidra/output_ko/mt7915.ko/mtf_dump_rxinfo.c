// module: mt7915.ko
// function: mtf_dump_rxinfo @ 0x19c094
// size: 796 bytes
//

void mtf_dump_rxinfo(undefined4 param_1,byte *param_2)

{
  hex_dump("RxInfo Raw Data",param_2,4);
  if (DebugLevel < 1) {
    return;
  }
  printk("RxInfo Fields:\n");
  if (DebugLevel < 1) {
LAB_0019c14c:
    if (0 < DebugLevel) {
      printk("\tU2M=%d\n",((uint)*param_2 << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tMcast=%d\n",((uint)*param_2 << 0x1a) >> 0x1f);
      goto LAB_0019c194;
    }
LAB_0019c1dc:
    if (0 < DebugLevel) {
      printk("\tCrc=%d\n",param_2[1] & 1);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tCipherErr=%d\n",((uint)param_2[1] << 0x1d) >> 0x1e);
      goto LAB_0019c224;
    }
LAB_0019c26c:
    if (0 < DebugLevel) {
      printk("\tRSSI=%d\n",((uint)param_2[1] << 0x1a) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tL2PAD=%d\n",((uint)param_2[1] << 0x19) >> 0x1f);
      goto LAB_0019c2b4;
    }
LAB_0019c2fc:
    if (DebugLevel < 1) goto LAB_0019c38c;
    printk("\tBssIdx3=%d\n",((uint)param_2[2] << 0x1e) >> 0x1f);
    if (DebugLevel < 1) {
      return;
    }
    printk("\twapi_kidx=%d\n",((uint)param_2[2] << 0x1d) >> 0x1f);
  }
  else {
    printk("\tBA=%d\n",*param_2 & 1);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tDATA=%d\n",((uint)*param_2 << 0x1e) >> 0x1f);
    if (0 < DebugLevel) {
      printk("\tNULLDATA=%d\n",((uint)*param_2 << 0x1d) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tFRAG=%d\n",((uint)*param_2 << 0x1c) >> 0x1f);
      goto LAB_0019c14c;
    }
LAB_0019c194:
    if (0 < DebugLevel) {
      printk("\tBcast=%d\n",((uint)*param_2 << 0x19) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tMyBss=%d\n",*param_2 >> 7);
      goto LAB_0019c1dc;
    }
LAB_0019c224:
    if (0 < DebugLevel) {
      printk("\tAMSDU=%d\n",((uint)param_2[1] << 0x1c) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tHTC=%d\n",((uint)param_2[1] << 0x1b) >> 0x1f);
      goto LAB_0019c26c;
    }
LAB_0019c2b4:
    if (0 < DebugLevel) {
      printk("\tAMPDU=%d\n",param_2[1] >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tDecrypted=%d\n",param_2[2] & 1);
      goto LAB_0019c2fc;
    }
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("\tpn_len=%d\n",((uint)param_2[2] << 0x1a) >> 0x1d);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tsw_fc_type0=%d\n",((uint)param_2[2] << 0x19) >> 0x1f);
LAB_0019c38c:
  if (DebugLevel < 1) {
    return;
  }
  printk("\tsw_fc_type1=%d\n",param_2[2] >> 7);
  return;
}

