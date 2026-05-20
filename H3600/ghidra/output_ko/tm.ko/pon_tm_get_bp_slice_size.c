// module: tm.ko
// function: pon_tm_get_bp_slice_size @ 0x44e74
// size: 232 bytes
//

undefined4 pon_tm_get_bp_slice_size(uint *param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14;
  
  local_14 = 0;
  iVar1 = tmOnuRegRead(7,&local_14,0,PonTmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14 & 0x3fff;
    *param_2 = (local_14 << 2) >> 0x12;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7107,"pon_tm_get_bp_slice_size"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_tm_get_bp_slice_size]output: norm_bpsize=%d, jum_bpsizee=%d\n",*param_1,
           *param_2);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7104,"pon_tm_get_bp_slice_size"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x277);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

