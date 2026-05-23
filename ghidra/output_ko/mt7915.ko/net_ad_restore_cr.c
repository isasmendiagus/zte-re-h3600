// module: mt7915.ko
// function: net_ad_restore_cr @ 0x25afc8
// size: 284 bytes
//

undefined4 net_ad_restore_cr(int param_1,int *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  piVar2 = param_2 + 0x5a;
  do {
    if (*param_2 == param_3) {
      if (param_2 == (int *)0x0) {
        return 0x600;
      }
      switch(param_2[2] + -1) {
      case 0:
        mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,param_2[1]);
        break;
      case 1:
        hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,param_2[1]);
        break;
      case 2:
        phy_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,param_2[1]);
        break;
      case 3:
        hw_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,param_2[1]);
        break;
      case 4:
        mcu_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,param_2[1]);
        break;
      default:
        printk("%s: bk-type not supported\n","net_ad_restore_cr",piVar2,param_2[2] + -1,param_4);
      }
      param_2[2] = 0;
      *param_2 = 0;
      param_2[1] = 0;
      return 0;
    }
    param_2 = param_2 + 3;
  } while (param_2 != piVar2);
  return 0x600;
}

