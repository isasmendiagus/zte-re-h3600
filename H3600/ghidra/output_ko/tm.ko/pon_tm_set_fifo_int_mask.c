// module: tm.ko
// function: pon_tm_set_fifo_int_mask @ 0x45880
// size: 356 bytes
//

undefined4 pon_tm_set_fifo_int_mask(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_fifo_int_mask]input: FifoMsk=%d,FifoIntMsk=%d\n",param_1,param_2);
  }
  bVar4 = param_2 != 0;
  bVar3 = param_2 == 1;
  if (param_2 < 2) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  if (bVar4 && !bVar3) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7203,"pon_tm_set_fifo_int_mask"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x3cc);
    }
    uVar1 = 1;
  }
  else {
    iVar2 = tmOnuRegRead(0xd,&local_14,0,PonTmRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(0xd,local_14 & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff),0,
                            PonTmRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar2 = ___ratelimit(_rs_7208,"pon_tm_set_fifo_int_mask");
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x3db);
        return 0xffffffff;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7206,"pon_tm_set_fifo_int_mask"), iVar2 == 0)) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x3d3);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

