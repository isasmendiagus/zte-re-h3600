// module: mt7915.ko
// function: WscGenPSK2 @ 0x1f3938
// size: 184 bytes
//

void WscGenPSK2(undefined4 param_1,int param_2,void *param_3)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  void *local_14 [2];
  
  local_14[0] = (void *)0x0;
  os_alloc_mem(0,local_14,0x20);
  if (local_14[0] == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s - pTempPsk alloc failed.","WscGenPSK2");
    }
  }
  else {
    if (*(char *)(param_2 + 0x1aec) == '\x04') {
      iVar2 = param_2 + 0x1ae6;
      uVar3 = 2;
    }
    else {
      iVar2 = param_2 + 0x1ae8;
      uVar3 = 4;
    }
    RT_HMAC_SHA256(param_2 + 0x1aed,0x20,iVar2,uVar3,local_14[0],0x20);
    pvVar1 = local_14[0];
    memmove(param_3,local_14[0],0x20);
    os_free_mem(pvVar1);
  }
  return;
}

