// module: tm.ko
// function: greg_info_show @ 0x6ea88
// size: 208 bytes
//

undefined4 greg_info_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  char *__s1;
  undefined4 uVar2;
  
  __s1 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(__s1,"helpGreg");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(" echo [port][enable 1:closed;0:not] > sportstatus       - set port close\n");
      printk(
            " echo [port]                        > gportstatus       - get Port close or not(1:closed;0:not)\n"
            );
      printk(" echo [port][enable]                > sport802xauth     - set 802.1x authen enable\n")
      ;
      printk(" echo [port]                        > gport802xauth     - get 802.1x authen enable\n")
      ;
      printk(" echo [ldo_val]                     > phyLdoTest        - set gephy ldo value test\n")
      ;
      printk(
            " echo [guard_en][print_en]          > phyGuardEn        - set gephy guard and print enable\n"
            );
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      printk("%s: illegal operation <%s>\n","greg_info_show",*param_2);
    }
  }
  return uVar2;
}

