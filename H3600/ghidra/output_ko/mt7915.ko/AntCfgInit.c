// module: mt7915.ko
// function: AntCfgInit @ 0x13cc68
// size: 192 bytes
//

void AntCfgInit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s(%d): Not support for HIF_MT yet!\n","AntCfgInit",0xbd0);
    return;
  }
  if ((("rtmp_read_vow_parms_from_file"[param_1 + 7] & 0x10U) == 0) ||
     (("rtmp_read_vow_parms_from_file"[param_1 + 7] & 8U) == 0)) {
    "RadarStateCheck"[param_1 + 0xe] = '\0';
    "RadarStateCheck"[param_1 + 0xf] = '\x01';
  }
  else {
    "RadarStateCheck"[param_1 + 0xe] = '\x01';
    "RadarStateCheck"[param_1 + 0xf] = '\0';
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("%s: primary/secondary ant %d/%d\n","AntCfgInit","RadarStateCheck"[param_1 + 0xe],
         "RadarStateCheck"[param_1 + 0xf]);
  return;
}

