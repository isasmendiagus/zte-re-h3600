// module: mt7915.ko
// function: MlmeDelBAReqSanity @ 0x1106b8
// size: 300 bytes
//

byte MlmeDelBAReqSanity(int param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *param_2;
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 < uVar2) {
    if (param_3 == 10) {
      uVar1 = *param_2;
      uVar2 = HcGetMaxStaNum(param_1);
      if (uVar1 < uVar2) {
        uVar1 = param_2[4];
        if (((byte)uVar1 & 0xf0) == 0) {
          iVar3 = memcmp((void *)((uint)*param_2 * 0x14c0 + param_1 + 0xa1e0c),param_2 + 1,6);
          if (iVar3 == 0) {
            return 1;
          }
          if (-1 < DebugLevel) {
            printk("MlmeDelBAReqSanity fail - the peer addr dosen\'t exist.\n");
            return (byte)uVar1 & 0xf0;
          }
        }
        else if (-1 < DebugLevel) {
          printk("MlmeDelBAReqSanity fail - The peer TID is incorrect.\n");
          return 0;
        }
      }
      else if (-1 < DebugLevel) {
        printk("MlmeDelBAReqSanity fail - The peer Mac is not associated yet.\n");
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("MlmeDelBAReqSanity fail - message lenght not correct.\n");
      return 0;
    }
  }
  return 0;
}

