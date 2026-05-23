// module: mt7915.ko
// function: RTMPIoctlGetMacTable @ 0xdce94
// size: 1292 bytes
//

void RTMPIoctlGetMacTable(int param_1,int param_2)

{
  char *pcVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  size_t sVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined *local_60;
  undefined *local_5c;
  undefined *local_58;
  undefined *local_54;
  undefined *local_50;
  undefined *local_4c;
  undefined *local_48;
  undefined *local_44;
  int local_40;
  undefined *local_3c;
  undefined *local_38;
  undefined *local_34;
  int *local_30;
  char *local_2c [2];
  
  local_30 = (int *)0x0;
  os_alloc_mem(0,&local_30,0xbbc);
  if (local_30 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","RTMPIoctlGetMacTable");
    }
  }
  else {
    __memzero(local_30,0xbbc);
    puVar8 = (undefined4 *)(param_1 + 0xa1e0c);
    *local_30 = 0;
    iVar5 = 0;
    while( true ) {
      iVar3 = HcGetMaxStaNum(param_1);
      piVar9 = local_30;
      if (iVar3 <= iVar5) break;
      if ((puVar8[-0x3b] == 0x20001) && (puVar8[4] == 2)) {
        iVar3 = *local_30;
        *(undefined1 *)(local_30 + iVar3 * 10 + 1) = *(undefined1 *)(puVar8 + -2);
        *(undefined4 *)((int)local_30 + iVar3 * 0x28 + 5) = *puVar8;
        *(undefined2 *)((int)local_30 + iVar3 * 0x28 + 9) = *(undefined2 *)(puVar8 + 1);
        *(ushort *)(local_30 + iVar3 * 10 + 3) = (ushort)*(byte *)(puVar8 + 3);
        *(undefined1 *)((int)local_30 + iVar3 * 0x28 + 0xe) = *(undefined1 *)(puVar8 + 0x283);
        *(undefined1 *)((int)local_30 + iVar3 * 0x28 + 0xf) = *(undefined1 *)(puVar8 + 0x309);
        *(undefined1 *)(local_30 + iVar3 * 10 + 4) = *(undefined1 *)(puVar8 + 8);
        *(undefined1 *)((int)local_30 + iVar3 * 0x28 + 0x11) = *(undefined1 *)((int)puVar8 + 0x21);
        *(undefined1 *)((int)local_30 + iVar3 * 0x28 + 0x12) = *(undefined1 *)((int)puVar8 + 0x22);
        local_30[iVar3 * 10 + 5] = puVar8[0x286];
        uVar2 = RTMPGetLastTxRate(param_1,puVar8 + -0x3b);
        *(undefined2 *)(piVar9 + iVar3 * 10 + 6) = uVar2;
        *local_30 = *local_30 + 1;
      }
      puVar8 = puVar8 + 0x530;
      iVar5 = iVar5 + 1;
    }
    uVar4 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 0xbbc;
    uVar7 = *(uint *)(((uint)&local_60 & 0xffffe000) + 8);
    if (uVar4 < 0xfffff444 && uVar4 + 0xbbc <= uVar7) {
      uVar7 = 0;
    }
    if (((uVar7 != 0) || (iVar5 = __copy_to_user(uVar4,local_30), iVar5 != 0)) && (2 < DebugLevel))
    {
      printk("%s: copy_to_user() fail\n","RTMPIoctlGetMacTable");
    }
    iVar5 = HcGetMaxStaNum(param_1);
    os_alloc_mem(0,local_2c,iVar5 * 0x49);
    pcVar1 = local_2c[0];
    if (local_2c[0] == (char *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s():Alloc memory failed\n","RTMPIoctlGetMacTable");
      }
    }
    else {
      iVar5 = HcGetMaxStaNum(param_1);
      if (iVar5 * 0x49 != 0) {
        __memzero(pcVar1);
      }
      pcVar1 = local_2c[0];
      local_40 = 0;
      local_2c[0][0] = '\n';
      local_2c[0][1] = '\0';
      sVar6 = strlen(local_2c[0]);
      piVar9 = (int *)(param_1 + 0xa1e1c);
      local_3c = &_LC340;
      local_38 = &_LC341;
      local_34 = &_LC342;
      local_58 = &_LC340;
      local_60 = &_LC338;
      local_5c = &_LC339;
      local_54 = &_LC341;
      local_4c = &_LC343;
      local_48 = &_LC344;
      local_50 = &_LC342;
      local_44 = &_LC345;
      sprintf(pcVar1 + sVar6,"%-14s%-4s%-4s%-4s%-4s%-6s%-6s%-10s%-10s%-10s\n",&_LC336,&_LC337);
      for (iVar5 = local_40; iVar3 = HcGetMaxStaNum(param_1), iVar5 < iVar3; iVar5 = iVar5 + 1) {
        if ((piVar9[-0x3f] == 0x20001) && (*piVar9 == 2)) {
          sVar6 = strlen(local_2c[0]);
          iVar3 = HcGetMaxStaNum(param_1);
          pcVar1 = local_2c[0];
          if ((uint)(iVar3 * 0x49) <= sVar6 + 0x49) break;
          sVar6 = strlen(local_2c[0]);
          local_60 = (undefined *)(uint)*(byte *)((int)piVar9 + -0xe);
          local_5c = (undefined *)(uint)*(byte *)((int)piVar9 + -0xd);
          local_58 = (undefined *)(uint)*(byte *)(piVar9 + -3);
          local_54 = (undefined *)(uint)*(byte *)((int)piVar9 + -0xb);
          sprintf(pcVar1 + sVar6,"%02x%02x%02x%02x%02x%02x  ",(uint)*(byte *)(piVar9 + -4),
                  (uint)*(byte *)((int)piVar9 + -0xf));
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-4d",(uint)*(byte *)(piVar9 + -6));
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-4d",(uint)*(ushort *)(piVar9 + -1));
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-4d",(uint)*(byte *)(piVar9 + 0x27f));
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-4d",piVar9[2]);
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-6d",(uint)(byte)RateIdToMbps[*(byte *)((int)piVar9 + 0xa83)]);
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-6d",0);
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-10d",0);
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-10d",0);
          pcVar1 = local_2c[0];
          sVar6 = strlen(local_2c[0]);
          sprintf(pcVar1 + sVar6,"%-10d\n",0);
        }
        piVar9 = piVar9 + 0x530;
      }
      if (2 < DebugLevel) {
        printk(&_LC351,local_2c[0]);
      }
      os_free_mem(local_2c[0]);
    }
    if (local_30 != (int *)0x0) {
      os_free_mem();
    }
  }
  return;
}

