// module: mt7915.ko
// function: os_alloc_mem_suspend @ 0x2432d4
// size: 60 bytes
//

bool os_alloc_mem_suspend(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = __kmalloc(param_3,0xd0);
  *param_2 = iVar1;
  if (iVar1 != 0) {
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  return iVar1 == 0;
}

