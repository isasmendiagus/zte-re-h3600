// module: switch.ko
// function: ethdrv_test_show @ 0x1004c
// size: 404 bytes
//

undefined4 ethdrv_test_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(pcVar3,"help");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands\n");
      printk("============================================================================\n");
      printk(" echo dbg recv|mac|send|close|all >dbg set the debug mode\n");
      printk(" echo mac xx:xx:xx:xx:xx:xx       >mac set the debug mac \n");
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat help\n");
      printk(" cat dbgmode                           show debug mode\n");
      printk(" cat dbgmac                            show debug mac\n");
      return 0;
    }
    iVar1 = strcmp(pcVar3,"dbgmode");
    if (iVar1 == 0) {
      if (g_debug_mode < 5) {
        pcVar3 = (&CSWTCH_19)[g_debug_mode];
      }
      else {
        pcVar3 = "UNKOWN";
      }
      printk("debug mode %s \n",pcVar3);
      uVar2 = 0;
    }
    else {
      iVar1 = strcmp(pcVar3,"dbgmac");
      if (iVar1 == 0) {
        printk("debug mac is %02x:%02x:%02x:%02x:%02x:%02x\n",(undefined1)g_eth_debug_mac,
               g_eth_debug_mac._1_1_,g_eth_debug_mac._2_1_,g_eth_debug_mac._3_1_,
               g_eth_debug_mac._4_1_,g_eth_debug_mac._5_1_);
        return 0;
      }
      uVar2 = 0;
      printk("illegal operation <%s>\n",*param_2);
    }
  }
  return uVar2;
}

