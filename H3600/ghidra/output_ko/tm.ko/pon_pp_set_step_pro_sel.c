// module: tm.ko
// function: pon_pp_set_step_pro_sel @ 0x282c8
// size: 352 bytes
//

undefined4 pon_pp_set_step_pro_sel(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_step_pro_sel]input: port_num=%d,pro_sel=%d\n",param_2,param_1);
  }
  bVar4 = param_1 != 0;
  bVar3 = param_1 == 1;
  if (param_1 < 2) {
    bVar4 = 6 < param_2;
    bVar3 = param_2 == 7;
  }
  if (bVar4 && !bVar3) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7088,"pon_pp_set_step_pro_sel"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x126);
    }
    uVar1 = 1;
  }
  else {
    iVar2 = tmOnuRegRead(3,&local_14,0,PonPpRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(3,local_14 & ~(1 << (param_2 & 0xff)) | param_1 << (param_2 & 0xff),0,
                            PonPpRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar2 = ___ratelimit(_rs_7093,"pon_pp_set_step_pro_sel");
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x136);
        return 0xffffffff;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7091,"pon_pp_set_step_pro_sel"), iVar2 == 0)) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x12d);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

