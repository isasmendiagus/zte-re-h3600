// module: mt7915.ko
// function: SetATETxBfChanProfileUpdate @ 0x266964
// size: 900 bytes
//

undefined4 SetATETxBfChanProfileUpdate(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  byte *__s;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  byte bVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  short local_b0;
  char local_9a [12];
  ushort local_8e [2];
  undefined2 local_8a;
  undefined2 local_88;
  ushort local_86;
  undefined2 local_84;
  ushort local_82;
  undefined2 local_80;
  ushort local_7e;
  undefined2 local_7c;
  ushort local_7a;
  char acStack_78 [84];
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  bVar13 = *(byte *)(param_1 + 0xa5b73) >> 4;
  local_8e[0] = 0;
  local_8e[1] = 0;
  local_8a = 0;
  local_88 = 0;
  local_86 = 0;
  local_84 = 0;
  local_82 = 0;
  local_80 = 0;
  local_7e = 0;
  local_7c = 0;
  local_7a = 0;
  if ((param_2 == (char *)0x0) || (sVar3 = strlen(param_2), sVar3 != 0x2b || iVar2 == 0)) {
    return 0;
  }
  __s = (byte *)rstrtok(param_2,&_LC2);
  if (__s != (byte *)0x0) {
    iVar18 = 0;
    do {
      sVar3 = strlen((char *)__s);
      if (3 < sVar3) {
        return 0;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return 0;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return 0;
      }
      iVar17 = iVar18;
      if ((sVar3 & 1) != 0) {
        local_9a[0] = '0';
        local_9a[1] = '\0';
        strncat(local_9a,(char *)__s,sVar3);
        iVar17 = iVar18 + 1;
        AtoH(local_9a,local_8e + iVar18,2);
        local_8e[iVar18] = local_8e[iVar18] << 8 | local_8e[iVar18] >> 8;
      }
      __s = (byte *)rstrtok(0,&_LC2);
      iVar18 = iVar17;
    } while (__s != (byte *)0x0);
  }
  uVar9 = (uint)local_86;
  uVar11 = (uint)local_82;
  uVar7 = (uint)local_7e;
  uVar4 = (uint)local_7a;
  uVar10 = (int)(uVar9 << 0x13) >> 0x13 & 0xffff;
  uVar12 = (int)(uVar11 << 0x13) >> 0x13 & 0xffff;
  uVar8 = (int)(uVar7 << 0x13) >> 0x13 & 0xffff;
  uVar15 = (uint)local_8e[0];
  uVar5 = (int)(uVar4 << 0x13) >> 0x13 & 0xffff;
  uVar16 = (uint)local_8e[1];
  cVar1 = (char)local_8a;
  if (*(char *)((int)param_1 + 0x79504d) == '\0') {
    if (bVar13 != 2) {
      if (bVar13 != 3) {
LAB_00266a74:
        uVar10 = uVar5 - uVar10 & 0xffff;
        uVar14 = uVar5 - uVar12 & 0xfff;
        uVar5 = uVar5 - uVar8 & 0xffff;
        goto LAB_00266a90;
      }
LAB_00266be0:
      uVar14 = uVar8 - uVar12 & 0xfff;
      uVar10 = uVar8 - uVar10 & 0xffff;
      uVar5 = 0;
      goto LAB_00266a90;
    }
  }
  else {
    iVar2 = HcGetBandByWdev(iVar2);
    if (iVar2 == 0) {
      bVar13 = *(byte *)((int)param_1 + 0x296dce);
    }
    else {
      bVar13 = *(byte *)(param_1 + 0xa5b74);
    }
    if (bVar13 != 2) {
      if (bVar13 == 3) goto LAB_00266be0;
      if (*(char *)((int)param_1 + 0x79504d) == '\0') goto LAB_00266a74;
    }
  }
  uVar14 = 0;
  uVar10 = uVar12 - uVar10 & 0xffff;
  uVar5 = uVar14;
LAB_00266a90:
  if (0 < DebugLevel) {
    local_b0 = (short)((int)(uVar4 << 0x13) >> 0x13);
    printk("%s: i2AngleH11 = 0x%x, i2AngleH21 = 0x%x, i2AngleH31 = 0x%x, i2AngleH41 = 0x%x\n",
           "SetATETxBfChanProfileUpdate",(int)(short)((int)(uVar9 << 0x13) >> 0x13),
           (int)(short)((int)(uVar11 << 0x13) >> 0x13),(int)(short)((int)(uVar7 << 0x13) >> 0x13),
           (int)local_b0);
  }
  if (cVar1 != '\0') {
    snprintf(acStack_78,0x50,"%02x:01",uVar15);
    Set_TxBfProfileTagRead(param_1,acStack_78);
    *(byte *)((int)param_1 + 0xa786c5) = *(byte *)((int)param_1 + 0xa786c5) | 8;
    Set_TxBfProfileTagWrite(param_1,acStack_78);
  }
  if (bVar13 == 3) {
    snprintf(acStack_78,0x50,"%02x:%03x:%03x:00:%03x:00:000:00:000:00:000:00:000:00:00:00:00:00",
             uVar15,uVar16,uVar10 & 0xfff,uVar14);
  }
  else {
    snprintf(acStack_78,0x50,"%02x:%03x:%03x:00:%03x:00:%03x:00:000:00:000:00:000:00:00:00:00:00",
             uVar15,uVar16,uVar10 & 0xfff,uVar14,uVar5 & 0xfff);
  }
  if (0 < DebugLevel) {
    printk(&_LC320,"SetATETxBfChanProfileUpdate");
  }
  uVar6 = Set_TxBfProfileDataWrite(param_1,acStack_78);
  return uVar6;
}

