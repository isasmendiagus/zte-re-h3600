// module: tm.ko
// function: red_set_out_buffer_queue_cfg @ 0x42efc
// size: 400 bytes
//

undefined4 red_set_out_buffer_queue_cfg(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  int local_24 [2];
  
  local_24[0] = 0;
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][red_set_out_buffer_queue_cfg]input:\n"), 6 < g_tm_debug_level)) {
    printk("QueID = %d, guart_space = %d, max_space = %d\n",param_1,param_2,param_3);
  }
  if (param_1 < 400 && (param_3 < 0x10000 && param_2 < 0x1000)) {
    uVar5 = 0;
    if (local_24[0] == 0) {
      uVar5 = 0;
      uVar6 = 0;
      do {
        uVar6 = uVar6 + 1;
        uVar1 = red_get_ind_acc_done(local_24);
        uVar5 = uVar5 | uVar1;
        bVar7 = uVar6 == 0x13;
        if (uVar6 < 0x14) {
          bVar7 = local_24[0] == 0;
        }
      } while (bVar7);
      if (0x13 < uVar6) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar2 = ___ratelimit(_rs_7238,"red_set_out_buffer_queue_cfg");
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        printk("[TM][red_set_out_buffer_queue_cfg]indirect access time out\n");
        return 0xffffffff;
      }
    }
    iVar2 = red_set_indirect_rw_cmd(0,0,param_1);
    iVar4 = red_set_ind_acc_data(param_2 + param_3 * 0x800,0);
    uVar3 = 0;
    if ((iVar2 != 0 || uVar5 != 0) || iVar4 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_7240,"red_set_out_buffer_queue_cfg"), iVar2 != 0)) {
        printk("[TM][red_set_out_buffer_queue_cfg]indirect access failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7232,"red_set_out_buffer_queue_cfg"), iVar2 != 0)) {
      printk("[TM][red_set_out_buffer_queue_cfg]input invalid parameter!\n");
    }
    uVar3 = 1;
  }
  return uVar3;
}

