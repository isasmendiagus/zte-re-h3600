// module: mt7915.ko
// function: sae_parse_commit_element_ecc @ 0x207628
// size: 448 bytes
//

undefined4 sae_parse_commit_element_ecc(int param_1,int *param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  uVar2 = *(undefined4 *)(param_1 + 0x70);
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_element_ecc");
  }
  if (param_3 < (uint)(*param_2 + *(int *)(param_1 + 100) * 2)) {
    if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 1;
      printk("%s(): not enough data in commit element\n","sae_parse_commit_element_ecc");
    }
  }
  else {
    Bignum_Bin2BI(*param_2,*(int *)(param_1 + 100),&local_34);
    Bignum_Bin2BI(*param_2 + *(int *)(param_1 + 100),*(int *)(param_1 + 100),&local_30);
    hex_dump_with_cat_and_lvl("peer element x:",*param_2,*(undefined4 *)(param_1 + 100),0xf,0x20,4);
    hex_dump_with_cat_and_lvl
              ("peer element y:",*param_2 + *(int *)(param_1 + 100),*(int *)(param_1 + 100),0xf,0x20
               ,4);
    ecc_point_init(local_2c);
    Bignum_Copy(local_34,local_2c[0]);
    Bignum_Copy(local_30,local_2c[0] + 4);
    ecc_point_set_z_to_one(local_2c[0]);
    iVar1 = ecc_point_is_on_curve(uVar2,local_2c[0]);
    if (iVar1 == 0) {
      if (-1 < DebugLevel) {
        printk("%s(): is not on curve\n","sae_parse_commit_element_ecc");
      }
      uVar2 = 1;
      ecc_point_free(local_2c);
    }
    else {
      uVar2 = 0;
      *param_2 = *param_2 + *(int *)(param_1 + 100) * 2;
      *(int *)(param_1 + 0x58) = local_2c[0];
    }
  }
  Bignum_Free(&local_34);
  Bignum_Free(&local_30);
  return uVar2;
}

