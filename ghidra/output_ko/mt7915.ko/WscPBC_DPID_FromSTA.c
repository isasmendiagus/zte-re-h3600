// module: mt7915.ko
// function: WscPBC_DPID_FromSTA @ 0x1eb804
// size: 656 bytes
//

void WscPBC_DPID_FromSTA(int param_1,undefined1 *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *__s1;
  int iVar5;
  int iVar6;
  void *__s2;
  int *piVar7;
  
  iVar2 = jiffies;
  iVar6 = param_1 + 0x795000;
  cVar1 = *(char *)(iVar6 + param_3 + 0xab4);
  if (cVar1 == '\0') {
    iVar5 = param_3 << 2;
    __s1 = (void *)(param_1 + param_3 * 0x18 + 0x795ab7);
    iVar3 = 0;
LAB_001eb930:
    iVar4 = memcmp(&MTK_OUI,param_2,3);
    if (iVar4 != 0) {
      *(char *)(iVar6 + param_3 + 0xab4) = cVar1 + '\x01';
    }
    *(int *)(iVar6 + (iVar5 + iVar3) * 4 + 0xa84) = iVar2;
    *(undefined1 *)(iVar6 + iVar5 + iVar3 + 0xaff) = 1;
    memmove(__s1,param_2,6);
  }
  else {
    iVar5 = 0;
    __s1 = (void *)(param_3 * 0x18 + param_1 + 0x795ab7);
    __s2 = __s1;
    do {
      iVar3 = memcmp(param_2,__s2,6);
      if (iVar3 == 0) {
        *(int *)(param_1 + 0x790000 + (iVar5 + param_3 * 4) * 4 + 0x5a84) = iVar2;
        return;
      }
      iVar5 = iVar5 + 1;
      __s2 = (void *)((int)__s2 + 6);
    } while (iVar5 != 4);
    piVar7 = (int *)(param_1 + (param_3 + 0x795a8) * 0x10);
    iVar3 = 0;
    do {
      piVar7 = piVar7 + 1;
      if ((12000 - iVar2) + *piVar7 < 0) {
        __s1 = (void *)(param_1 + param_3 * 0x18 + iVar3 * 6 + 0x795ab7);
LAB_001eb9d4:
        iVar5 = param_3 * 4;
        if (*(char *)(iVar6 + iVar5 + iVar3 + 0xaff) != '\0') {
          *(int *)(iVar6 + (iVar5 + iVar3) * 4 + 0xa84) = iVar2;
          memmove(__s1,param_2,6);
          return;
        }
        goto LAB_001eb930;
      }
      iVar5 = memcmp(__s1,&ZERO_MAC_ADDR,6);
      if (iVar5 == 0) goto LAB_001eb9d4;
      iVar3 = iVar3 + 1;
      __s1 = (void *)((int)__s1 + 6);
    } while (iVar3 != 4);
  }
  if ((2 < DebugLevel) &&
     (printk("%s(): STA_MAC = %02x:%02x:%02x:%02x:%02x:%02x\n","WscPBC_DPID_FromSTA",*param_2,
             param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]), 2 < DebugLevel)) {
    printk("%s(): WscPBCStaProbeCount[%d] = %d\n","WscPBC_DPID_FromSTA",param_3,
           *(undefined1 *)(param_1 + 0x790000 + param_3 + 0x5ab4));
    return;
  }
  return;
}

