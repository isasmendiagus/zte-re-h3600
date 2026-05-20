// module: mt7915.ko
// function: show_devinfo_proc @ 0xe18b4
// size: 152 bytes
//

undefined4 show_devinfo_proc(int param_1,undefined4 param_2)

{
  char *pcVar1;
  
  if (0 < DebugLevel) {
    printk("Device MAC\n");
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      pcVar1 = "AP";
    }
    else {
      pcVar1 = "Unknown";
      if (*(char *)(param_1 + 0x286285) == '\0') {
        pcVar1 = "STA";
      }
    }
    if (0 < DebugLevel) {
      printk("Operation Mode: %s\n",pcVar1);
    }
  }
  show_radio_info_proc(param_1,param_2);
  return 1;
}

