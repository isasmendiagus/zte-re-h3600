// module: mt7915.ko
// function: set_rx_amsdu @ 0xc3974
// size: 364 bytes
//

undefined4 set_rx_amsdu(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_20;
  uint local_1c [2];
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar2 = sscanf(param_2,"%u-%u",&local_20,local_1c), iVar2 != 2)) {
    if (-1 < DebugLevel) {
      printk("please input wcid-type (type: 0: RX_SW_AMSDU, 1:RX_HW_AMSDU)\n");
    }
  }
  else {
    if (1 < local_1c[0]) {
      if (-1 < DebugLevel) {
        printk("wrong type(%d), please input 0: RX_SW_AMSDU, 1: RX_HW_AMSDU\n");
      }
      return 0;
    }
    if (local_1c[0] == 1) {
      uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if ((uVar3 & 0x80) == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("wrong type(%d), chip do not have RX_HW_AMSDU cap, please input 0: RX_SW_AMSDU\n",
               local_1c[0]);
        return 0;
      }
      if (local_1c[0] != 0) {
        if (local_1c[0] != 1) {
          return 1;
        }
        *(undefined1 *)(param_1 + 0x9daa3) = 1;
        if (*(code **)(iVar1 + 0x58) == (code *)0x0) {
          return 1;
        }
        (**(code **)(iVar1 + 0x58))(param_1,local_20,1);
        return 1;
      }
    }
    *(undefined1 *)(param_1 + 0x9daa3) = 0;
    if (*(code **)(iVar1 + 0x58) != (code *)0x0) {
      (**(code **)(iVar1 + 0x58))(param_1,local_20);
      return 1;
    }
  }
  return 1;
}

