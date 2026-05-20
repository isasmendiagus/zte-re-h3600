// module: switch.ko
// function: sw_acl_get_port_flowconfig @ 0x121c0
// size: 568 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_acl_get_port_flowconfig(uint *param_1)

{
  void *__dest;
  undefined4 extraout_r1;
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  uint *puVar6;
  undefined8 uVar7;
  uint local_30;
  uint uStack_2c;
  
  local_30 = 0;
  uStack_2c = 0;
  __dest = (void *)kmem_cache_alloc(_DAT_0002c340,0xd0);
  if (__dest == (void *)0x0) {
    printk("switch ERR: sw_acl_get_port_flowconfig alloc mem failed\n");
    return -1;
  }
  __memzero(__dest,0x49c);
  if (1 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_acl_get_port_flowconfig"
           ,"FlowConfig.ruleType",(char)*param_1,"FlowConfig.rule_pri",
           *(undefined1 *)((int)param_1 + 1),"FlowConfig.index",*(undefined2 *)((int)param_1 + 2),
           "FlowConfig.direction",param_1[1],"FlowConfig.match.entrynum",(char)param_1[2]);
  }
  if ((char)param_1[2] != '\0') {
    puVar4 = param_1 + 8;
    iVar5 = 0;
    do {
      if (1 < g_switch_debug_level) {
        printk("FlowConfig.match.entry[%d.]field = %d\n",iVar5,puVar4[-5]);
      }
      puVar6 = puVar4 + -4;
      iVar2 = 0;
      uVar3 = g_switch_debug_level;
      do {
        if (1 < uVar3) {
          printk("FlowConfig.match.entry[%d].value[%d] = %x\n",iVar5,iVar2,(char)*puVar6);
          uVar3 = g_switch_debug_level;
        }
        iVar2 = iVar2 + 1;
        puVar6 = (uint *)((int)puVar6 + 1);
      } while (iVar2 != 0x10);
      iVar2 = 0;
      puVar6 = puVar4;
      do {
        if (1 < uVar3) {
          printk("FlowConfig.match.entry[%d].mask[%d] = %x\n",iVar5,iVar2,(char)*puVar6);
        }
        iVar2 = iVar2 + 1;
        puVar6 = (uint *)((int)puVar6 + 1);
        uVar3 = g_switch_debug_level;
      } while (iVar2 != 0x10);
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 9;
    } while (iVar5 < (int)(uint)(byte)param_1[2]);
  }
  memcpy(__dest,param_1,0x49c);
  uVar7 = zte_api_sw_qos_get_port_streamselect(__dest,&local_30);
  uVar1 = (undefined4)((ulonglong)uVar7 >> 0x20);
  iVar5 = (int)uVar7;
  if (iVar5 != 0) {
    if (g_switch_debug_level == 0) {
      uVar3 = (uint)*(ushort *)((int)param_1 + 2);
      goto LAB_000122c8;
    }
    printk("sw_acl_get_port_flowconfig is error: %d\n ",iVar5);
    uVar1 = extraout_r1;
  }
  uVar3 = (uint)*(ushort *)((int)param_1 + 2);
  if (1 < g_switch_debug_level) {
    printk("sw_acl_get_port_flowconfig result: %lld\n",uVar1,local_30,uStack_2c);
  }
LAB_000122c8:
  *param_1 = uVar3;
  param_1[2] = local_30;
  param_1[3] = uStack_2c;
  kfree(__dest);
  return iVar5;
}

