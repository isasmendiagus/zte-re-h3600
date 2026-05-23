// module: mt7915.ko
// function: tm_tasklet_qm_init @ 0x1506a4
// size: 356 bytes
//

undefined4 tm_tasklet_qm_init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *(byte *)(iVar2 + 0x158);
  if (bVar1 == 1) {
    tasklet_init(param_1 + 0x285bb0,fp_tx_pkt_deq_tasklet,param_1);
    tasklet_init(param_1 + 0x285bc4,fp1_tx_pkt_deq_tasklet,param_1);
    *(undefined1 *)(param_1 + 0x285bac) = 1;
    tasklet_init(param_1 + 0x285bb0,fp_tx_pkt_deq_tasklet,param_1);
    tasklet_init(param_1 + 0x285bc4,fp1_tx_pkt_deq_tasklet,param_1);
    *(undefined1 *)(param_1 + 0x285bad) = 1;
  }
  else if (bVar1 == 3) {
    tasklet_init(param_1 + 0x285bb0,fp_fair_tx_pkt_deq_tasklet,param_1);
    tasklet_init(param_1 + 0x285bc4,fp1_fair_tx_pkt_deq_tasklet,param_1);
    *(undefined1 *)(param_1 + 0x285bac) = 1;
    *(undefined1 *)(param_1 + 0x285bad) = 1;
  }
  else if ((bVar1 & 0xfd) == 0) {
    tasklet_init(param_1 + 0x285bb0,ge_tx_pkt_deq_tasklet,param_1);
    *(undefined1 *)(param_1 + 0x285bac) = 1;
  }
  if (*(char *)(iVar2 + 0x15b) == '\0') {
    tasklet_init(param_1 + 0x285bdc,ge_rx_pkt_deq_tasklet,param_1,0,param_4);
  }
  return 0;
}

