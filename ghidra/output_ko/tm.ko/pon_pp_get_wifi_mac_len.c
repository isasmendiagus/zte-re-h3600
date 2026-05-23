// module: tm.ko
// function: pon_pp_get_wifi_mac_len @ 0x29b84
// size: 212 bytes
//

undefined4 pon_pp_get_wifi_mac_len(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x10,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 0x3fff;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7346,"pon_pp_get_wifi_mac_len"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_pp_get_wifi_mac_len]output: wifi_mac_len = %d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7343,"pon_pp_get_wifi_mac_len"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x544);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

