// module: tm.ko
// function: sadm_set_indtbl_token_bucket_capacity @ 0x267c4
// size: 488 bytes
//

undefined4 sadm_set_indtbl_token_bucket_capacity(uint param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  undefined4 local_20;
  uint local_1c;
  
  bVar9 = 6 < param_1;
  if (param_1 < 8) {
    bVar9 = 0x1fffff < param_3;
  }
  if (7 < param_2) {
    bVar9 = true;
  }
  if ((bVar9) || (param_2 == 0 && 6 < param_1)) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14764,"sadm_set_indtbl_token_bucket_capacity"), iVar2 != 0)) {
      printk("[TM][sadm_set_indtbl_token_bucket_capacity]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  else {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_indtbl_token_bucket_capacity]input:inport_id = %d,capacity = %d\n",
             param_1);
    }
    switch(param_2) {
    case 1:
      param_1 = param_1 + 0x10;
      uVar1 = 0;
      break;
    case 2:
      uVar1 = 0;
      param_1 = 0;
      printk("ERROR\n");
      break;
    case 3:
      uVar1 = 1;
      break;
    case 4:
      param_1 = param_1 + 0x20;
      uVar1 = 1;
      break;
    case 5:
      uVar1 = 2;
      break;
    case 7:
      param_1 = param_1 + 0x10;
    case 6:
      uVar1 = 3;
      break;
    default:
      param_1 = param_1 + 1;
      uVar1 = 0;
    }
    iVar2 = sadm_set_indreg_rd_cfg(param_1,uVar1,"sadm_set_indtbl_token_bucket_capacity");
    iVar3 = sadm_get_indacs_dat(&local_20,0);
    iVar4 = sadm_get_indacs_dat(&local_1c,1);
    iVar5 = sadm_set_indreg_wr_cfg(param_1,uVar1,"sadm_set_indtbl_token_bucket_capacity");
    iVar6 = sadm_set_indacs_dat(0,2);
    iVar7 = sadm_set_indacs_dat(local_1c | param_3 << 5,1);
    iVar8 = sadm_set_indacs_dat(local_20,0);
    uVar1 = 0;
    if ((((((iVar3 != 0 || iVar2 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) || iVar7 != 0)
        || iVar8 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14777,"sadm_set_indtbl_token_bucket_capacity"), iVar2 != 0)) {
        printk("[TM][sadm_set_indtbl_token_bucket_capacity]write reg failed!\n");
      }
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

