// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwpmksa @ 0x6458c
// size: 952 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwpmksa(int *param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  uint uVar6;
  void *__src;
  int iVar7;
  void *pvVar8;
  void *__src_00;
  bool bVar9;
  
  iVar2 = *param_2;
  iVar7 = *(int *)(*param_1 + 0x3c);
  if (iVar2 == 2) {
    uVar4 = param_1[iVar7 * 0x84dec + 0x1600c0];
    if (uVar4 != 0) {
      pvVar8 = (void *)param_2[1];
      uVar6 = 0;
      pvVar5 = (void *)((int)param_1 + iVar7 * 0x2137b0 + 0x5801a1);
      do {
        iVar2 = memcmp(pvVar8,pvVar5,6);
        if (iVar2 == 0) {
          __memzero(pvVar5,6);
          pvVar8 = (void *)((int)param_1 + uVar6 * 0x57 + iVar7 * 0x2137b0 + 0x5801a7);
          __memzero(pvVar8,0x10);
          uVar4 = param_1[iVar7 * 0x84dec + 0x1600c0] - 1;
          if (uVar6 < uVar4) {
            uVar6 = uVar6 + 1;
            __src = (void *)((int)param_1 + iVar7 * 0x2137b0 + 0x5801a7 + uVar6 * 0x57);
            do {
              __src_00 = (void *)((int)__src + -6);
              memmove(pvVar5,__src_00,6);
              memmove(pvVar8,__src,0x10);
              __src = (void *)((int)__src + 0x57);
              pvVar8 = (void *)((int)pvVar8 + 0x57);
              uVar4 = param_1[iVar7 * 0x84dec + 0x1600c0] - 1;
              bVar9 = uVar6 < uVar4;
              uVar6 = uVar6 + 1;
              pvVar5 = __src_00;
            } while (bVar9);
          }
          param_1[iVar7 * 0x84dec + 0x1600c0] = uVar4;
          break;
        }
        uVar6 = uVar6 + 1;
        pvVar5 = (void *)((int)pvVar5 + 0x57);
      } while (uVar6 != uVar4);
    }
    if (DebugLevel < 3) {
      return 0;
    }
    printk("rt_ioctl_siwpmksa - IW_PMKSA_REMOVE\n");
    return 0;
  }
  if (iVar2 != 3) {
    if (iVar2 == 1) {
      __memzero((int)param_1 + iVar7 * 0x2137b0 + 0x5801a1,0x15c,*param_1,iVar7 * 0x21,param_4);
      if (DebugLevel < 3) {
        return 0;
      }
      printk("rt_ioctl_siwpmksa - IW_PMKSA_FLUSH\n");
      return 0;
    }
    if (DebugLevel < 3) {
      return 0;
    }
    printk("rt_ioctl_siwpmksa - Unknow Command!!\n");
    return 0;
  }
  iVar2 = param_1[iVar7 * 0x84dec + 0x1600c0];
  if (iVar2 == 0) {
    iVar3 = 0;
  }
  else {
    pvVar8 = (void *)param_2[1];
    iVar3 = 0;
    pvVar5 = (void *)((int)param_1 + iVar7 * 0x2137b0 + 0x5801a1);
    do {
      iVar1 = memcmp(pvVar8,pvVar5,6);
      if (iVar1 == 0) break;
      iVar3 = iVar3 + 1;
      pvVar5 = (void *)((int)pvVar5 + 0x57);
    } while (iVar3 != iVar2);
    if (3 < iVar3) {
      uVar4 = *(byte *)((int)pvVar8 + 5) & 3;
      if (0 < DebugLevel) {
        printk("Update PMKID, idx = %d\n",uVar4);
        pvVar8 = (void *)param_2[1];
      }
      iVar2 = uVar4 * 0x57 + iVar7 * 0x2137b0;
      memmove((void *)((int)param_1 + iVar2 + 0x5801a1),pvVar8,6);
      memmove((void *)((int)param_1 + iVar2 + 0x5801a7),(void *)param_2[2],0x10);
      goto LAB_000646fc;
    }
  }
  if (0 < DebugLevel) {
    printk("Update PMKID, idx = %d\n",iVar3);
  }
  iVar2 = iVar3 * 0x57 + iVar7 * 0x2137b0;
  memmove((void *)((int)param_1 + iVar2 + 0x5801a1),(void *)param_2[1],6);
  memmove((void *)((int)param_1 + iVar2 + 0x5801a7),(void *)param_2[2],0x10);
  param_1[iVar7 * 0x84dec + 0x1600c0] = param_1[iVar7 * 0x84dec + 0x1600c0] + 1;
LAB_000646fc:
  if (2 < DebugLevel) {
    printk("rt_ioctl_siwpmksa - IW_PMKSA_ADD\n");
  }
  return 0;
}

