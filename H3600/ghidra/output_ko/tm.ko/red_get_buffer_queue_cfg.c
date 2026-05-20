// module: tm.ko
// function: red_get_buffer_queue_cfg @ 0x43e24
// size: 692 bytes
//

undefined4 red_get_buffer_queue_cfg(uint param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  int local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24 [2];
  
  uVar5 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0x17f < param_1) {
      return 1;
    }
LAB_00043e68:
    uVar6 = 0;
    uVar5 = 0;
    do {
      uVar6 = uVar6 + 1;
      uVar1 = red_get_ind_acc_done(&local_34);
      uVar5 = uVar5 | uVar1;
      bVar8 = uVar6 == 0x13;
      if (uVar6 < 0x14) {
        bVar8 = local_34 == 0;
      }
    } while (bVar8);
    if (0x13 < uVar6) goto LAB_00043e9c;
  }
  else {
    printk("[TM][red_get_in_buffer_queue_cfg]input: QueID = %d\n",param_1);
    if (0x17f < param_1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][red_get_in_buffer_queue_cfg]input invalid parameter!\n");
      return 1;
    }
    if (local_34 == 0) goto LAB_00043e68;
  }
  uVar6 = red_set_indirect_rw_cmd(1,4,param_1);
  uVar6 = uVar6 | uVar5;
  if (local_34 != 0) {
LAB_00043f50:
    iVar7 = red_get_ind_acc_data(local_24,3);
    iVar2 = red_get_ind_acc_data(&local_28,2);
    iVar3 = red_get_ind_acc_data(&local_2c,1);
    iVar4 = red_get_ind_acc_data(&local_30,0);
    if ((((iVar7 == 0 && uVar6 == 0) && iVar2 == 0) && iVar3 == 0) && iVar4 == 0) {
      *param_2 = local_30 & 0xffff;
      uVar5 = g_tm_debug_level;
      param_2[2] = local_30 >> 0x18;
      param_2[1] = (local_30 << 8) >> 0x18;
      param_2[3] = local_2c & 0xff;
      param_2[4] = (local_2c << 0x10) >> 0x18;
      param_2[5] = local_2c >> 0x10;
      param_2[6] = local_28 & 0xffff;
      param_2[7] = local_28 >> 0x10;
      param_2[8] = local_24[0] & 0xffff;
      if ((((6 < uVar5) && (printk("[TM][red_get_buffer_queue_cfg]output:\n"), 6 < g_tm_debug_level)
           ) && (printk("ALL_Space = %d\n",*param_2), 6 < g_tm_debug_level)) &&
         (printk("YellowDiscP0 = %d, YellowDiscP1 = %d, GreenDiscP0 = %d, GreenDiscP1 = %d\n",
                 param_2[1],param_2[2],param_2[3],param_2[4]), 6 < g_tm_debug_level)) {
        printk("YellowThh0 = %d, YellowThh1 = %d, GreenThh0 = %d, GreenThh1 = %d\n",param_2[5],
               param_2[6],param_2[7],param_2[8]);
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar7 = ___ratelimit(_rs_7396,"red_get_buffer_queue_cfg");
    if (iVar7 != 0) {
      printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_red.c",0x5ce);
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  iVar7 = 0;
  do {
    iVar7 = iVar7 + 1;
    uVar5 = red_get_ind_acc_done(&local_34);
    uVar6 = uVar6 | uVar5;
    if (local_34 != 0) {
      if (iVar7 != 0x14) goto LAB_00043f50;
      break;
    }
  } while (iVar7 != 0x14);
LAB_00043e9c:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][red_get_in_buffer_queue_cfg]indirect access time out\n");
  return 0xffffffff;
}

