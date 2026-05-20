// module: switch.ko
// function: FROM_WAN @ 0x12474
// size: 80 bytes
//

bool FROM_WAN(char *param_1)

{
  int iVar1;
  
  if (2 < g_switch_debug_level) {
    printk("xmit dev name %s\n",param_1);
  }
  iVar1 = strncmp(param_1,"pon",3);
  return iVar1 != 0;
}

