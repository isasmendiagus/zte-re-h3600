// module: mt7915.ko
// function: RTMPAllocAdapterBlock @ 0x139c94
// size: 740 bytes
//

int RTMPAllocAdapterBlock(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int *local_2c [2];
  
  local_2c[0] = (int *)0x0;
  if (2 < DebugLevel) {
    printk("--> RTMPAllocAdapterBlock\n");
  }
  RtmpUtilInit();
  *param_2 = 0;
  iVar1 = AdapterBlockAllocateMemory(param_1,local_2c,0xa86c60);
  if (iVar1 == 0) {
    *(undefined1 *)(local_2c[0] + 0xa5b4e) = 2;
    local_2c[0][0x29e113] = 0;
    local_2c[0][0x29e112] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e114) = 0;
    local_2c[0][0x29e116] = 0;
    local_2c[0][0x29e115] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e117) = 0;
    local_2c[0][0x29e119] = 0;
    local_2c[0][0x29e118] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e11a) = 0;
    local_2c[0][0x29e11c] = 0;
    local_2c[0][0x29e11b] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e11d) = 0;
    local_2c[0][0x29e11f] = 0;
    local_2c[0][0x29e11e] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e120) = 0;
    local_2c[0][0x29e122] = 0;
    local_2c[0][0x29e121] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e123) = 0;
    local_2c[0][0x29e125] = 0;
    local_2c[0][0x29e124] = 0;
    *(undefined1 *)(local_2c[0] + 0x29e126) = 0;
    *local_2c[0] = param_1;
    iVar1 = DebugLevel;
    *(int **)(param_1 + 0x10) = local_2c[0];
    if (0 < iVar1) {
      printk("\n\n=== pAd = %p, size = %zu ===\n\n",local_2c[0],0xa86c60);
    }
    iVar1 = RtmpOsStatsAlloc(local_2c[0] + 0x29def0,local_2c[0] + 0x29deef);
    if (iVar1 != 0) {
      iVar1 = 0;
      local_2c[0][0x29efc3] = 0;
      local_2c[0][2] = 0;
      local_2c[0][0xa18a4] = 0;
      local_2c[0][0xa1714] = 0;
      local_2c[0][0x29efb4] = 0;
      local_2c[0][0xd9e45] = 0;
      local_2c[0][0xda1a9] = 0;
      local_2c[0][0xdb6a7] = 0;
      local_2c[0][0x1e530b] = 0;
      *param_2 = local_2c[0];
      do {
        iVar3 = iVar1 + 0x14ef89;
        iVar2 = os_alloc_mem(local_2c[0],local_2c[0] + iVar3 * 2 + 1,0x400);
        if (iVar2 == 0) {
          iVar2 = local_2c[0][iVar3 * 2 + 1];
          puVar4 = (undefined1 *)(iVar2 + -1);
          do {
            puVar4 = puVar4 + 1;
            *puVar4 = 0;
          } while (puVar4 != (undefined1 *)(iVar2 + 0x3ff));
        }
        else {
          local_2c[0][iVar3 * 2 + 1] = 0;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 != 0x100);
      hdev_ctrl_init(local_2c[0],param_3);
      wifi_sys_init(local_2c[0]);
      wpf_config_init(local_2c[0]);
      if (DebugLevel < 1) {
        return 0;
      }
      printk("<-- RTMPAllocAdapterBlock, Status=%x\n",0);
      return 0;
    }
    iVar1 = 1;
  }
  else if (-1 < DebugLevel) {
    printk("Failed to allocate memory - ADAPTER\n");
  }
  if (local_2c[0] != (int *)0x0) {
    if (local_2c[0][0x29def0] != 0) {
      os_free_mem();
      local_2c[0][0x29def0] = 0;
    }
    if (local_2c[0][0x29deef] != 0) {
      os_free_mem();
      local_2c[0][0x29deef] = 0;
    }
    RtmpOsVfree(local_2c[0]);
  }
  return iVar1;
}

