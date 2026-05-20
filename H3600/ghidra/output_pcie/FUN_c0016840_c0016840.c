// vmlinux.bin: FUN_c0016840 @ 0xc0016840
// matched strings: request pcie irq failed
//

void FUN_c0016840(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_c004dec8(*(undefined4 *)(&DAT_c069ea34 + param_1 * 0x38),&LAB_c0015a74,0,0x80,
                       &DAT_c0585ca4,*(undefined4 *)(&DAT_c069ea20 + param_1 * 0x38));
  if (-1 < iVar1) {
    return;
  }
  FUN_c046ab98(s_request_pcie_irq_failed_c0585cac);
  return;
}

