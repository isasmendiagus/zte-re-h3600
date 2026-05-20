// module: mt7915.ko
// function: vow_mbss_init @ 0x4326c
// size: 84 bytes
//

void vow_mbss_init(int param_1,int param_2)

{
  undefined1 uVar1;
  
  if (param_2 == 0) {
    return;
  }
  vow_mbss_grp_band_map();
  vow_mbss_wmm_map(param_1,param_2);
  uVar1 = HcGetWmmIdx(param_1,param_2);
  vow_set_client(param_1,*(undefined1 *)(param_1 + (uint)*(byte *)(param_2 + 0xe) + 0xa7bea8),
                 *(undefined2 *)(param_2 + 0x10),uVar1);
  return;
}

