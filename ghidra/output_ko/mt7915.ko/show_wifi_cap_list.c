// module: mt7915.ko
// function: show_wifi_cap_list @ 0x155c90
// size: 100 bytes
//

undefined4 show_wifi_cap_list(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (3 < DebugLevel) {
    printk("%s, chip_cap:0x%08x\n","print_wifi_chip_cap",*(undefined4 *)(param_1 + 0xa7d094),
           DebugLevel,param_4);
    if (3 < DebugLevel) {
      printk("%s, sec_cap:0x%08x\n","print_wifi_sec_cap",*(undefined4 *)(param_1 + 0xa7d098),
             DebugLevel,param_4);
    }
  }
  return 1;
}

