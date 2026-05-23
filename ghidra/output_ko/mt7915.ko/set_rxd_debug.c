// module: mt7915.ko
// function: set_rxd_debug @ 0xbc5bc
// size: 296 bytes
//

undefined4 set_rxd_debug(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  iVar1 = hif_get_rx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 != (char *)0x0) {
    iVar3 = sscanf(param_2,"%u-%u-%u-%u",&local_28,&local_24,&local_20,&local_1c);
    if (iVar3 == 4) {
      if (0 < DebugLevel) {
        printk("hw_rxd=%d, sw_addr=%d, sw_payload=%d, hw_payload=%d\n",local_28,local_24,local_20,
               local_1c);
      }
    }
    else if (0 < DebugLevel) {
      printk("Format: iwpriv ra0 set rxd_debug=[hw_rxd]-[sw_addr]-[sw_payload]-[hw_payload]\n");
    }
    if (iVar1 != 0) {
      iVar3 = 0;
      do {
        iVar4 = *(int *)(*(int *)(iVar2 + 4) + iVar3 * 4);
        iVar3 = iVar3 + 1;
        iVar5 = iVar4 + 0x54;
        _raw_spin_lock_bh(iVar5);
        *(byte *)(iVar4 + 0x68) =
             (byte)(local_20 << 2) | (byte)(local_24 << 1) | (byte)local_28 | (byte)(local_1c << 3);
        _raw_spin_unlock_bh(iVar5);
      } while (iVar3 != iVar1);
    }
  }
  return 1;
}

