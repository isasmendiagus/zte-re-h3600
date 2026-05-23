// module: mt7915.ko
// function: init_owe_group @ 0x21beac
// size: 288 bytes
//

undefined4 init_owe_group(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int local_1c;
  
  local_1c = 0;
  iVar1 = get_ecc_group_info(param_2);
  iVar2 = get_ecc_group_info_bi(param_2);
  if (*(char *)((int)param_1 + 0x19) == '\x01') {
    return 1;
  }
  if (iVar1 == 0 || iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("==> %s(), get ec_group failed. shall not happen!\n","init_owe_group");
      return 0;
    }
  }
  else {
    if (*param_1 == 0) {
      *param_1 = iVar1;
    }
    if (param_1[1] == 0) {
      param_1[1] = iVar2;
    }
    ecc_point_init(&local_1c);
    Bignum_Copy(*(undefined4 *)(iVar2 + 0x14),local_1c);
    Bignum_Copy(*(undefined4 *)(iVar2 + 0x18),local_1c + 4);
    ecc_point_set_z_to_one(local_1c);
    param_1[4] = local_1c;
    iVar1 = ecc_gen_key(iVar1,iVar2,param_1 + 5,local_1c,param_1 + 3);
    if (iVar1 != 0) {
      *(undefined1 *)((int)param_1 + 0x19) = 1;
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("==> %s(), ecc_gen_key failed...\n","init_owe_group");
      return 0;
    }
  }
  return 0;
}

