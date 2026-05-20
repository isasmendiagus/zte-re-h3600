// module: mt7915.ko
// function: OS_LOAD_CODE_FROM_BIN @ 0x2451f4
// size: 160 bytes
//

void OS_LOAD_CODE_FROM_BIN(undefined4 *param_1,undefined4 param_2,int param_3,size_t *param_4)

{
  int iVar1;
  void *__dest;
  size_t *local_14;
  
  iVar1 = request_firmware(&local_14,param_2,param_3 + 0x68);
  if (iVar1 != 0) {
    if (-1 < DebugLevel) {
      printk("%s:fw not available(/lib/firmware/%s)\n","OS_LOAD_CODE_FROM_BIN",param_2);
    }
    *param_1 = 0;
    return;
  }
  __dest = (void *)__kmalloc(*local_14,0xd0);
  *param_1 = __dest;
  memcpy(__dest,(void *)local_14[1],*local_14);
  *param_4 = *local_14;
  release_firmware();
  return;
}

