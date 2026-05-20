// module: switch.ko
// function: sw_qos_set_queue @ 0x1943c
// size: 692 bytes
//

undefined4 sw_qos_set_queue(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  bool bVar9;
  
  uVar5 = (uint)*param_1;
  bVar1 = param_1[1];
  uVar8 = *(uint *)(param_1 + 4);
  if (1 < g_switch_debug_level) {
    printk("the function:%s, the parameters coming in as follows:\n%s = %d\n%s = %d\n%s = %d\n",
           "sw_qos_set_queue","queue_id",uVar5,"status",(uint)bVar1,"weight",uVar8);
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    uVar2 = (uint)TCONT_QUEUE;
    bVar9 = g_qos_mode == '\x02';
    uVar5 = (uVar2 - 1) - uVar5 & 0xff;
    (&g_qos_queue)[uVar5 * 3] = uVar8;
    (&DAT_0002ba10)[uVar5 * 3] = (uint)bVar1;
    (&DAT_0002ba0c)[uVar5 * 3] = 1;
    if (bVar9) {
      g_queue_index = g_queue_index + 1;
      if (g_num_weight == 100) {
        if (g_queue_index <= uVar2) {
          if (uVar2 != g_queue_index) {
            return 0;
          }
          g_num_weight = 0;
          g_queue_index = 0;
          return 0;
        }
        g_queue_index = 1;
        g_num_weight = 0;
      }
      if (g_switch_debug_level != 0) {
        printk("the function:%s, num_weight = %d queue_index  = %d:\n","pon_driver_adapter_wght",
               g_num_weight,g_queue_index);
      }
      g_num_weight = g_num_weight + (&g_qos_queue)[uVar5 * 3];
      if ((g_num_weight == 100) && (uVar5 = (uint)g_tcont_start, uVar5 < g_tcont_size)) {
        do {
          if (TCONT_QUEUE != 0) {
            iVar3 = 0;
            piVar7 = &DAT_0002ba0c;
            do {
              iVar4 = 0;
              iVar6 = iVar3 + 1;
              if (*piVar7 == 1) {
                iVar4 = piVar7[-1];
              }
              iVar3 = tm_tcont_que_sch_weight_set(uVar5,iVar3,iVar4);
              if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
                printk("the function:%s, the error code is %d:\n","pon_driver_adapter_wght");
              }
              iVar3 = iVar6;
              piVar7 = piVar7 + 3;
            } while (iVar6 < (int)(uint)TCONT_QUEUE);
          }
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < (int)(uint)g_tcont_size);
      }
    }
  }
  else {
    if (7 < uVar5) {
      printk("queue_id = %d  >= QUEUE_SIZE\n",uVar5,8);
      return 0xffffffff;
    }
    if (*(char *)((int)&g_queue_mode + uVar5) != '\x02') {
      printk("queue_id=%d, weight=%d\n",uVar5,uVar8);
      return 0;
    }
    iVar3 = sw_qos_vdsl_up();
    if (iVar3 == 0) {
      iVar3 = zte_api_sw_qos_set_port_schedule
                        (zte_api_sw_mac_set_port_learnlimit,uVar5,0,uVar8 & 0xff);
    }
    else {
      iVar3 = tm_tcont_que_sch_weight_set(0,uVar5,uVar8);
    }
    if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
      printk("the function:%s, the error code is %d:\n","wan_driver_adapter_wght");
      return 0;
    }
  }
  return 0;
}

