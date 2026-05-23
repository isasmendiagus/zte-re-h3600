// compatible: snps,has-lpm-erratum
// function: FUN_c027c604 @ 0xc027c604
// found via struct field ptr -> 0xc027c604
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c027c604(undefined4 param_1)

{
  if (_DAT_c06bdea8 != 0) {
    FUN_c00c863c(param_1,s__devuid__u_c05b7238);
  }
  if (_DAT_c06bdeac != 0) {
    FUN_c00c863c(param_1,s__devgid__u_c05b7244);
  }
  if (DAT_c069eff0 != 0x1a4) {
    FUN_c00c863c(param_1,s__devmode__o_c05b7250);
  }
  if (_DAT_c06bdeb0 != 0) {
    FUN_c00c863c(param_1,s__busuid__u_c05b725c);
  }
  if (_DAT_c06bdeb4 != 0) {
    FUN_c00c863c(param_1,s__busgid__u_c05b7268);
  }
  if (DAT_c069eff2 != 0x16d) {
    FUN_c00c863c(param_1,s__busmode__o_c05b7274);
  }
  if (_DAT_c06bdeb8 != 0) {
    FUN_c00c863c(param_1,s__listuid__u_c05b7280);
  }
  if (_DAT_c06bdebc != 0) {
    FUN_c00c863c(param_1,s__listgid__u_c05b728c);
  }
  if (DAT_c069eff4 != 0x124) {
    FUN_c00c863c(param_1,s__listmode__o_c05b7298);
  }
  return 0;
}

