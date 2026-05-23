// module: mt7915.ko
// function: set_radar_dbg_log_config_proc @ 0x101c78
// size: 312 bytes
//

undefined4 set_radar_dbg_log_config_proc(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c;
  uint local_18;
  uint local_14 [2];
  
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 1;
  if (param_2 != (char *)0x0) {
    iVar1 = sscanf(param_2,"%u-%u-%u",&local_1c,&local_18,local_14);
    if (iVar1 == 3) {
      if (local_1c == 0) {
        *(undefined1 *)(param_1 + 0x795436) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x795436) = 1;
      }
      *(undefined1 *)(param_1 + 0x7953ee) = 1;
      *(bool *)(param_1 + 0x795437) = local_18 != 0;
      if (local_14[0] == 0) {
        *(undefined1 *)(param_1 + 0x795438) = 0;
      }
      iVar1 = DebugLevel;
      uVar2 = 1;
      if (local_14[0] == 0) {
        uVar2 = 2;
      }
      else {
        *(undefined1 *)(param_1 + 0x795438) = 1;
      }
      if (-1 < iVar1) {
        printk("%s():HWRDD_LOG_ENB = %d, SWRDD_LOG_ENB = %d SWRDD_LOG_COND = %d\n",
               "set_radar_dbg_log_config_proc",*(undefined1 *)(param_1 + 0x795436),
               *(undefined1 *)(param_1 + 0x795437),*(undefined1 *)(param_1 + 0x795438));
      }
      mtRddControl(param_1,2,0,0,uVar2);
      mt_cmd_set_rdd_log_config(param_1,local_1c & 0xff,local_18 & 0xff,local_14[0] & 0xff);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk(
            "Format Error! Please enter in the following format\nHWRDD_LOG_ENB-SWRDD_LOG_ENB-SWRDD_LOG_COND\n"
            );
    }
  }
  return 1;
}

