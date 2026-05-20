// module: switch.ko
// function: pon_driver_adapter_schedue_mode_set @ 0x190d0
// size: 296 bytes
//

int pon_driver_adapter_schedue_mode_set
              (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (g_qos_mode != param_1) {
    g_qos_mode = (byte)param_1;
    qos_global_para_clr();
    if (2 < g_switch_debug_level) {
      printk("[%s] output mode = %d\n","pon_driver_adapter_schedue_mode_set",param_1,
             g_switch_debug_level,param_4);
    }
    if (param_1 == 1) {
      param_1 = 0;
    }
    else if (param_1 == 2) {
      param_1 = 1;
    }
    iVar4 = -1;
    uVar3 = (uint)g_tcont_start;
    if (uVar3 < g_tcont_size) {
      do {
        if (TCONT_QUEUE != 0) {
          iVar1 = 0;
          do {
            iVar2 = iVar1 + 1;
            iVar4 = tm_tcont_que_sch_sp_dwwr_mod_set(uVar3,iVar1,param_1);
            if ((iVar4 != 0) && (g_switch_debug_level != 0)) {
              printk("The function %s line:%d is error :%d\n","pon_driver_adapter_schedue_mode_set",
                     0x23f,iVar4);
            }
            iVar1 = iVar2;
          } while (iVar2 < (int)(uint)TCONT_QUEUE);
        }
        uVar3 = uVar3 + 1;
      } while ((int)uVar3 < (int)(uint)g_tcont_size);
    }
    return iVar4;
  }
  qos_global_para_clr();
  if (g_switch_debug_level != 0) {
    printk("[%s] the qos mode is not changed\n","pon_driver_adapter_schedue_mode_set");
    return 0;
  }
  return 0;
}

