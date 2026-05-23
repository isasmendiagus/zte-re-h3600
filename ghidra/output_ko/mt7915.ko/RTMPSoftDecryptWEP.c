// module: mt7915.ko
// function: RTMPSoftDecryptWEP @ 0x118500
// size: 416 bytes
//

undefined4 RTMPSoftDecryptWEP(int param_1,uint *param_2,ushort *param_3)

{
  ushort uVar1;
  uint uVar2;
  uint *puVar3;
  ushort uVar4;
  uint *puVar5;
  int local_20;
  uint local_1c;
  
  local_20 = 0;
  os_alloc_mem(0,&local_20,0x108);
  if (local_20 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: ARC4_CTX Allocate memory fail!!!\n","RTMPSoftDecryptWEP");
      return 0;
    }
  }
  else if (*(char *)(param_1 + 0x50) == '\0') {
    os_free_mem(local_20);
    if (-1 < DebugLevel) {
      printk("%s : The key is not available !\n","RTMPSoftDecryptWEP");
      return 0;
    }
  }
  else {
    RTMPInitWepEngine(param_2,param_1,*(char *)(param_1 + 0x50));
    uVar1 = *param_3;
    if (uVar1 < 5) {
      os_free_mem(local_20);
      return 0;
    }
    uVar4 = uVar1 - 8;
    ARC4_Compute(local_20,param_2 + 1,uVar1 - 4,param_2);
    puVar5 = (uint *)((int)param_2 + (uint)uVar4);
    local_1c = *puVar5;
    if (uVar4 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
      do {
        puVar3 = (uint *)((int)param_2 + 1);
        uVar2 = *(uint *)(FCSTAB_32 + (((byte)*param_2 ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
        param_2 = puVar3;
      } while (puVar5 != puVar3);
      uVar2 = ~uVar2;
    }
    if (local_1c == uVar2) {
      *param_3 = uVar4;
      os_free_mem(local_20);
      return 1;
    }
    os_free_mem(local_20);
    if (-1 < DebugLevel) {
      printk("! WEP Data CRC Error !\n");
      return 0;
    }
  }
  return 0;
}

