// module: mt7915.ko
// function: MlmeCheckForFastRoaming @ 0x12fa90
// size: 668 bytes
//

undefined4 MlmeCheckForFastRoaming(undefined4 param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  void *__s1;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  int local_3c;
  
  iVar1 = GetStaCfgByWdev();
  puVar2 = (uint *)get_scan_tab_by_wdev(param_1,param_2);
  if (iVar1 != 0) {
    if (2 < DebugLevel) {
      printk("==> MlmeCheckForFastRoaming\n");
    }
    BssTableInit(iVar1 + 0x162a38);
    uVar7 = *puVar2;
    if (uVar7 == 0) {
      local_3c = DebugLevel;
    }
    else {
      uVar6 = 1;
      local_3c = DebugLevel;
      __s1 = (void *)((int)puVar2 + 0xe);
      do {
        iVar5 = (int)*(char *)((int)__s1 + 0x6b);
        if ((((-0x32 < iVar5) || (*(char *)((int)__s1 + 6) != *(char *)(param_2 + 0x1a))) &&
            (iVar3 = memcmp(__s1,(void *)(iVar1 + 0x212428),6), iVar3 != 0)) &&
           ((uint)*(byte *)(iVar1 + 0x212426) == (uint)*(byte *)((int)__s1 + 0x8e))) {
          iVar3 = memcmp((void *)((int)__s1 + 0x8f),(void *)(iVar1 + 0x212406),
                         (uint)*(byte *)(iVar1 + 0x212426));
          if (iVar3 == 0) {
            iVar3 = RTMPMaxRssi(param_1,(int)*(char *)(iVar1 + 0x2131c8),
                                (int)*(char *)(iVar1 + 0x2131c9),(int)*(char *)(iVar1 + 0x2131ca));
            if (iVar3 + 5 <= iVar5) {
              if (2 < local_3c) {
                printk("max_rssi = %d, pBss->Rssi = %d\n",iVar3,iVar5);
                local_3c = DebugLevel;
              }
              memmove((void *)(*(int *)(iVar1 + 0x162a38) * 0xaf4 + iVar1 + 0x162a38 + 8),
                      (void *)((int)__s1 + -6),0xaf4);
              *(int *)(iVar1 + 0x162a38) = *(int *)(iVar1 + 0x162a38) + 1;
              uVar7 = *puVar2;
            }
          }
        }
        uVar4 = uVar6 & 0xffff;
        bVar10 = 0xff < uVar4;
        bVar8 = uVar4 != 0x100;
        if (bVar8) {
          bVar10 = uVar6 <= uVar7;
        }
        bVar9 = uVar7 != uVar6;
        __s1 = (void *)((int)__s1 + 0xaf4);
        uVar6 = uVar6 + 1;
        if (bVar10 && (bVar8 && bVar9)) {
          uVar4 = 1;
        }
        if (!bVar10 || (!bVar8 || !bVar9)) {
          uVar4 = 0;
        }
      } while (uVar4 != 0);
    }
    if (2 < local_3c) {
      printk("<== MlmeCheckForFastRoaming (BssNr=%d)\n",*(undefined4 *)(iVar1 + 0x162a38));
    }
    if (*(int *)(iVar1 + 0x162a38) != 0) {
      cntl_connect_request(param_2,3,0,0);
    }
    return 0;
  }
  printk(&_LC14,0xb36);
  dump_stack();
  return 0;
}

