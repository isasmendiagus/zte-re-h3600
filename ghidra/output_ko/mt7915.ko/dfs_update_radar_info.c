// module: mt7915.ko
// function: dfs_update_radar_info @ 0x231688
// size: 124 bytes
//

void dfs_update_radar_info(byte *param_1)

{
  int iVar1;
  
  if (param_1 == (byte *)0x0) {
    return;
  }
  if (2 < *param_1) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s() wrong parameter rdd_idx %d\n","dfs_update_radar_info");
    return;
  }
  iVar1 = (uint)*param_1 * 0x4a4;
  os_zero_mem(g_radar_info + iVar1,0x4a4);
  memcpy(g_radar_info + iVar1,param_1,0x4a4);
  return;
}

