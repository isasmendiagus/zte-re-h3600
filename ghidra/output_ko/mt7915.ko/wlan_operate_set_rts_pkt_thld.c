// module: mt7915.ko
// function: wlan_operate_set_rts_pkt_thld @ 0x107dac
// size: 56 bytes
//

undefined4
wlan_operate_set_rts_pkt_thld(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((param_1 != 0) && (iVar2 = *(int *)(param_1 + 0xb14), iVar2 != 0)) {
    uVar1 = *(undefined4 *)(param_1 + 8);
    *(char *)(iVar2 + 0x14) = (char)param_2;
    HW_SET_RTS_THLD(uVar1,param_1,param_2,*(undefined4 *)(iVar2 + 0x18),param_4);
  }
  return 0;
}

