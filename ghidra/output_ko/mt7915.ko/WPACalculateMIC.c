// module: mt7915.ko
// function: WPACalculateMIC @ 0x11cc1c
// size: 404 bytes
//

void WPACalculateMIC(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  size_t __n;
  int local_88;
  undefined4 local_84;
  undefined1 local_80 [24];
  undefined4 local_68 [20];
  
  local_84 = 0;
  os_alloc_mem(0,&local_88,0x200);
  if (local_88 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("!!!CalculateMIC: no memory!!!\n");
    return;
  }
  MakeOutgoingFrame(local_88,&local_84,
                    CONCAT11(*(undefined1 *)(param_5 + 2),*(undefined1 *)(param_5 + 3)) + 4,param_5,
                    0xffffffff);
  __memzero(local_80,0x18);
  if (param_1 == 2) {
    RT_HMAC_SHA1(param_3,0x10,local_88,local_84,local_68,0x14);
    __n = 0x10;
  }
  else if (param_1 == 1) {
    RT_HMAC_MD5(param_3,0x10,local_88,local_84,local_80,0x10);
    __n = 0x10;
  }
  else {
    if (param_1 == 0) {
      if ((param_2 & 0x30000) != 0) {
        RT_HMAC_SHA384(param_3,0x18,local_88,local_84,local_80,0x18);
        __n = 0x18;
        goto LAB_0011ccb0;
      }
    }
    else if (param_1 != 3) {
      __n = 0x10;
      goto LAB_0011ccb0;
    }
    __n = 0x10;
    local_68[0] = 0x10;
    AES_CMAC(local_88,local_84,param_3,0x10,local_80,local_68);
  }
LAB_0011ccb0:
  memcpy((void *)(param_5 + 0x51),local_80,__n);
  os_free_mem(local_88);
  return;
}

