// module: tm.ko
// function: spa_set_onu_mac_addr @ 0x39408
// size: 288 bytes
//

uint spa_set_onu_mac_addr(uint param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  uint uVar3;
  uint uVar4;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_onu_mac_addr]input: mac_addr_num=%d, MacAddr = %x:%x:%x:%x:%x;%x\n",param_1
           ,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
  }
  if (param_1 < 0x10) {
    uVar1 = *param_2;
    uVar2 = param_2[1];
    uVar4 = tmOnuRegWrite(0x16,(uint)(byte)param_2[3] << 0x10 | (uint)(byte)param_2[4] << 8 |
                               (uint)(byte)param_2[5] | (uint)(byte)param_2[2] << 0x18,param_1,
                          &spaRegTable);
    uVar3 = tmOnuRegWrite(0x17,CONCAT11(uVar1,uVar2),param_1,&spaRegTable);
    uVar3 = uVar3 | uVar4;
    if ((uVar3 == 0) || (g_tm_debug_level == 0)) {
      return uVar3;
    }
    printk("[TM][spa_set_onu_mac_addr]write reg failed!\n");
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 1;
  }
  else {
    printk("[TM][spa_set_onu_mac_addr]input invalid parameter!\n");
    uVar3 = 1;
  }
  return uVar3;
}

