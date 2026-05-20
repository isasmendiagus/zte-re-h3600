// module: tm.ko
// function: zte_api_sw_set_muti2uni @ 0x641ec
// size: 80 bytes
//

undefined4
zte_api_sw_set_muti2uni(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 == 1) {
    uVar1 = 2;
  }
  else {
    uVar1 = 0;
  }
  iVar2 = pon_pp_set_mult_mode(uVar1,1,param_3,param_4,param_4);
  if (iVar2 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pon_pp_set_mult_mode] set failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  return 0;
}

