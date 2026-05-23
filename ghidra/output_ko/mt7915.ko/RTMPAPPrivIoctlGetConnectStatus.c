// module: mt7915.ko
// function: RTMPAPPrivIoctlGetConnectStatus @ 0x15f408
// size: 1416 bytes
//

undefined4 RTMPAPPrivIoctlGetConnectStatus(int *param_1,int param_2)

{
  char cVar1;
  short sVar2;
  void *pvVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined1 auStack_30 [4];
  int local_2c;
  int local_28;
  void *local_24;
  
  iVar12 = *param_1;
  local_2c = 0;
  local_28 = 0;
  local_24 = (void *)0x0;
  if (*(int *)(iVar12 + 0x38) != 0x400) {
    return 1;
  }
  os_alloc_mem(0,&local_24,0xc4);
  if (local_24 == (void *)0x0) {
    return 1;
  }
  uVar6 = (uint)*(ushort *)(param_2 + 0x14);
  uVar9 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar6) && *(uint *)(param_2 + 0x10) + uVar6 <= uVar9) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    iVar5 = __copy_from_user(local_24);
    if (iVar5 != 0) goto LAB_0015f50c;
  }
  else if (uVar6 != 0) {
    __memzero(local_24,uVar6);
LAB_0015f50c:
    os_free_mem(local_24);
    return 1;
  }
  cVar1 = *(char *)((int)local_24 + 0xc0);
  os_zero_mem(local_24,0xc4);
  uVar6 = (uint)*(byte *)(iVar12 + 0x3c);
  if ((((1 < uVar6) || (*(char *)((int)param_1 + uVar6 * 0x2137b0 + 0x580e8e) == '\0')) ||
      (*(char *)((int)param_1 + uVar6 * 0x2137b0 + 0x57ff7e) == '\0')) ||
     (uVar9 = (uint)*(ushort *)(param_1 + uVar6 * 0x84dec + 0x16038e), 0x11f < uVar9)) {
    *(undefined4 *)((int)local_24 + 0x88) = 0;
    goto LAB_0015f4bc;
  }
  if (((param_1[uVar9 * 0x530 + 0x28787] != 2) ||
      (0x11f < *(ushort *)(param_1 + uVar9 * 0x530 + 0x28780))) ||
     (*(char *)((int)param_1 +
               (uint)*(ushort *)(param_1 + uVar9 * 0x530 + 0x28780) * 0x620 + 0x2f762) != '\x01'))
  goto LAB_0015f4bc;
  *(undefined4 *)((int)local_24 + 0x88) = 1;
  uVar7 = (uint)*(byte *)((int)param_1 + uVar6 * 0x2137b0 + 0x57ff7e);
  if (uVar7 < 0x21) {
    memcpy(local_24,(void *)((int)param_1 + uVar6 * 0x2137b0 + 0x57ff5e),uVar7);
  }
  pvVar3 = local_24;
  *(int *)((int)local_24 + 0x28) = param_1[uVar9 * 0x530 + 0x28783];
  *(short *)((int)local_24 + 0x2c) = (short)param_1[uVar9 * 0x530 + 0x28784];
  uVar4 = RTMPMaxRssi(param_1,(int)(char)param_1[uVar9 * 0x530 + 0x2878b],
                      (int)*(char *)((int)param_1 + uVar9 * 0x14c0 + 0xa1e2d),
                      (int)*(char *)((int)param_1 + uVar9 * 0x14c0 + 0xa1e2e));
  *(undefined4 *)((int)pvVar3 + 0x8c) = uVar4;
  *(undefined4 *)((int)local_24 + 0x94) = 0xffffffa1;
  *(int *)((int)local_24 + 0x90) = *(int *)((int)local_24 + 0x8c) + 0x5f;
  ZTE_GetAssocRate(param_1 + uVar9 * 0x530 + 0x28748,&local_2c);
  iVar12 = local_2c * 1000;
  *(int *)((int)local_24 + 0x98) = iVar12;
  if (cVar1 == '\0') {
    ZTE_GetRealTimeTxRxRate(param_1,param_1 + uVar9 * 0x530 + 0x28748,&local_2c,&local_28);
    iVar12 = DebugLevel;
    *(int *)((int)local_24 + 0x9c) = local_2c * 1000;
    *(int *)((int)local_24 + 0xa0) = local_28 * 1000;
    if (2 < iVar12) {
      printk("dwLastDataDownlinkRate=%d dwLastDataUplinkRate=%d\n");
    }
  }
  else {
    *(int *)((int)local_24 + 0x9c) = iVar12;
    *(int *)((int)local_24 + 0xa0) = iVar12;
  }
  uVar9 = (uint)param_1[uVar6 * 0x84dec + 0x160342] >> 7;
  if ((uVar9 == 0) && (uVar9 = 0, param_1[uVar6 * 0x84dec + 0x160342] != 0)) {
    uVar9 = 1;
  }
  uVar7 = (uint)param_1[uVar6 * 0x84dec + 0x160343] >> 7;
  if ((uVar7 == 0) && (uVar7 = 0, param_1[uVar6 * 0x84dec + 0x160343] != 0)) {
    uVar7 = 1;
  }
  *(uint *)((int)local_24 + 0xa4) = uVar9;
  *(uint *)((int)local_24 + 0xa8) = uVar7;
  *(undefined4 *)((int)local_24 + 0xac) = 10;
  *(int *)((int)local_24 + 0xbc) = param_1[uVar6 * 0x84dec + 0x160335];
  *(int *)((int)local_24 + 0xb8) = param_1[(int)(map_check_zte_ie + uVar6 * 0x84dec)];
  *(int *)((int)local_24 + 0xb0) = param_1[uVar6 * 0x84dec + 0x16033a];
  *(int *)((int)local_24 + 0xb4) = param_1[uVar6 * 0x84dec + 0x160338];
  if ((param_1[uVar6 * 0x84dec + 0xdc2b3] == 0) || (7 < (uint)param_1[uVar6 * 0x84dec + 0xdc2b4])) {
    *(undefined1 *)((int)local_24 + 0x84) = 0;
    goto LAB_0015f4bc;
  }
  *(undefined1 *)((int)local_24 + 0x84) = 1;
  iVar12 = param_1[uVar6 * 0x84dec + 0xdc2b4];
  uVar9 = (uint)*(ushort *)(&DAT_00370af8 + (int)(param_1 + uVar6 * 0x84dec + iVar12 * 0x1d));
  if (uVar9 == 0x20) {
    *(undefined4 *)((int)local_24 + 0x7c) = 3;
  }
  else {
    if (uVar9 == 0x22) {
LAB_0015f810:
      uVar9 = 6;
    }
    else if (uVar9 != 2) {
      if (2 < DebugLevel) {
        printk("GetConnectStatus: WLAN_WPA_11I. AuthType=%d\n",*(undefined4 *)((int)local_24 + 0x7c)
              );
      }
      goto LAB_0015f810;
    }
    *(uint *)((int)local_24 + 0x7c) = uVar9;
  }
  sVar2 = *(short *)(&DAT_00370afa + (int)(param_1 + uVar6 * 0x84dec + iVar12 * 0x1d));
  if (sVar2 == 8) {
    *(undefined4 *)((int)local_24 + 0x80) = 1;
  }
  else {
    if (sVar2 != 0xc) {
      if (sVar2 == 4) {
        *(undefined4 *)((int)local_24 + 0x80) = 0;
        goto LAB_0015f888;
      }
      if (2 < DebugLevel) {
        printk("GetConnectStatus, set default: TKIP_AES_MIX.EncrType=%d\n");
      }
    }
    *(undefined4 *)((int)local_24 + 0x80) = 2;
  }
