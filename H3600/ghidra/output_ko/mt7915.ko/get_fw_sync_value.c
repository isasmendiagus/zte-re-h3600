// module: mt7915.ko
// function: get_fw_sync_value @ 0x17695c
// size: 104 bytes
//

uint get_fw_sync_value(int param_1)

{
  uint local_c [2];
  
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x180600f0,local_c);
  local_c[0] = local_c[0] & 7;
  if (2 < DebugLevel) {
    printk("%s: current sync CR = 0x%x\n","get_fw_sync_value");
  }
  return local_c[0];
}

