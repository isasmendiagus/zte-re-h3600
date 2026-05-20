// module: mt7915.ko
// function: mt_test_mac_set_sta_pause_cr @ 0x257128
// size: 80 bytes
//

undefined4
mt_test_mac_set_sta_pause_cr(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r2;
  code *pcVar3;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0x30));
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x401;
  }
  pcVar3 = *(code **)(iVar1 + 0x2e4);
  if (pcVar3 != (code *)0x0) {
    (*pcVar3)(iVar2,0xf,extraout_r2,pcVar3,param_4);
    return 0;
  }
  return 0x404;
}

