// module: mt7915.ko
// function: dedicated_rx_hist_scan_timeout_action @ 0x22cd78
// size: 132 bytes
//

void dedicated_rx_hist_scan_timeout_action(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 auStack_4c [4];
  undefined4 auStack_48 [13];
  
  puVar2 = auStack_4c;
  os_zero_mem(puVar2,0x34);
  iVar1 = 0;
  mt_cmd_get_rdd_ipi_hist(param_1,0xc,auStack_4c);
  do {
    if (3 < DebugLevel) {
      printk("ipi[%d],\t ipi_hist_cnt=\t%d\n",iVar1,*(undefined4 *)(puVar2 + 4));
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 4;
  } while (iVar1 != 0xb);
  *(undefined4 *)(param_1 + 0xa79184) = 0;
  return;
}

