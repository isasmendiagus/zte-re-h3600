// module: tm.ko
// function: spa_get_onu_mac_addr @ 0x39528
// size: 332 bytes
//

uint spa_get_onu_mac_addr(uint param_1,undefined1 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint local_20;
  uint local_1c [2];
  
  local_20 = 0;
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_get_onu_mac_addr]input: mac_addr_num=%d\n",param_1);
  }
  if (param_1 < 0x10) {
    uVar2 = tmOnuRegRead(0x16,&local_20,param_1,&spaRegTable);
    uVar1 = tmOnuRegRead(0x17,local_1c,param_1,&spaRegTable);
    uVar1 = uVar1 | uVar2;
    if (uVar1 == 0) {
      param_2[3] = (char)(local_20 >> 0x10);
      param_2[2] = (char)(local_20 >> 0x18);
      param_2[1] = (char)local_1c[0];
      *param_2 = (char)(local_1c[0] >> 8);
      uVar2 = g_tm_debug_level;
      param_2[5] = (char)local_20;
      param_2[4] = (char)(local_20 >> 8);
      if (uVar2 < 7) {
        return 0;
      }
      printk("[TM][spa_get_onu_mac_addr]output: MacAddr = %x:%x:%x:%x:%x;%x\n",
             local_1c[0] >> 8 & 0xff,local_1c[0] & 0xff,local_20 >> 0x18,local_20 >> 0x10 & 0xff,
             local_20 >> 8 & 0xff,local_20 & 0xff);
    }
    else {
      if (g_tm_debug_level == 0) {
        return uVar1;
      }
      printk("[TM][spa_get_onu_mac_addr]read reg failed!\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_onu_mac_addr]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

