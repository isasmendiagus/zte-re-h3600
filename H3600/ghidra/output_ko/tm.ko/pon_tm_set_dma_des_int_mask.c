// module: tm.ko
// function: pon_tm_set_dma_des_int_mask @ 0x455d8
// size: 352 bytes
//

undefined4 pon_tm_set_dma_des_int_mask(uint param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_dma_des_int_mask]input: dma_des=%d,QueIntMsk=%d\n",param_2,param_1);
  }
  uVar1 = param_1;
  if (param_1 < 2) {
    uVar1 = param_2;
  }
  if (uVar1 < 2) {
    iVar3 = tmOnuRegRead(0xc,&local_14,0,PonTmRegTable);
    if (iVar3 == 0) {
      iVar3 = tmOnuRegWrite(0xc,local_14 & ~(1 << (param_2 & 0xff)) | param_1 << (param_2 & 0xff),0,
                            PonTmRegTable);
      uVar2 = 0;
      if (iVar3 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar3 = ___ratelimit(_rs_7183,"pon_tm_set_dma_des_int_mask");
        if (iVar3 == 0) {
          return 0xffffffff;
        }
        printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x380);
        return 0xffffffff;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar3 = ___ratelimit(_rs_7181,"pon_tm_set_dma_des_int_mask"), iVar3 == 0)) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x377);
      uVar2 = 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar3 = ___ratelimit(_rs_7178,"pon_tm_set_dma_des_int_mask"), iVar3 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x370);
    }
    uVar2 = 1;
  }
  return uVar2;
}

