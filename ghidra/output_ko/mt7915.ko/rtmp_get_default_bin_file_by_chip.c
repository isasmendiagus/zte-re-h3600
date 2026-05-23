// module: mt7915.ko
// function: rtmp_get_default_bin_file_by_chip @ 0x127be8
// size: 220 bytes
//

undefined4
rtmp_get_default_bin_file_by_chip
          (undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (RTMP_CHIP_E2P_FILE_TABLE._0_4_ != 0) {
    if (RTMP_CHIP_E2P_FILE_TABLE._0_4_ == param_2) {
      iVar3 = 0;
    }
    else {
      iVar2 = 0;
      do {
        iVar2 = iVar2 + 1;
        iVar3 = iVar2 * 8;
        if (*(int *)(RTMP_CHIP_E2P_FILE_TABLE + iVar2 * 8) == 0) goto LAB_00127c30;
      } while (*(int *)(RTMP_CHIP_E2P_FILE_TABLE + iVar2 * 8) != param_2);
    }
    uVar1 = *(undefined4 *)(RTMP_CHIP_E2P_FILE_TABLE + iVar3 + 4);
    *param_3 = uVar1;
    if (0 < DebugLevel) {
      printk("%s(): Found E2P bin file name:%s\n","rtmp_get_default_bin_file_by_chip",uVar1,
             DebugLevel,param_4);
      if (0 < DebugLevel) {
        printk("%s::Found E2P bin file name=%s\n","rtmp_get_default_bin_file_by_chip",*param_3,
               DebugLevel,param_4);
      }
    }
    return 1;
  }
LAB_00127c30:
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s::E2P bin file name not found\n","rtmp_get_default_bin_file_by_chip",param_3,DebugLevel,
         param_4);
  return 0;
}

