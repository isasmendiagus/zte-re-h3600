// module: mt7915.ko
// function: sae_derive_commit_element_ecc @ 0x207988
// size: 316 bytes
//

undefined4 sae_derive_commit_element_ecc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_1c;
  
  iVar1 = *(int *)(param_1 + 0x5c);
  iVar2 = *(int *)(param_1 + 0x70);
  local_1c = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_commit_element_ecc");
  }
  if (iVar1 != 0 && param_2 != 0) {
    ecc_point_mul_windowed(iVar1,param_2,iVar2,&local_1c);
    if (local_1c == 0) {
      if (-1 < DebugLevel) {
        printk("%s(): ECC_POINT_MUL fail\n","sae_derive_commit_element_ecc");
        return 0;
      }
    }
    else {
      ecc_point_3d_to_2d(iVar2,local_1c);
      iVar1 = ecc_point_is_on_curve(iVar2,local_1c);
      if (iVar1 == 0) {
        if (-1 < DebugLevel) {
          printk("ecc_point_mul_dblandadd fail!!!!!!\n");
        }
        ecc_point_free(&local_1c);
        return 0;
      }
      ecc_point_inverse(local_1c,*(undefined4 *)(iVar2 + 4),&local_1c);
      if (local_1c != 0) {
        *(int *)(param_1 + 0x54) = local_1c;
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s(): inverse fail\n","sae_derive_commit_element_ecc");
        return 0;
      }
    }
  }
  return 0;
}

