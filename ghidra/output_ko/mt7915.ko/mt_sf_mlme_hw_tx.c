// module: mt7915.ko
// function: mt_sf_mlme_hw_tx @ 0x19b414
// size: 176 bytes
//

undefined4
mt_sf_mlme_hw_tx(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  uint __n;
  undefined2 local_22;
  
  local_22 = 1;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __n = (uint)*(byte *)(iVar1 + 2);
  asic_write_tmac_info_fixed_rate(param_1,param_2,param_3,param_4);
  *(void **)(param_5 + 0x30) = *(void **)(param_5 + 0x24);
  memcpy(*(void **)(param_5 + 0x58),*(void **)(param_5 + 0x24),__n);
  *(uint *)(param_5 + 0x30) = *(int *)(param_5 + 0x30) + __n;
  *(uint *)(param_5 + 0x28) = *(int *)(param_5 + 0x28) - __n;
  *(undefined1 *)(param_5 + 0x35) = 0;
  *(undefined1 *)(param_5 + 0x2c) = 0;
  *(undefined1 *)(param_5 + 0x34) = 0;
  *(undefined1 *)(param_5 + 0x39) = 0;
  asic_write_tx_resource(param_1,param_5,1,&local_22);
  return 0;
}

