// module: mt7915.ko
// function: sta_join_peer_response_matched @ 0x783d4
// size: 1432 bytes
//

bool sta_join_peer_response_matched(undefined4 param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  size_t __n;
  bool bVar11;
  bool bVar12;
  void *__s1;
  
  iVar4 = GetStaCfgByWdev();
  if (iVar4 == 0) {
    return false;
  }
  if (((*(char *)(param_3 + 0x2d) == '\0') && (*(short *)(param_2 + 0x18) == 4)) &&
     ((uint)*(byte *)(param_3 + 0xac) + (uint)*(byte *)(param_3 + 0xb9) < 0xc)) {
    return false;
  }
  __s1 = (void *)(iVar4 + 0x213303);
  iVar5 = memcmp(__s1,&ZERO_MAC_ADDR,6);
  if (iVar5 == 0) {
    bVar1 = *(byte *)(param_3 + 0x178);
    if ((bVar1 & 8) != 0) {
LAB_00078444:
      if (1 < DebugLevel) {
        printk(" hopnum is %d In Apcli ProbeRsp Join\n",bVar1 & 7);
      }
      if ((bVar1 & 7) == 0) {
        if (DebugLevel < 0) {
          return false;
        }
        printk("WARN: hopnum is 0 In Apcli ProbeRsp Join\n");
        return (bool)(bVar1 & 7);
      }
      iVar5 = memcmp(__s1,&ZERO_MAC_ADDR,6);
      if (iVar5 != 0) {
        iVar5 = memcmp(__s1,(void *)(param_3 + 6),6);
        goto LAB_00078490;
      }
    }
    bVar11 = false;
    bVar1 = 1;
  }
  else {
    iVar5 = memcmp(__s1,(void *)(param_3 + 6),6);
    if (iVar5 != 0) {
      if (DebugLevel < 0) {
        return false;
      }
      printk("ERROR: AP BSSID not equal\n");
      return false;
    }
    bVar1 = *(byte *)(param_3 + 0x178);
    if ((bVar1 & 8) != 0) goto LAB_00078444;
    iVar5 = 0;
LAB_00078490:
    bVar1 = 0;
    bVar11 = iVar5 == 0;
  }
  iVar5 = *(int *)(param_2 + 0x12e4);
  if ((iVar5 == 0) || (*(char *)(param_2 + 0x3cc8) != '\x01')) {
    bVar3 = 0;
LAB_000784c8:
    uVar10 = (uint)*(byte *)(iVar4 + 0x213395);
    if (uVar10 == 0) {
LAB_000784dc:
      if (*(byte *)(iVar4 + 0x213302) == 0) {
        bVar12 = false;
        bVar2 = false;
      }
      else {
        if ((uint)*(byte *)(param_3 + 0x2c) == (uint)*(byte *)(iVar4 + 0x213302)) {
          iVar9 = memcmp((void *)(iVar4 + 0x2132e2),(void *)(param_3 + 0xc),
                         (uint)*(byte *)(param_3 + 0x2c));
          bVar2 = iVar9 == 0;
        }
        else {
          bVar2 = false;
        }
        bVar12 = (bool)(bVar3 ^ 1);
      }
LAB_000784ec:
      if (!bVar12 && bVar1 == 1) {
        iVar5 = memcmp((void *)(iVar4 + 0x413a),(void *)(param_3 + 6),6);
        bVar12 = iVar5 == 0;
        goto LAB_00078518;
      }
      if (iVar5 != 0) goto LAB_00078724;
      goto LAB_000785f8;
    }
    __n = (size_t)*(byte *)(param_3 + 0x2c);
LAB_000785a0:
    if ((__n == uVar10) &&
       (iVar9 = memcmp((void *)(iVar4 + 0x213396),(void *)(param_3 + 0xc),__n), iVar9 == 0)) {
      iVar9 = memcmp((void *)(iVar4 + 0x2133b6),(void *)(param_3 + 6),6);
      bVar2 = true;
      bVar3 = 0;
    }
    else {
      bVar2 = false;
      iVar9 = memcmp((void *)(iVar4 + 0x2133b6),(void *)(param_3 + 6),6);
    }
    if (iVar9 != 0) {
      bVar12 = (bool)(bVar3 ^ 1);
      bVar11 = false;
      goto LAB_000784ec;
    }
    if (iVar5 == 0) {
      bVar12 = true;
      bVar11 = bVar12;
      if (bVar2 == false) goto LAB_00078748;
      goto LAB_000786ac;
    }
    if (*(char *)(param_2 + 0x3cc8) == '\x01') goto LAB_000787ac;
    bVar11 = true;
LAB_00078838:
    if ((bVar2 & bVar11) == 0) {
LAB_00078748:
      bVar12 = false;
    }
    else {
LAB_00078618:
      bVar12 = true;
      if (bVar11 != true) goto LAB_00078620;
    }
  }
  else {
    if (*(uint *)(param_2 + 0x130c) == 0) {
      bVar3 = 1;
      goto LAB_000784c8;
    }
    __n = (size_t)*(byte *)(param_3 + 0x2c);
    if ((*(uint *)(param_2 + 0x130c) != __n) ||
       (iVar9 = memcmp((void *)(param_2 + 0x1310),(void *)(param_3 + 0xc),__n), iVar9 != 0)) {
      uVar10 = (uint)*(byte *)(iVar4 + 0x213395);
      if (uVar10 != 0) goto LAB_00078788;
      bVar3 = 0;
      goto LAB_000784dc;
    }
    uVar10 = (uint)*(byte *)(iVar4 + 0x213395);
    bVar2 = true;
    if (uVar10 != 0) {
LAB_00078788:
      bVar3 = 0;
      goto LAB_000785a0;
    }
LAB_00078724:
    if (*(char *)(param_2 + 0x3cc8) != '\x01') {
LAB_000785f8:
      if (bVar1 == 0) goto LAB_00078838;
      if (bVar2 == false) goto LAB_00078748;
      bVar2 = true;
      goto LAB_00078618;
    }
    if (bVar11 != false) {
LAB_000787ac:
      bVar12 = true;
      bVar11 = true;
      goto LAB_000786ac;
    }
    if ((bVar1 & bVar2) == 0) goto LAB_00078748;
LAB_00078620:
    param_4 = param_4 + 0x918;
    uVar6 = ConvertToRssi(param_1,param_4,0);
    uVar7 = ConvertToRssi(param_1,param_4,1);
    uVar8 = ConvertToRssi(param_1,param_4,2);
    iVar5 = RTMPMaxRssi(param_1,uVar6,uVar7,uVar8);
    if (0 < DebugLevel) {
      printk("SYNC - previous Rssi = %ld current Rssi=%ld current bssid = %02x:%02x:%02x:%02x:%02x:%02x\n"
             ,*(undefined4 *)(iVar4 + 0x21239c),iVar5,*(undefined1 *)(param_3 + 6),
             *(undefined1 *)(param_3 + 7),*(undefined1 *)(param_3 + 8),*(undefined1 *)(param_3 + 9),
             *(undefined1 *)(param_3 + 10),*(undefined1 *)(param_3 + 0xb));
    }
    if (iVar5 < *(int *)(iVar4 + 0x21239c)) {
      return false;
    }
    *(int *)(iVar4 + 0x21239c) = iVar5;
    bVar12 = true;
  }
LAB_000786ac:
  if (DebugLevel < 3) {
    if (*(char *)(param_3 + 0x30) != *(char *)(iVar4 + 0x4165)) {
      return false;
    }
    return bVar12;
  }
  printk("SYNC - bssidEqualFlag=%d, ssidEqualFlag=%d, matchFlag=%d\n",bVar11,bVar2,bVar12);
LAB_00078518:
  if (*(char *)(param_3 + 0x30) != *(char *)(iVar4 + 0x4165)) {
    if (2 < DebugLevel) {
      printk("SYNC - current ie channel=%d, apcli channel=%d!\n");
    }
    return false;
  }
  return bVar12;
}

