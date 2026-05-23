// module: mt7915.ko
// function: os_load_code_from_bin @ 0x245698
// size: 176 bytes
//

void os_load_code_from_bin(int *param_1,undefined4 *param_2,undefined4 param_3,size_t *param_4)

{
  int iVar1;
  size_t *local_1c [2];
  
  iVar1 = request_firmware(local_1c,param_3,*(undefined4 *)(*param_1 + 0xc));
  if (iVar1 != 0) {
    if (-1 < DebugLevel) {
      printk("%s:fw not available(/lib/firmware/%s)\n","os_load_code_from_bin",param_3);
    }
    *param_2 = 0;
    return;
  }
  os_alloc_mem(param_1,param_2,*local_1c[0]);
  memcpy((void *)*param_2,(void *)local_1c[0][1],*local_1c[0]);
  *param_4 = *local_1c[0];
  release_firmware();
  return;
}

