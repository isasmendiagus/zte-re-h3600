// module: tm.ko
// function: sadm_set_indtbl_token_bucket_fill_spd @ 0x2613c
// size: 492 bytes
//

undefined4 sadm_set_indtbl_token_bucket_fill_spd(uint param_1,uint param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint local_28;
  uint auStack_24 [2];
  
  if ((param_2 < 8 && (param_1 < 0x11 && (param_4 == 0 && param_3 < 0x20000000))) &&
     (param_2 != 0 || param_1 < 7)) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_indtbl_token_bucket_fill_spd]input:inport_id = %d,speed = %d\n",param_1)
      ;
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
    iVar2 = sadm_set_indreg_rd_cfg(param_1,uVar1,"sadm_set_indtbl_token_bucket_fill_spd");
    iVar3 = sadm_get_indacs_dat(&local_28,0);
    iVar4 = sadm_get_indacs_dat(auStack_24,1);
    iVar5 = sadm_set_indreg_wr_cfg(param_1,uVar1,"sadm_set_indtbl_token_bucket_fill_spd");
    iVar6 = sadm_set_indacs_dat(auStack_24[0] & 0xffffffe0,1);
    iVar7 = sadm_set_indacs_dat(local_28 & 3 | param_3 << 2,0);
    uVar1 = 0;
    if (((((iVar3 != 0 || iVar2 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) || iVar7 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14701,"sadm_set_indtbl_token_bucket_fill_spd"), iVar2 != 0)) {
        printk("[TM][sadm_set_indtbl_token_bucket_fill_spd]write reg failed!\n");
      }
      uVar1 = 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14688,"sadm_set_indtbl_token_bucket_fill_spd"), iVar2 != 0)) {
      printk("[TM][sadm_set_indtbl_token_bucket_fill_spd]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

