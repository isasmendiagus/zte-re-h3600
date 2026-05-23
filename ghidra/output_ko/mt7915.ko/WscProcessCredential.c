// module: mt7915.ko
// function: WscProcessCredential @ 0x1f3214
// size: 1064 bytes
//

undefined4 WscProcessCredential(undefined4 param_1,uint *param_2,int param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  uint __n;
  uint uVar9;
  uint *__src;
  uint uVar10;
  uint uVar11;
  ushort uStack_2b;
  
  iVar7 = param_4 + 0x1c90;
  __memzero(iVar7,0x3a8);
  hex_dump("WscProcessCredential - PlainData",param_2,param_3);
  if (4 < param_3) {
    uVar11 = 0;
    uVar10 = 0;
LAB_001f327c:
    uVar8 = *param_2;
    uStack_2b = (ushort)(uVar8 >> 0x10);
    uVar4 = (uint)(uStack_2b >> 8);
    __n = (uStack_2b & 0xff) << 8 | uVar4;
    if (param_3 < (int)(__n + 4)) {
      if (2 < DebugLevel) {
        printk("unexpected WSC IE Length(%u)\n",__n);
      }
      goto LAB_001f3494;
    }
    param_3 = param_3 + -4;
    __src = param_2 + 1;
    uVar2 = uVar10;
    switch((uVar8 & 0xff) << 8 | uVar8 >> 8 & 0xff) {
    case 0x1003:
      param_3 = param_3 - __n;
      *(ushort *)(param_4 + uVar11 * 0x74 + 0x1cbc) =
           (ushort)param_2[1] << 8 | (ushort)param_2[1] >> 8;
      param_2 = (uint *)((int)__src + __n);
      goto joined_r0x001f362c;
    default:
      if (2 < DebugLevel) {
        printk("WscProcessCredential --> Unknown IE 0x%04x\n");
      }
      goto switchD_001f32c0_caseD_101e;
    case 0x100e:
      param_2 = __src;
      goto joined_r0x001f362c;
    case 0x100f:
      *(ushort *)(param_4 + uVar11 * 0x74 + 0x1cbe) =
           (ushort)param_2[1] << 8 | (ushort)param_2[1] >> 8;
      goto joined_r0x001f3680;
    case 0x101e:
      goto switchD_001f32c0_caseD_101e;
    case 0x1020:
      RTMPMoveMemory(iVar7 + uVar11 * 0x74 + 0x72,__src,6);
joined_r0x001f3680:
      param_3 = param_3 - __n;
      param_2 = (uint *)((int)__src + __n);
      goto joined_r0x001f362c;
    case 0x1026:
      uVar2 = uVar10 + 1 & 0xffff;
      uVar11 = uVar10;
      break;
    case 0x1027:
      if (__n == 0) goto switchD_001f32c0_caseD_101e;
      iVar3 = RTMPCheckStrPrintAble(__src,uVar4);
      if ((iVar3 == 0) && (*(char *)(param_4 + 0x2b21) != '\0')) {
        return 0;
      }
      *(short *)(param_4 + uVar11 * 0x74 + 0x1d00) = (short)__n;
      memmove((void *)(iVar7 + uVar11 * 0x74 + 0x30),__src,__n);
      break;
    case 0x1028:
      *(char *)(param_4 + uVar11 * 0x74 + 0x1d08) = (char)param_2[1];
      break;
    case 0x1045:
      uVar10 = __n;
      if (__n == 0) {
        uVar4 = 0;
      }
      else if ((char)param_2[1] == '\0') {
        uVar4 = 0;
        uVar10 = 0;
      }
      else {
        uVar8 = 0;
        pcVar6 = (char *)((int)param_2 + 5);
        do {
          uVar9 = uVar8 + 1;
          uVar8 = uVar9 & 0xffff;
          if (uVar8 == __n) goto LAB_001f3418;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        uVar4 = uVar9 & 0xff;
        uVar10 = uVar8;
      }
LAB_001f3418:
      *(uint *)(param_4 + 0x1000 + uVar11 * 0x74 + 0xc98) = uVar10;
      iVar3 = RTMPCheckStrPrintAble(__src,uVar4);
      if ((iVar3 == 0) && (*(char *)(param_4 + 0x2b21) != '\0')) {
        return 0;
      }
      memmove((void *)(iVar7 + uVar11 * 0x74 + 0xc),__src,
              *(size_t *)(param_4 + 0x1000 + uVar11 * 0x74 + 0xc98));
      goto switchD_001f32c0_caseD_101e;
    }
    goto joined_r0x001f362c;
  }
  uVar10 = 0;
  *(undefined4 *)(param_4 + 0x1c90) = 0;
  goto LAB_001f36d4;
switchD_001f32c0_caseD_101e:
joined_r0x001f362c:
  param_3 = param_3 - __n;
  param_2 = (uint *)((int)__src + __n);
  uVar10 = uVar2;
joined_r0x001f362c:
  if (param_3 < 5) goto LAB_001f3494;
  goto LAB_001f327c;
LAB_001f3494:
  *(uint *)(param_4 + 0x1c90) = uVar10;
  if ((*(char *)(param_4 + 0x2b31) != '\0') && (uVar10 != 0)) {
    bVar5 = false;
    uVar11 = 0;
    do {
      if (*(short *)(param_4 + uVar11 * 0x74 + 0x1cbe) == 2) {
        __memzero(iVar7,0x3a8);
        bVar5 = true;
      }
      uVar11 = uVar11 + 1 & 0xffff;
    } while (uVar11 < *(uint *)(param_4 + 0x1c90));
    if (bVar5) {
      return 0;
    }
  }
LAB_001f36d4:
  if (2 < DebugLevel) {
    printk("WscProcessCredential --> %d profile retrieved from credential\n",uVar10);
  }
  return 1;
}

