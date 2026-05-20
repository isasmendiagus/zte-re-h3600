// module: mt7915.ko
// function: wlan_operate_set_rts_len_thld @ 0x107de4
// size: 64 bytes
//

undefined4
wlan_operate_set_rts_len_thld(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((param_1 != 0) && (iVar2 = *(int *)(param_1 + 0xb14), iVar2 != 0)) {
    uVar1 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar2 + 0x18) = param_2;
    HW_SET_RTS_THLD(uVar1,param_1,*(undefined1 *)(iVar2 + 0x14),param_2,param_4);
    return 0;
  }
  return 0;
}

