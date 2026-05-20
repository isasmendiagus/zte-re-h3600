// module: mt7915.ko
// function: set_tx_amsdu @ 0xc377c
// size: 504 bytes
//

undefined4 set_tx_amsdu(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  
  uVar5 = *(undefined4 *)(param_1 + 0xa797a0);
  iVar1 = hc_get_chip_cap(uVar5);
  iVar2 = hc_get_chip_dbg(uVar5);
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar3 = sscanf(param_2,"%u-%u-%u-%u",&local_28,&local_24,&local_20,&local_1c), iVar3 != 4)) {
    if (-1 < DebugLevel) {
      printk(
            "please input wcid-type-amsdu_nums-len (type: 0: TX_SW_AMSDU, 1:TX_HW_AMSDU), len unit 256b\n"
            );
    }
LAB_000c37d4:
    uVar5 = 1;
  }
  else {
    if (local_24 < 2) {
      if ((local_24 == 1) &&
         (uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0)), (uVar4 & 0x1000) == 0)) {
        if (-1 < DebugLevel) {
          printk("wrong type(%d), chip do not have TX_HW_AMSDU cap, please input 0: TX_SW_AMSDU\n",
                 local_24);
          return 0;
        }
      }
      else {
        if (local_20 <= *(byte *)(iVar1 + 0x1c5)) {
          if (0 < DebugLevel) {
            printk("wcid = %d, type: %d, nums  = %d, len = %d(unit: 256bytes)\n",local_28,local_24,
                   local_20,local_1c);
          }
          if (local_24 == 0) {
            *(undefined1 *)(param_1 + 0x9daa0) = 0;
            *(char *)(param_1 + 0x9daa2) = (char)local_20;
            if ((char)local_20 == '\0') {
              *(undefined1 *)(param_1 + 0x9daa1) = 0;
            }
            else {
              *(undefined1 *)(param_1 + 0x9daa1) = 1;
            }
            return 1;
          }
          if (local_24 == 1) {
            *(undefined1 *)(param_1 + 0x9daa0) = 1;
            if (*(code **)(iVar2 + 0x54) != (code *)0x0) {
              (**(code **)(iVar2 + 0x54))(param_1,local_28,local_20 & 0xff,local_1c);
              return 1;
            }
          }
          goto LAB_000c37d4;
        }
        if (-1 < DebugLevel) {
          printk("amsdu num is out of range(%d), chip cap(%d)\n",local_20);
          return 0;
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("wrong type(%d), please input 0: TX_SW_AMSDU, 1: TX_HW_AMSDU\n");
    }
    uVar5 = 0;
  }
  return uVar5;
}

