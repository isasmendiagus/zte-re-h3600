// module: tm.ko
// function: sadm_get_indtbl_token_bucket_capacity @ 0x269d4
// size: 452 bytes
//

undefined4 sadm_get_indtbl_token_bucket_capacity(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_20;
  int aiStack_1c [2];
  
  uVar1 = param_2;
  if (param_2 < 8) {
    uVar1 = param_1;
  }
  if ((7 < uVar1) || (param_2 == 0 && 6 < param_1)) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_indtbl_token_bucket_capacity]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_indtbl_token_bucket_capacity]input:inport_id = %d\n",param_1);
  }
  switch(param_2) {
  case 1:
    param_1 = param_1 + 0x10;
    uVar4 = 0;
    break;
  case 2:
    printk("ERROR\n");
    uVar4 = 0;
    param_1 = 0;
    break;
  case 3:
    uVar4 = 1;
    break;
  case 4:
    param_1 = param_1 + 0x20;
    uVar4 = 1;
    break;
  case 5:
    uVar4 = 2;
    break;
  case 7:
    param_1 = param_1 + 0x10;
  case 6:
    uVar4 = 3;
    break;
  default:
    param_1 = param_1 + 1;
    uVar4 = 0;
  }
  iVar2 = sadm_set_indreg_rd_cfg(param_1,uVar4,"sadm_get_indtbl_token_bucket_capacity");
  if (iVar2 == 0) {
    iVar2 = sadm_get_indacs_dat(&local_20);
    iVar3 = sadm_get_indacs_dat(aiStack_1c,1);
    if (iVar3 == 0 && iVar2 == 0) {
      *param_3 = aiStack_1c[0] << 2 | local_20 >> 0x1e;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_indtbl_token_bucket_capacity]output:capacity = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_14802,"sadm_get_indtbl_token_bucket_capacity");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_14799,"sadm_get_indtbl_token_bucket_capacity");
  }
  if (iVar2 != 0) {
    printk("[TM][sadm_get_indtbl_token_bucket_capacity]write reg failed!\n");
  }
  return 0xffffffff;
}

