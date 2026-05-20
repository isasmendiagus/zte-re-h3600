// module: tm.ko
// function: zte_api_sw_qos_get_availbktid @ 0x63c1c
// size: 140 bytes
//

undefined4 zte_api_sw_qos_get_availbktid(int *param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = (char *)((int)&fast_api_busy_lock + 3);
  while( true ) {
    pcVar2 = pcVar2 + 1;
    if (*pcVar2 == '\0') break;
    iVar1 = iVar1 + 1;
    if (iVar1 == 0x20) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("zte_api_sw_qos_get_availbktid return ERROR!\nno avail bucket\n");
      return 0xffffffff;
    }
  }
  *param_1 = iVar1;
  if (g_tm_debug_level < 2) {
    return 0;
  }
  printk("zte_api_sw_qos_get_availbktid output:\nbucket index=%d\n");
  return 0;
}

