// module: mt7915.ko
// function: os_alloc_mem @ 0x245640
// size: 88 bytes
//

undefined4 os_alloc_mem(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = __kmalloc(param_3,0x20,param_3,param_4,param_4);
  *param_2 = iVar1;
  if (iVar1 != 0) {
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    return 0;
  }
  wlan_dbg_set_last_error(0,2,param_3,0);
  return 1;
}