LAB_0015f888:
  iVar12 = iVar12 * 0x74 + uVar6 * 0x2137b0;
  puVar8 = (undefined4 *)((int)local_24 + 0x34);
  puVar10 = (undefined4 *)((int)param_1 + (int)(&DAT_00370af8 + iVar12 + 4));
  do {
    puVar11 = puVar10 + 4;
    uVar4 = puVar10[1];
    uVar14 = puVar10[2];
    uVar13 = puVar10[3];
    *puVar8 = *puVar10;
    puVar8[1] = uVar4;
    puVar8[2] = uVar14;
    puVar8[3] = uVar13;
    puVar8 = puVar8 + 4;
    puVar10 = puVar11;
  } while (puVar11 != (undefined4 *)((int)param_1 + (int)(&DAT_00370af8 + iVar12 + 0x44)));
LAB_0015f4bc:
  uVar9 = *(uint *)(param_2 + 0x10);
  *(undefined2 *)(param_2 + 0x14) = 0xc4;
  uVar6 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
  if (uVar9 < 0xffffff3c && uVar9 + 0xc4 <= uVar6) {
    uVar6 = 0;
  }
  if ((uVar6 == 0) && (iVar12 = __copy_to_user(uVar9), iVar12 == 0)) {
    os_free_mem(local_24);
    uVar4 = 0;
  }
  else {
    os_free_mem(local_24);
    uVar4 = 1;
  }
  return uVar4;
}

