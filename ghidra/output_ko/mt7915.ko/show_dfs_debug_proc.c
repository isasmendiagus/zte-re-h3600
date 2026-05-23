// module: mt7915.ko
// function: show_dfs_debug_proc @ 0x231708
// size: 684 bytes
//

undefined4
show_dfs_debug_proc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  sVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  if (sVar2 == 1) {
    os_zero_mem(g_radar_info,0xdec);
    if (0 < DebugLevel) {
      printk("Info clear\n");
    }
  }
  else if (sVar2 == 0) {
    if (0 < DebugLevel) {
      printk("Debug info Start\n");
    }
    iVar5 = 0;
    iVar3 = DebugLevel;
    do {
      if (0 < iVar3) {
        printk("RDD%d INFO\n",iVar5);
        iVar3 = DebugLevel;
      }
      iVar1 = iVar5 * 0x4a4;
      if (((g_radar_info[iVar1 + 1] == '\0') && (g_radar_info[iVar1 + 2] == '\0')) &&
         (g_radar_info[iVar1 + 3] == '\0')) {
        if (0 < iVar3) {
          printk("\tNo data\n");
          iVar3 = DebugLevel;
        }
      }
      else {
        if (g_radar_info[iVar5 * 0x4a4 + 6] != '\0') {
          uVar4 = 0;
          do {
            if (0 < iVar3) {
              printk(&_LC73,uVar4);
              iVar1 = (uVar4 * 3 + iVar5 * 0x129) * 4;
              iVar3 = DebugLevel;
              if (((0 < DebugLevel) &&
                  (printk(&_LC74,*(undefined4 *)(g_radar_info + iVar1 + 0x24)), iVar3 = DebugLevel,
                  0 < DebugLevel)) &&
                 (printk(&_LC74,*(undefined2 *)(g_radar_info + iVar1 + 0x28)), iVar3 = DebugLevel,
                 0 < DebugLevel)) {
                printk(&_LC39,(int)*(short *)(g_radar_info + iVar1 + 0x2a));
                iVar3 = DebugLevel;
              }
            }
            uVar4 = uVar4 + 1 & 0xff;
          } while (uVar4 < (byte)g_radar_info[iVar5 * 0x4a4 + 6]);
        }
        if (g_radar_info[iVar5 * 0x4a4 + 5] != '\0') {
          uVar4 = 0;
          do {
            if (0 < iVar3) {
              printk(&_LC73,uVar4);
              iVar1 = (uVar4 * 3 + iVar5 * 0x129) * 4;
              iVar3 = DebugLevel;
              if (((0 < DebugLevel) &&
                  (printk(&_LC74,*(undefined4 *)(g_radar_info + iVar1 + 0x1a4)), iVar3 = DebugLevel,
                  0 < DebugLevel)) &&
                 (printk(&_LC74,*(undefined2 *)(g_radar_info + iVar1 + 0x1a8)), iVar3 = DebugLevel,
                 0 < DebugLevel)) {
                printk(&_LC39,(int)*(short *)(g_radar_info + iVar1 + 0x1aa));
                iVar3 = DebugLevel;
              }
            }
            uVar4 = uVar4 + 1 & 0xff;
          } while (uVar4 < (byte)g_radar_info[iVar5 * 0x4a4 + 5]);
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 3);
    if (0 < iVar3) {
      printk("Debug info End\n");
    }
  }
  return 1;
}

