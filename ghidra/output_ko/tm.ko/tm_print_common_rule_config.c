// module: tm.ko
// function: tm_print_common_rule_config @ 0x67714
// size: 724 bytes
//

void tm_print_common_rule_config(undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_84 [50];
  undefined1 auStack_52 [54];
  
  printk(&_LC193);
  printk("%-3s | %-8s | %-8s |  %-9s |  %-9s |  %-9s | %-9s | %-10s \n",&_LC7,"index","ruleType",
         "flowid","ruleAddr","hashAddr","extRam","extIdxRam");
  printk("--------------------------------------------------------------------------\n");
  printk("%3u | %8u | %8u | 0x%8.8x | 0x%8.8x | 0x%8.8x | 0x%8.8x | 0x%8.8x \n",param_1[2],*param_1,
         *(undefined1 *)(param_1 + 1),param_1[0x128],param_1[0x129],param_1[0x12a],param_1[299],
         param_1[300]);
  printk("ruleType        : %d \n",*(undefined1 *)(param_1 + 1));
  printk("rulePri         : %d \n",*(undefined1 *)((int)param_1 + 5));
  printk("direction       : %d \n",param_1[2]);
  uVar4 = (uint)*(byte *)(param_1 + 3);
  printk("match.entrynum  : %d \n",uVar4);
  if (uVar4 != 0) {
    puVar2 = (undefined1 *)((int)param_1 + 0x23);
    uVar3 = 0;
    do {
      puVar1 = puVar2 + -0x10;
      tm_convert_value_to_name(0,*(undefined4 *)(puVar2 + -0x13),auStack_84);
      printk("field[%d]        : %d(%s)\n",uVar3,*(undefined4 *)(puVar2 + -0x13),auStack_84);
      printk("value           :     \n");
      do {
        puVar1 = puVar1 + 1;
        printk(" 0x%02x ",*puVar1);
      } while (puVar1 != puVar2);
      printk(&_LC193);
      printk("mask            :     \n");
      puVar1 = puVar2;
      do {
        puVar1 = puVar1 + 1;
        printk(" 0x%02x ",*puVar1);
      } while (puVar1 != puVar2 + 0x10);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 0x24;
      printk(&_LC193);
    } while (uVar4 != uVar3);
  }
  printk("fwdmode         : %d \n",param_1[0x94]);
  printk("desportmsk      : %d \n",param_1[0x95]);
  printk("gemport         : %d \n",*(undefined2 *)(param_1 + 0x96));
  printk("desq            : %d \n",*(undefined1 *)((int)param_1 + 0x25a));
  uVar4 = (uint)*(byte *)(param_1 + 0x97);
  printk("actionnum       : %d \n",uVar4);
  if (uVar4 != 0) {
    puVar2 = (undefined1 *)((int)param_1 + 0x273);
    uVar3 = 0;
    do {
      puVar1 = puVar2 + -0x10;
      tm_convert_value_to_name(1,*(undefined4 *)(puVar2 + -0x13),auStack_52);
      printk("acttype[%d]      : %d(%s)\n",uVar3,*(undefined4 *)(puVar2 + -0x13),auStack_52);
      printk("value           : \n");
      do {
        puVar1 = puVar1 + 1;
        printk(" 0x%02x ",*puVar1);
      } while (puVar1 != puVar2);
      printk(&_LC193);
      printk("mask            :     \n");
      puVar1 = puVar2;
      do {
        puVar1 = puVar1 + 1;
        printk(" 0x%02x ",*puVar1);
      } while (puVar1 != puVar2 + 0x10);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 0x24;
      printk(&_LC193);
    } while (uVar4 != uVar3);
  }
  return;
}

