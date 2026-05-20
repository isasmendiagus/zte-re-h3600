// module: mt7915.ko
// function: vow_mbss_wmm_map @ 0x42c60
// size: 76 bytes
//

void vow_mbss_wmm_map(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return;
  }
  uVar1 = HcGetWmmIdx();
  iVar2 = param_1 + (uint)*(byte *)(param_2 + 0xe);
  *(undefined1 *)(iVar2 + 0xa79816) = uVar1;
  vow_set_mbss2wmm_map
            (param_1,*(undefined1 *)(param_1 + (uint)*(byte *)(param_2 + 0xe) + 0xa7bea8),iVar2,
             param_4);
  return;
}

