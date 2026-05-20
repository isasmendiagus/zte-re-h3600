// module: mt7915.ko
// function: mt_test_mac_restore_cr @ 0x257054
// size: 120 bytes
//

undefined4 mt_test_mac_restore_cr(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0x30));
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x401;
  }
  if (param_4 == 1) {
    if (*(code **)(iVar1 + 0x2d4) != (code *)0x0) {
      (**(code **)(iVar1 + 0x2d4))();
    }
  }
  else if ((param_4 == 2) && (*(code **)(iVar1 + 0x2d8) != (code *)0x0)) {
    (**(code **)(iVar1 + 0x2d8))(iVar2,param_3);
    return 0;
  }
  return 0;
}

