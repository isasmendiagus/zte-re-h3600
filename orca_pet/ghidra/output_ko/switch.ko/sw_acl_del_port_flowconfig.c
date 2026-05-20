// module: switch.ko
// function: sw_acl_del_port_flowconfig @ 0x11e70
// size: 432 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_acl_del_port_flowconfig(undefined1 *param_1)

{
  void *__dest;
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_30 [12];
  
  __dest = (void *)kmem_cache_alloc(_DAT_0002c350,0xd0);
  if (__dest == (void *)0x0) {
    printk("switch ERR: sw_acl_del_port_flowconfig alloc mem failed\n");
    uVar2 = 0xffffffff;
  }
  else {
    __memzero(auStack_30,8);
    __memzero(__dest,0x49c);
    if (1 < g_switch_debug_level) {
      printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
             ,"sw_acl_del_port_flowconfig","FlowConfig.ruleType",*param_1,"FlowConfig.rule_pri",
             param_1[1],"FlowConfig.index",*(undefined2 *)(param_1 + 2),"FlowConfig.direction",
             *(undefined4 *)(param_1 + 4),"FlowConfig.match.entrynum",param_1[8],
             "FlowConfig.fwd.fwdmode",*(undefined4 *)(param_1 + 0x24c),"FlowConfig.fwd.desportmsk",
             *(undefined4 *)(param_1 + 0x250),"FlowConfig.fwd.gemport",
             *(undefined2 *)(param_1 + 0x254),"FlowConfig.fwd.des_q",param_1[0x256],
             "FlowConfig.fwd.reserved",param_1[599],"FlowConfig.action.actionnum",param_1[600]);
    }
    memcpy(__dest,param_1,0x49c);
    iVar1 = zte_api_sw_qos_del_port_streamselect(__dest,auStack_30);
    if (iVar1 == 0) {
      kfree(__dest);
      uVar2 = 0;
    }
    else {
      printk("[%s] L%d tm sdk failed!\n","sw_acl_del_port_flowconfig",0x81);
      kfree(__dest);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

