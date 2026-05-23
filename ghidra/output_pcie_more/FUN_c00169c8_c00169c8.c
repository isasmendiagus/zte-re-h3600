// FUN_c00169c8 @ c00169c8

void FUN_c00169c8(int param_1)

{
  int iVar1;
  
  FUN_c046ab98(s_synopsys_pcie_d_controller_waitt_c0585cc8,param_1);
  iVar1 = 2000;
  do {
    (*DAT_c068531c)(0x66665b0);
    DataSynchronizationBarrier(0xf);
    if ((uint)(*(int *)(*(int *)(&DAT_c069ea2c + param_1 * 0x38) + 0xdc) << 9) >> 0x1a == 0x11) {
      DataSynchronizationBarrier(0xf);
      FUN_c046ab98(s_pcie_d_link_up_gen_d_cnt__d__c0585cf8,param_1,
                   (uint)(*(int *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0x80) << 0xc) >> 0x1c,
                   0x7d1 - iVar1);
      return;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

