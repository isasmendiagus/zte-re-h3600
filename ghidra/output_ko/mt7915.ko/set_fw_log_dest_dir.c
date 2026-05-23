// module: mt7915.ko
// function: set_fw_log_dest_dir @ 0x1d4a50
// size: 148 bytes
//

undefined4 set_fw_log_dest_dir(int param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = param_2;
  do {
    pcVar2 = pcVar2 + 1;
    if (*pcVar2 == '\0') break;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x1f);
  if (param_2[iVar1] == '/') {
    pcVar2 = "%sfw_log.bin";
  }
  else {
    pcVar2 = "%s/fw_log.bin";
  }
  snprintf((char *)(param_1 + 0xa7cc33),0x1f,pcVar2);
  if (0 < DebugLevel) {
    printk("FW Binary log destination directory: %s\n",(char *)(param_1 + 0xa7cc33));
  }
  return 1;
}

