// module: mt7915.ko
// function: AsicSetRxFilter @ 0x132788
// size: 140 bytes
//

undefined4 AsicSetRxFilter(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  uint local_14;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(&local_18,8);
  if ("hif_set_WPDMA"[param_1 + 0xc] == '\x01') {
    local_14 = CONCAT31(local_14._1_3_,1);
  }
  else {
    local_18 = 0x73b86;
    local_14 = local_14 & 0xffff0000;
  }
  if (*(code **)(iVar1 + 0x68) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetRxFilter");
    return 0;
  }
  uVar2 = (**(code **)(iVar1 + 0x68))(param_1,local_18,local_14);
  return uVar2;
}

