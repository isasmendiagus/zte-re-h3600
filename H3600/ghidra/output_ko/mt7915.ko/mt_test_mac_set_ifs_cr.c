// module: mt7915.ko
// function: mt_test_mac_set_ifs_cr @ 0x257178
// size: 84 bytes
//

undefined4 mt_test_mac_set_ifs_cr(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0x30));
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x401;
  }
  if (*(code **)(iVar1 + 0x2dc) != (code *)0x0) {
    (**(code **)(iVar1 + 0x2dc))(iVar2,param_3);
    return 0;
  }
  return 0x404;
}

