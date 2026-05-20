// module: mt7915.ko
// function: RTMPSoftEncryptWEP @ 0x1183b4
// size: 328 bytes
//

undefined4 RTMPSoftEncryptWEP(undefined4 param_1,int param_2,byte *param_3,int param_4)

{
  byte *pbVar1;
  int local_20;
  uint local_1c;
  byte *pbVar2;
  
  local_20 = 0;
  os_alloc_mem(0,&local_20,0x108);
  if (local_20 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: ARC4_CTX Allocate memory fail!!!\n","RTMPSoftEncryptWEP");
    }
  }
  else {
    if (*(char *)(param_2 + 0x50) != '\0') {
      RTMPInitWepEngine(param_1,param_2,*(char *)(param_2 + 0x50));
      if (param_4 == 0) {
        local_1c = 0;
      }
      else {
        local_1c = 0xffffffff;
        pbVar2 = param_3;
        do {
          pbVar1 = pbVar2 + 1;
          local_1c = *(uint *)(FCSTAB_32 + ((*pbVar2 ^ local_1c) & 0xff) * 4) ^ local_1c >> 8;
          pbVar2 = pbVar1;
        } while (pbVar1 != param_3 + param_4);
        local_1c = ~local_1c;
      }
      *(uint *)(param_3 + param_4) = local_1c;
      ARC4_Compute(local_20,param_3,param_4 + 4,param_3);
      os_free_mem(local_20);
      return 1;
    }
    os_free_mem(local_20);
    if (-1 < DebugLevel) {
      printk("%s : The key is empty !\n","RTMPSoftEncryptWEP");
    }
  }
  return 0;
}

