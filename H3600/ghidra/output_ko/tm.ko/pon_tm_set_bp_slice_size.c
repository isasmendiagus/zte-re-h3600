// module: tm.ko
// function: pon_tm_set_bp_slice_size @ 0x44d74
// size: 240 bytes
//

undefined4 pon_tm_set_bp_slice_size(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_bp_slice_size]input: norm_bpsize=%d jum_bpsize=%d\n",param_1,param_2);
  }
  uVar1 = param_2;
  if (param_2 < 0x3fff) {
    uVar1 = param_1;
  }
  if (uVar1 < 0x3fff) {
    iVar2 = tmOnuRegWrite(7,param_1 + param_2 * 0x10000,0,PonTmRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_7096,"pon_tm_set_bp_slice_size"), iVar2 != 0)) {
        printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",600);
      }
      return 0xffffffff;
    }
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar2 = ___ratelimit(_rs_7093,"pon_tm_set_bp_slice_size"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x24e);
  }
  return 1;
}

