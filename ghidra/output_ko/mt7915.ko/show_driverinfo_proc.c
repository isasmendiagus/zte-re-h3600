// module: mt7915.ko
// function: show_driverinfo_proc @ 0xd7fd8
// size: 196 bytes
//

undefined4 show_driverinfo_proc(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x286285);
  if (cVar1 == '\x01') {
    if (DebugLevel < 0) goto LAB_000d8018;
    printk("Driver version: %s\n","7.1.0.1");
    cVar1 = *(char *)(param_1 + 0x286285);
  }
  if (cVar1 == '\0') {
    if (DebugLevel < 0) goto LAB_000d8018;
    printk("Driver version: %s\n","7.1.0.1");
  }
  if (-1 < DebugLevel) {
    printk("FW ver: 0x%x, HW ver: 0x%x, CHIP ID: 0x%x\n",
           *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x14),
           *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x10),
           *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc));
  }
LAB_000d8018:
  show_patch_info(param_1);
  show_fw_info(param_1);
  return 1;
}

