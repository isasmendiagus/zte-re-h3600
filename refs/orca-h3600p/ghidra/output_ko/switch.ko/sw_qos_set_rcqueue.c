// module: switch.ko
// function: sw_qos_set_rcqueue @ 0x19700
// size: 232 bytes
//

int sw_qos_set_rcqueue(undefined1 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  char *pcVar7;
  uint uVar8;
  
  uVar3 = (uint)(byte)param_1[8];
  uVar1 = *param_1;
  uVar4 = *(undefined4 *)(param_1 + 4);
  if (1 < g_switch_debug_level) {
    pcVar5 = "bandwidth";
    pcVar7 = "action";
    uVar6 = uVar4;
    uVar8 = uVar3;
    printk("the function:%s, the parameters coming in as follows:\n%s = %d\n%s = %d\n%s = %d\n",
           "sw_qos_set_rcqueue","index",uVar1,"bandwidth",uVar4,"action",uVar3);
    if (1 < g_switch_debug_level) {
      printk("the function:%s, the parameters coming in as follows:\n%s = %d\n",
             "pon_driver_adapter_rcqueue","rcqueue.ena",uVar3 == 0,pcVar5,uVar6,pcVar7,uVar8);
    }
  }
  iVar2 = tm_flow_rate_limit_set(uVar1,uVar3 == 0,uVar4,0);
  if ((iVar2 != 0) && (g_switch_debug_level != 0)) {
    printk("the function:%s, qos set rcqueue failed\n","sw_qos_set_rcqueue");
  }
  return iVar2;
}

