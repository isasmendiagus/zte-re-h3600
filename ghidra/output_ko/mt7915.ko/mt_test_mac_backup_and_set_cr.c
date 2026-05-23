// module: mt7915.ko
// function: mt_test_mac_backup_and_set_cr @ 0x257008
// size: 76 bytes
//

undefined4 mt_test_mac_backup_and_set_cr(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0x30));
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x401;
  }
  if (*(code **)(iVar1 + 0x2d0) != (code *)0x0) {
    (**(code **)(iVar1 + 0x2d0))();
    return 0;
  }
  return 0x404;
}

