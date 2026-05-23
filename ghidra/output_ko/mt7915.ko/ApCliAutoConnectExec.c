// module: mt7915.ko
// function: ApCliAutoConnectExec @ 0x6a528
// size: 1316 bytes
//

undefined4 ApCliAutoConnectExec(int *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint *__src;
  undefined4 uVar11;
  undefined4 uVar12;
  void *__s2;
  uint uVar13;
  uint uVar14;
  uint local_4c;
  
  iVar9 = *param_1;
  iVar2 = GetStaCfgByWdev();
  if (iVar2 == 0) {
    printk(&_LC9,0x87c);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk("---> ApCliAutoConnectExec()\n");
  }
  if (param_2 == 0) {
    return 0;
  }
  uVar14 = (uint)*(byte *)(param_2 + 0xe);
  if (1 < uVar14) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Error  ifIdx=%d\n",uVar14);
    return 0;
  }
  if (*(char *)(iVar2 + 0x213356) != '\x01') {
    return 0;
  }
  bVar1 = *(byte *)(iVar2 + 0x213302);
  iVar7 = iVar2 + 0x4000;
  puVar3 = (uint *)get_scan_tab_by_wdev(param_1,param_2);
  *(undefined4 *)(iVar2 + 0x4228) = 0;
  uVar10 = *puVar3;
  iVar4 = iVar2 + 0x4228;
  local_4c = 0;
  if (uVar10 != 0) {
    __src = puVar3 + 2;
    local_4c = 0;
    if ((char)puVar3[5] != '\0') {
      local_4c = 0;
      uVar13 = 0;
      do {
        __s2 = (void *)((int)puVar3 + uVar13 * 0xaf4 + 0x9d);
        iVar5 = memcmp((void *)(iVar2 + 0x2132e2),__s2,(uint)bVar1);
        if (((iVar5 == 0) &&
            ((uint)bVar1 == (uint)(byte)puVar3[uVar13 * 0x2bd + 0x27] &&
             (byte)puVar3[uVar13 * 0x2bd + 0x27] != 0)) && (local_4c < 0x100)) {
          uVar6 = puVar3[uVar13 * 0x2bd + 0x33];
          uVar8 = *(uint *)(param_2 + 0x2c);
          if (((((uVar6 & uVar8) != 0) || (((uVar8 & 4) != 0 && ((uVar6 & 2) != 0)))) ||
              (uVar6 == 0x80 && uVar8 == 0x2000)) &&
             ((puVar3[uVar13 * 0x2bd + 0x34] & *(uint *)(param_2 + 0x174)) != 0)) {
            if ((2 < DebugLevel) &&
               (printk("Found desired ssid in Entry %2d:\n",uVar13), 2 < DebugLevel)) {
              uVar10 = (uint)(byte)puVar3[uVar13 * 0x2bd + 5];
              iVar5 = (int)*(char *)((int)puVar3 + uVar13 * 0xaf4 + 0x79);
              printk("I/F(apcli%d) ApCliAutoConnectExec:(Len=%d,Ssid=%s, Channel=%d, Rssi=%d)\n",
                     uVar14,(char)puVar3[uVar13 * 0x2bd + 0x27],__s2,uVar10,iVar5);
              if (2 < DebugLevel) {
                uVar11 = GetAuthMode((int)(char)puVar3[uVar13 * 0x2bd + 0x3b]);
                uVar12 = GetEncryptType((int)(char)puVar3[uVar13 * 0x2bd + 0x3c]);
                printk("I/F(apcli%d) ApCliAutoConnectExec::(AuthMode=%s, EncrypType=%s)\n",uVar14,
                       uVar11,uVar12,uVar10,iVar5);
              }
            }
            iVar5 = *(int *)(iVar2 + 0x4228);
            *(int *)(iVar2 + 0x4228) = iVar5 + 1;
            memmove((void *)(iVar5 * 0xaf4 + iVar4 + 8),__src,0xaf4);
            local_4c = *(uint *)(iVar2 + 0x4228);
            uVar10 = *puVar3;
          }
        }
        uVar13 = uVar13 + 1 & 0xff;
      } while ((uVar13 < uVar10) &&
              (__src = puVar3 + uVar13 * 0x2bd + 2, (char)puVar3[uVar13 * 0x2bd + 5] != '\0'));
      if (0xff < local_4c) goto LAB_0006a7b8;
    }
  }
  __memzero(local_4c * 0xaf4 + iVar4 + 8);
LAB_0006a7b8:
  BssTableSortByRssi(iVar4,1);
  if (*(int *)(iVar2 + 0x4228) == 0) {
    if (2 < DebugLevel) {
      printk("No match entry.\n");
    }
    *(undefined1 *)(iVar2 + 0x213390) = 0;
  }
  else {
    uVar10 = *(int *)(iVar2 + 0x4228) - 1;
    if (0xff < uVar10) {
      if (-1 < DebugLevel) {
        printk("Error! Out of table range: (BssNr=%d).\n");
      }
      RtmpOSNetDevProtect(1);
      uVar12 = *(undefined4 *)(iVar9 + 0x3c);
      uVar11 = *(undefined4 *)(iVar9 + 0x38);
      *(uint *)(iVar9 + 0x3c) = uVar14;
      *(undefined4 *)(iVar9 + 0x38) = 0x400;
      Set_ApCli_Enable_Proc(param_1,&_LC55);
      *(undefined4 *)(iVar9 + 0x3c) = uVar12;
      *(undefined4 *)(iVar9 + 0x38) = uVar11;
      RtmpOSNetDevProtect(0);
      if (DebugLevel < 3) {
        return 0;
      }
      printk("<--- ApCliAutoConnectExec()\n");
      return 0;
    }
    iVar2 = ApCliAutoConnectBWAdjust(param_1,param_2,iVar4 + uVar10 * 0xaf4 + 8);
    if (((iVar2 == 2) || (uVar13 = *(uint *)(iVar7 + uVar10 * 0xaf4 + 0x2f8), (uVar13 & 0x1e) == 0))
       || ((uVar13 & 0x20) != 0)) {
      if (2 < DebugLevel) {
        printk("Switch to channel :%d\n",*(undefined1 *)(uVar10 * 0xaf4 + iVar7 + 0x23c));
      }
      rtmp_set_channel(param_1,param_2,*(undefined1 *)(uVar10 * 0xaf4 + iVar7 + 0x23c));
    }
  }
  RtmpOSNetDevProtect(1);
  uVar12 = *(undefined4 *)(iVar9 + 0x3c);
  uVar11 = *(undefined4 *)(iVar9 + 0x38);
  *(uint *)(iVar9 + 0x3c) = uVar14;
  *(undefined4 *)(iVar9 + 0x38) = 0x400;
  Set_ApCli_Enable_Proc(param_1,&_LC55);
  *(undefined4 *)(iVar9 + 0x3c) = uVar12;
  *(undefined4 *)(iVar9 + 0x38) = uVar11;
  RtmpOSNetDevProtect(0);
  if (2 < DebugLevel) {
    printk("<--- ApCliAutoConnectExec()\n");
    return 1;
  }
  return 1;
}

