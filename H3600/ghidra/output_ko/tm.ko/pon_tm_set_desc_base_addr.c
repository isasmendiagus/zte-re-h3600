// module: tm.ko
// function: pon_tm_set_desc_base_addr @ 0x4496c
// size: 144 bytes
//

undefined4
pon_tm_set_desc_base_addr
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_desc_base_addr]input: DescAddr=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(4,param_1,0,PonTmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7043,"pon_tm_set_desc_base_addr"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x177);
  }
  return 0xffffffff;
}

