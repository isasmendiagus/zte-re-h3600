// module: mt7915.ko
// function: set_rx_cnt_io_thd @ 0xc3f0c
// size: 244 bytes
//

undefined4 set_rx_cnt_io_thd(int param_1,char *param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *local_14 [2];
  
  local_14[0] = param_2;
  iVar3 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if ((local_14[0] != (char *)0x0) && (*local_14[0] != '\0')) {
    pcVar4 = strsep(local_14,":");
    uVar5 = os_str_tol(pcVar4,0,10);
    if ((local_14[0] != (char *)0x0) && (*local_14[0] != '\0')) {
      uVar2 = os_str_tol(local_14[0],0,10);
      iVar1 = DebugLevel;
      uVar5 = uVar5 & 0xff;
      if (uVar5 <= *(byte *)(iVar3 + 1)) {
        *(undefined2 *)(*(int *)(*(int *)(iVar3 + 4) + uVar5 * 4) + 0x6a) = uVar2;
        if (iVar1 < 1) {
          return 1;
        }
        printk("rx ring %d rx count threshold for io = %u\n",uVar5);
        return 1;
      }
    }
  }
  if (0 < DebugLevel) {
    printk("invalid input, should be resource_idx:rx_cnt_io_thd\n");
  }
  return 1;
}

