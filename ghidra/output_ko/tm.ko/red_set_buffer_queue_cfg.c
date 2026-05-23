// module: tm.ko
// function: red_set_buffer_queue_cfg @ 0x43aa8
// size: 864 bytes
//

undefined4 red_set_buffer_queue_cfg(uint param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  int local_2c [2];
  
  local_2c[0] = 0;
  if ((((6 < g_tm_debug_level) &&
       (printk("[TM][red_set_in_buffer_queue_cfg]input:\n"), 6 < g_tm_debug_level)) &&
      (printk("QueID = %d, ALL_Space = %d\n",param_1,*param_2), 6 < g_tm_debug_level)) &&
     (printk("YellowDiscP0 = %d, YellowDiscP1 = %d, GreenDiscP0 = %d, GreenDiscP1 = %d\n",param_2[1]
             ,param_2[2],param_2[3],param_2[4]), 6 < g_tm_debug_level)) {
    printk("YellowThh0 = %d, YellowThh1 = %d, GreenThh0 = %d, GreenThh1 = %d\n",param_2[5],
           param_2[6],param_2[7],param_2[8]);
  }
  if ((((0x17f < param_1) || (0x1ffff < *param_2)) ||
      ((0xff < param_2[1] || ((0xff < param_2[2] || (0xff < param_2[3])))))) ||
     ((0xff < param_2[4] ||
      ((((0x1ffff < param_2[5] || (0x1ffff < param_2[6])) || (0x1ffff < param_2[7])) ||
       (0x1ffff < param_2[8])))))) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7362,"red_set_buffer_queue_cfg"), iVar2 != 0)) {
      printk("[TM][red_set_buffer_queue_cfg]input invalid parameter!\n");
    }
    return 1;
  }
  if (local_2c[0] == 0) {
    uVar5 = 0;
    uVar7 = 0;
    do {
      uVar5 = uVar5 + 1;
      uVar1 = red_get_ind_acc_done(local_2c);
      uVar7 = uVar7 | uVar1;
      bVar12 = uVar5 == 0x13;
      if (uVar5 < 0x14) {
        bVar12 = local_2c[0] == 0;
      }
    } while (bVar12);
    if (0x13 < uVar5) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      iVar2 = ___ratelimit(_rs_7368,"red_set_buffer_queue_cfg");
      if (iVar2 == 0) {
        return 0xffffffff;
      }
      printk("[TM][red_set_buffer_queue_cfg]indirect access time out\n");
      return 0xffffffff;
    }
  }
  else {
    uVar7 = 0;
  }
  iVar2 = red_set_indirect_rw_cmd(0,4,param_1);
  uVar1 = param_2[1];
  uVar4 = param_2[4];
  uVar9 = param_2[5];
  uVar11 = param_2[6];
  uVar5 = param_2[7];
  uVar6 = *param_2;
  uVar10 = param_2[2];
  uVar8 = param_2[3];
  iVar3 = red_set_ind_acc_data((short)param_2[8],3);
  if ((iVar2 == 0 && uVar7 == 0) && iVar3 == 0) {
    iVar2 = red_set_ind_acc_data(uVar5 * 0x10000 + (uVar11 & 0xffff),2);
    if (iVar2 == 0) {
      iVar2 = red_set_ind_acc_data(uVar9 * 0x10000 + (uVar8 & 0xff) + (uVar4 & 0xff) * 0x100,1);
      if (iVar2 == 0) {
        iVar2 = red_set_ind_acc_data(uVar6 + uVar10 * 0x1000000 + (uVar1 & 0xff) * 0x10000);
        if (iVar2 == 0) {
          return 0;
        }
        if ((g_tm_debug_level != 0) &&
           (iVar2 = ___ratelimit(_rs_7376,"red_set_buffer_queue_cfg"), iVar2 != 0)) {
          printk("[TM][red_set_buffer_queue_cfg]indirect access0 failed\n");
        }
      }
      else if ((g_tm_debug_level != 0) &&
              (iVar2 = ___ratelimit(_rs_7374,"red_set_buffer_queue_cfg"), iVar2 != 0)) {
        printk("[TM][red_set_buffer_queue_cfg]indirect access1 failed\n");
        return 0xffffffff;
      }
    }
    else if ((g_tm_debug_level != 0) &&
            (iVar2 = ___ratelimit(_rs_7372,"red_set_buffer_queue_cfg"), iVar2 != 0)) {
      printk("[TM][red_set_buffer_queue_cfg]indirect access2 failed\n");
      return 0xffffffff;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7370,"red_set_buffer_queue_cfg"), iVar2 != 0)) {
    printk("[TM][red_set_buffer_queue_cfg]indirect access3 failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

