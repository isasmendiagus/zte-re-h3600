// compatible: snps,has-lpm-erratum
// function: FUN_c027b9a8 @ 0xc027b9a8
// found via struct field ptr -> 0xc027b9a8
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c027b9a8(undefined4 param_1)

{
  if (_DAT_c06ad760 != 0) {
    FUN_c00c83b8(param_1,s__devuid__u_c05b8564);
  }
  if (_DAT_c06ad764 != 0) {
    FUN_c00c83b8(param_1,s__devgid__u_c05b8570);
  }
  if (DAT_c068ede4 != 0x1a4) {
    FUN_c00c83b8(param_1,s__devmode__o_c05b857c);
  }
  if (_DAT_c06ad768 != 0) {
    FUN_c00c83b8(param_1,s__busuid__u_c05b8588);
  }
  if (_DAT_c06ad76c != 0) {
    FUN_c00c83b8(param_1,s__busgid__u_c05b8594);
  }
  if (DAT_c068ede6 != 0x16d) {
    FUN_c00c83b8(param_1,s__busmode__o_c05b85a0);
  }
  if (_DAT_c06ad770 != 0) {
    FUN_c00c83b8(param_1,s__listuid__u_c05b85ac);
  }
  if (_DAT_c06ad774 != 0) {
    FUN_c00c83b8(param_1,s__listgid__u_c05b85b8);
  }
  if (DAT_c068ede8 != 0x124) {
    FUN_c00c83b8(param_1,s__listmode__o_c05b85c4);
  }
  return 0;
}

