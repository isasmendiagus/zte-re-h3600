// module: tm.ko
// function: red_get_in_buffer_queue_cfg @ 0x43674
// size: 488 bytes
//

undefined4 red_get_in_buffer_queue_cfg(uint param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  int local_28;
  uint local_24;
  
  uVar3 = 0;
  local_28 = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    if (0x17f < param_1) {
      return 1;
    }
LAB_000436b0:
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1;
      uVar3 = red_get_ind_acc_done(&local_28);
      bVar4 = uVar1 == 0x13;
      if (uVar1 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar1) goto LAB_000436e0;
  }
  else {
    printk("[TM][red_set_in_buffer_queue_cfg]input: QueID = %d\n",param_1);
    if (0x17f < param_1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][red_set_in_buffer_queue_cfg]input invalid parameter!\n");
      return 1;
    }
    if (local_28 == 0) goto LAB_000436b0;
  }
  uVar1 = red_set_indirect_rw_cmd(1,2,param_1);
  uVar1 = uVar1 | uVar3;
  if (local_28 != 0) {
LAB_00043794:
    iVar2 = red_get_ind_acc_data(&local_24,0);
    if (iVar2 == 0 && uVar1 == 0) {
      *param_2 = local_24 & 0x1fff;
      *param_3 = (local_24 << 6) >> 0x13;
      if ((6 < g_tm_debug_level) &&
         (printk("[TM][red_set_in_buffer_queue_cfg]output:\n"), 6 < g_tm_debug_level)) {
        printk("guart_space = %d, max_space = %d\n",*param_2,*param_3);
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_7322,"red_get_in_buffer_queue_cfg");
    if (iVar2 != 0) {
      printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_red.c",0x4a1);
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    uVar3 = red_get_ind_acc_done(&local_28);
    uVar1 = uVar1 | uVar3;
    if (local_28 != 0) {
      if (iVar2 != 0x14) goto LAB_00043794;
      break;
    }
  } while (iVar2 != 0x14);
LAB_000436e0:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][red_set_in_buffer_queue_cfg]indirect access time out\n");
  return 0xffffffff;
}

