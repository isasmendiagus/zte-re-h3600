// module: mt7915.ko
// function: mt_ct_mlme_hw_tx @ 0x1c9798
// size: 212 bytes
//

int mt_ct_mlme_hw_tx(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    int param_5)

{
  byte bVar1;
  int iVar2;
  undefined2 local_22;
  
  local_22 = 1;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  asic_write_tmac_info_fixed_rate(param_1,param_2,param_3,param_4);
  *(void **)(param_5 + 0x30) = *(void **)(param_5 + 0x24);
  memcpy(*(void **)(param_5 + 0x58),*(void **)(param_5 + 0x24),(uint)*(byte *)(iVar2 + 2));
  *(uint *)(param_5 + 0x30) = *(int *)(param_5 + 0x30) + (uint)*(byte *)(iVar2 + 2);
  bVar1 = *(byte *)(iVar2 + 2);
  *(undefined1 *)(param_5 + 0x35) = 0;
  *(undefined1 *)(param_5 + 0x2c) = 0;
  *(uint *)(param_5 + 0x28) = *(int *)(param_5 + 0x28) - (uint)bVar1;
  *(undefined1 *)(param_5 + 0x34) = 0;
  *(undefined1 *)(param_5 + 0x39) = 0;
  iVar2 = asic_write_txp_info(param_1,*(int *)(param_5 + 0x58) + (uint)*(byte *)(iVar2 + 2),param_5)
  ;
  if (iVar2 == 0) {
    asic_write_tx_resource(param_1,param_5,1,&local_22);
  }
  return iVar2;
}

