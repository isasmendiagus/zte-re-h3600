// module: tm.ko
// function: sadm_get_indtbl_token_bucket_fill_spd @ 0x26350
// size: 472 bytes
//

undefined4 sadm_get_indtbl_token_bucket_fill_spd(uint param_1,uint param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined8 uVar4;
  uint local_20;
  int local_1c [2];
  
  uVar3 = param_2;
  if (param_2 < 8) {
    uVar3 = param_1;
  }
  local_20 = 0;
  local_1c[0] = 0;
  if ((7 < uVar3) || (param_2 == 0 && 6 < param_1)) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_indtbl_token_bucket_fill_spd]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_indtbl_token_bucket_fill_spd]input:inport_id = %d\n",param_1);
  }
  switch(param_2) {
  case 1:
    param_1 = param_1 + 0x10;
    uVar2 = 0;
    break;
  case 2:
    printk("ERROR\n");
    uVar2 = 0;
    param_1 = 0;
    break;
  case 3:
    uVar2 = 1;
    break;
  case 4:
    param_1 = param_1 + 0x20;
    uVar2 = 1;
    break;
  case 5:
    uVar2 = 2;
    break;
  case 7:
    param_1 = param_1 + 0x10;
  case 6:
    uVar2 = 3;
    break;
  default:
    param_1 = param_1 + 1;
    uVar2 = 0;
  }
  iVar1 = sadm_set_indreg_rd_cfg(param_1,uVar2,"sadm_get_indtbl_token_bucket_fill_spd");
  if (iVar1 == 0) {
    iVar1 = sadm_get_indacs_dat(&local_20);
    uVar4 = sadm_get_indacs_dat(local_1c,1);
    if ((int)uVar4 == 0 && iVar1 == 0) {
      param_3[1] = 0;
      uVar3 = local_1c[0] << 0x1e | local_20 >> 2;
      *param_3 = uVar3;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_indtbl_token_bucket_fill_spd]output:speed = %d\n",
               (int)((ulonglong)uVar4 >> 0x20),uVar3,0);
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14726,"sadm_get_indtbl_token_bucket_fill_spd");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14723,"sadm_get_indtbl_token_bucket_fill_spd");
  }
  if (iVar1 != 0) {
    printk("[TM][sadm_get_indtbl_token_bucket_fill_spd]write reg failed!\n");
  }
  return 0xffffffff;
}

