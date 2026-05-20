// module: tm.ko
// function: pon_tm_set_queue_int_mask @ 0x45330
// size: 352 bytes
//

undefined4 pon_tm_set_queue_int_mask(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_queue_int_mask]input: que_num=%d,QueIntMsk=%d\n",param_2,param_1);
  }
  bVar4 = param_1 != 0;
  bVar3 = param_1 == 1;
  if (param_1 < 2) {
    bVar4 = 1 < param_2;
    bVar3 = param_2 == 2;
  }
  if (bVar4 && !bVar3) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7153,"pon_tm_set_queue_int_mask"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x316);
    }
    uVar1 = 1;
  }
  else {
    iVar2 = tmOnuRegRead(0xb,&local_14,0,PonTmRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(0xb,local_14 & ~(1 << (param_2 & 0xff)) | param_1 << (param_2 & 0xff),0,
                            PonTmRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar2 = ___ratelimit(_rs_7158,"pon_tm_set_queue_int_mask");
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x326);
        return 0xffffffff;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7156,"pon_tm_set_queue_int_mask"), iVar2 == 0)) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x31d);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

