// module: mt7915.ko
// function: PMF_CalculateBIPMIC @ 0x219d24
// size: 224 bytes
//

undefined4
PMF_CalculateBIPMIC(undefined4 param_1,void *param_2,void *param_3,size_t param_4,undefined4 param_5
                   ,undefined4 *param_6)

{
  void *pvVar1;
  undefined4 uVar2;
  void *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  local_34 = 0x10;
  os_alloc_mem(0,&local_38,0x900);
  if (local_38 == (void *)0x0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("%s : out of resource.\n","PMF_CalculateBIPMIC");
    }
  }
  else {
    __memzero(local_38,0x900);
    memmove(local_38,param_2,0x14);
    pvVar1 = local_38;
    memmove((void *)((int)local_38 + 0x14),param_3,param_4);
    AES_CMAC(pvVar1,param_4 + 0x14,param_5,0x10,&local_30,&local_34);
    *param_6 = local_30;
    param_6[1] = uStack_2c;
    os_free_mem(local_38);
    uVar2 = 1;
  }
  return uVar2;
}

