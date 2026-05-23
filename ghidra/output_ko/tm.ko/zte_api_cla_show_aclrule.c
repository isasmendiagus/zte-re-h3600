// module: tm.ko
// function: zte_api_cla_show_aclrule @ 0x6afbc
// size: 176 bytes
//

undefined4 zte_api_cla_show_aclrule(void)

{
  undefined4 *puVar1;
  undefined1 auStack_130 [100];
  undefined1 auStack_cc [192];
  
  puVar1 = g_AclFilter_Head;
  while (puVar1 != (undefined4 *)0x0) {
    __memzero(auStack_cc,0xbc);
    __memzero(auStack_130,100);
    printk("[%s] rule index=%d\n","zte_api_cla_show_aclrule",*puVar1);
    tm_cla_get_parse_info(puVar1 + 1,auStack_cc);
    tm_cla_get_oper_info(puVar1 + 1,auStack_130,auStack_cc);
    printk("[%s] output: tm rule hash addr=0x%x m_extIdxRamAddr=%d m_extRamMsk=%d\n",
           "zte_api_cla_show_aclrule",puVar1[0x12a],puVar1[300],puVar1[299]);
    puVar1 = (undefined4 *)puVar1[0x12e];
    printk("*******************************************\n");
  }
  return 0;
}

