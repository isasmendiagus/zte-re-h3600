// module: mt7915.ko
// function: hif_set_WPDMA @ 0x17be04
// size: 676 bytes
//

undefined4 hif_set_WPDMA(int param_1,int param_2,int param_3)

{
  int iVar1;
  int local_24;
  uint local_20;
  uint local_1c [2];
  
  local_24 = param_2;
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa0);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024208,&local_20);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025208,local_1c);
  if (local_24 == 1) {
    if (param_3 == 1) {
      local_20 = local_20 | 4;
      local_1c[0] = local_1c[0] | 4;
    }
    else {
      local_20 = local_20 & 0xfffffffb;
      local_1c[0] = local_1c[0] & 0xfffffffb;
    }
  }
  else if (local_24 == 2) {
    if (param_3 == 1) {
      local_1c[0] = local_1c[0] | 5;
      local_20 = local_20 | 5;
    }
    else {
      local_1c[0] = local_1c[0] & 0xfffffffa;
      local_20 = local_20 & 0xfffffffa;
    }
  }
  else if (local_24 == 0) {
    if (param_3 == 1) {
      local_20 = local_20 | 1;
      local_1c[0] = local_1c[0] | 1;
    }
    else {
      local_20 = local_20 & 0xfffffffe;
      local_1c[0] = local_1c[0] & 0xfffffffe;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Unknown path (%d\n","hif_set_WPDMA");
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024208,local_20);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025208,local_1c[0]);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar1 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028208,&local_20);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029208,local_1c);
    if (local_24 == 1) {
      if (param_3 == 1) {
        local_20 = local_20 | 4;
        local_1c[0] = local_1c[0] | 4;
      }
      else {
        local_20 = local_20 & 0xfffffffb;
        local_1c[0] = local_1c[0] & 0xfffffffb;
      }
    }
    else if (local_24 == 2) {
      if (param_3 == 1) {
        local_1c[0] = local_1c[0] | 5;
        local_20 = local_20 | 5;
      }
      else {
        local_1c[0] = local_1c[0] & 0xfffffffa;
        local_20 = local_20 & 0xfffffffa;
      }
    }
    else if (local_24 == 0) {
      if (param_3 == 1) {
        local_20 = local_20 | 1;
        local_1c[0] = local_1c[0] | 1;
      }
      else {
        local_20 = local_20 & 0xfffffffe;
        local_1c[0] = local_1c[0] & 0xfffffffe;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: Unknown path (%d\n","hif_set_WPDMA");
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028208,local_20);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029208,local_1c[0]);
  }
  if (param_3 == 0) {
    local_24 = -1;
  }
  mt_wlan_hook_call(9,param_1,&local_24);
  return 1;
}

