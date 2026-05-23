// module: tm.ko
// function: red_get_out_que_ram_used_space @ 0x4328c
// size: 560 bytes
//

undefined4 red_get_out_que_ram_used_space(uint param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  int local_28;
  uint local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][red_get_out_que_ram_used_space]input: que_index = %d\n",param_1);
  }
  if (399 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7271,"red_get_out_que_ram_used_space"), iVar2 != 0)) {
      printk("[TM][red_get_out_que_ram_used_space]input invalid parameter!\n");
    }
    return 1;
  }
  if (local_28 == 0) {
    uVar3 = 0;
    uVar4 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar1 = red_get_ind_acc_done(&local_28);
      uVar4 = uVar4 | uVar1;
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_28 == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      iVar2 = ___ratelimit(_rs_7277,"red_get_out_que_ram_used_space");
      goto joined_r0x000433d4;
    }
  }
  else {
    uVar4 = 0;
  }
  uVar3 = red_set_indirect_rw_cmd(1,1,param_1);
  uVar3 = uVar3 | uVar4;
  if (local_28 != 0) {
LAB_000433f4:
    iVar2 = red_get_ind_acc_data(&local_24,0);
    if (iVar2 == 0 && uVar3 == 0) {
      *param_2 = local_24 & 0x7ff;
      *param_3 = (local_24 << 6) >> 0x11;
      if ((6 < g_tm_debug_level) &&
         (printk("[TM][red_get_out_que_ram_used_space]output:\n"), 6 < g_tm_debug_level)) {
        printk("space_guart_size = %d, space_max_size = %d\n",*param_2,*param_3);
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_7284,"red_get_out_que_ram_used_space");
    if (iVar2 == 0) {
      return 0xffffffff;
    }
    printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_red.c",0x40d);
    return 0xffffffff;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    uVar4 = red_get_ind_acc_done(&local_28);
    uVar3 = uVar3 | uVar4;
    if (local_28 != 0) {
      if (iVar2 != 0x14) goto LAB_000433f4;
      break;
    }
  } while (iVar2 != 0x14);
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  iVar2 = ___ratelimit(_rs_7282,"red_get_out_que_ram_used_space");
joined_r0x000433d4:
  if (iVar2 != 0) {
    printk("[TM][red_get_out_que_ram_used_space]indirect access time out\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

