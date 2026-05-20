// module: mt7915.ko
// function: WscGenPSK1 @ 0x1f3880
// size: 180 bytes
//

void WscGenPSK1(undefined4 param_1,int param_2,void *param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  void *local_14 [2];
  
  local_14[0] = (void *)0x0;
  os_alloc_mem(0,local_14,0x20);
  if (local_14[0] == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s - pTempPsk alloc failed.","WscGenPSK1");
    }
  }
  else {
    if (*(char *)(param_2 + 0x1aec) == '\x04') {
      uVar2 = 2;
    }
    else {
      uVar2 = 4;
    }
    RT_HMAC_SHA256(param_2 + 0x1aed,0x20,param_2 + 0x1ae4,uVar2,local_14[0],0x20);
    pvVar1 = local_14[0];
    memmove(param_3,local_14[0],0x20);
    os_free_mem(pvVar1);
  }
  return;
}

