// module: tm.ko
// function: sadm_get_dn_tf_mode @ 0x254c0
// size: 172 bytes
//

undefined4 sadm_get_dn_tf_mode(uint *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_c;
  
  local_c = 0;
  cVar1 = tmOnuRegRead(0x14,&local_c,0,sadmRegTable);
  if (cVar1 == '\0') {
    if (local_c < 5) {
      *param_1 = local_c;
    }
    if (g_tm_debug_level < 7) {
      uVar3 = 0;
    }
    else {
      printk("[TM][sadm_get_dn_tf_mode]output:tf_mod = %d\n",*param_1);
      uVar3 = 0;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14572,"sadm_get_dn_tf_mode"), iVar2 != 0)) {
      printk("[TM][sadm_get_dn_tf_mode]read reg failed!\n");
    }
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

