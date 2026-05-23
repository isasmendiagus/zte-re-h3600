// module: switch.ko
// function: set_mii_dev_name_type.part.0 @ 0x10400
// size: 52 bytes
//

void set_mii_dev_name_type_part_0(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  strncpy(g_mii_dev_name + param_1 * 0x10,param_2,0xf);
  printk("g_mii_dev_name[%d]  %s \n",param_1,g_mii_dev_name + param_1 * 0x10,param_4);
  return;
}

