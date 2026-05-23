// module: mt7915.ko
// function: bcn_buf_deinit @ 0xb3430
// size: 160 bytes
//

undefined4 bcn_buf_deinit(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    if ((*(int *)(param_2 + 4) != 1) && (-1 < DebugLevel)) {
      printk("%s(): Bcn not in idle(%d) when try to free it!\n","bcn_buf_deinit");
    }
    *(undefined4 *)(param_2 + 4) = 0;
  }
  if (*(int *)(param_2 + 0xc) != 0) {
    _raw_spin_lock_bh(param_2 + 0x3c);
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0xc));
    *(undefined4 *)(param_2 + 0xc) = 0;
    _raw_spin_unlock_bh(param_2 + 0x3c);
  }
  return 1;
}

