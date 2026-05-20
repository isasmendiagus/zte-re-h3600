// module: mt7915.ko
// function: net_ad_backup_cr @ 0x25aeac
// size: 268 bytes
//

undefined4 net_ad_backup_cr(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  if (4 < param_4 - 1U) {
    return 0x600;
  }
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  piVar2 = (int *)0x0;
  piVar4 = param_2;
  do {
    piVar3 = piVar4;
    if (piVar3[2] == 0) {
      if (piVar2 == (int *)0x0) {
        piVar2 = piVar3;
      }
    }
    else if ((param_4 == piVar3[2]) && (*piVar3 == param_3)) break;
    piVar4 = piVar3 + 3;
    piVar3 = piVar2;
  } while (piVar4 != param_2 + 0x5a);
  if (piVar3 != (int *)0x0) {
    piVar3[2] = param_4;
    *piVar3 = param_3;
    switch(param_4) {
    case 2:
      hif_io_read32(*(undefined4 *)(iVar1 + 0xa797a0));
      return 0;
    case 3:
      phy_io_read32(*(undefined4 *)(iVar1 + 0xa797a0));
      return 0;
    case 4:
      hw_io_read32(*(undefined4 *)(iVar1 + 0xa797a0));
      return 0;
    case 5:
      mcu_io_read32(*(undefined4 *)(iVar1 + 0xa797a0));
      return 0;
    default:
      mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),param_3,piVar3 + 1);
      return 0;
    }
  }
  return 0x600;
}

