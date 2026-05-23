// module: switch.ko
// function: set_mii_dev_name_type @ 0x10480
// size: 32 bytes
//

void set_mii_dev_name_type(uint param_1)

{
  if (2 < param_1) {
    printk("invalid dev_type %d \n",param_1);
    return;
  }
  set_mii_dev_name_type_part_0();
  return;
}

