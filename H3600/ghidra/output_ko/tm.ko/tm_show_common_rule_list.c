// module: tm.ko
// function: tm_show_common_rule_list @ 0x60db4
// size: 236 bytes
//

void tm_show_common_rule_list(void)

{
  undefined4 *puVar1;
  
  puVar1 = g_AclFilter_Head;
  printk("========== common rule ===========\n\n");
  printk("%-3s | %-8s | %-8s |  %-9s |  %-9s |  %-9s | %-9s | %-10s \n",&_LC7,"index","ruleType",
         "flowid","ruleAddr","hashAddr","extRam","extIdxRam");
  printk("--------------------------------------------------------------------------\n");
  for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)puVar1[0x12e]) {
    printk("%3u | %8u | %8u | 0x%8.8x | 0x%8.8x | 0x%8.8x | 0x%8.8x | 0x%8.8x \n",puVar1[2],*puVar1,
           *(undefined1 *)(puVar1 + 1),puVar1[0x128],puVar1[0x129],puVar1[0x12a],puVar1[299],
           puVar1[300]);
  }
  return;
}

