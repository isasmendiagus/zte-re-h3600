// module: mt7915.ko
// function: MlmeAutoReconnectLastSSID @ 0x129c90
// size: 548 bytes
//

void MlmeAutoReconnectLastSSID(undefined4 param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint local_44;
  undefined1 auStack_40 [36];
  
  iVar3 = GetStaCfgByWdev();
  if (iVar3 == 0) {
    printk(&_LC14,0xae9);
    dump_stack();
    return;
  }
  if (*(int *)(param_2 + 0x12e4) == 0) goto LAB_00129d48;
  if (*(char *)(param_2 + 0x3cc8) != '\0') {
    if (*(int *)(param_2 + 0x12e8) == 2) {
      cVar1 = *(char *)(param_2 + 0x1330);
    }
    else {
      if (*(int *)(param_2 + 0x12e8) != 1) goto LAB_00129cec;
      cVar1 = *(char *)(param_2 + 0x1347);
    }
    if (cVar1 != '\x01') {
      return;
    }
  }
LAB_00129cec:
  if (1 < *(int *)(param_2 + 0x12f4)) {
    iVar4 = WscSearchWpsApBySSID
                      (param_1,param_2 + 0x1310,*(undefined1 *)(param_2 + 0x130c),
                       *(undefined4 *)(param_2 + 0x12e8),param_2);
    if ((iVar4 != -1) && (*(char *)(iVar3 + 0x4060) == '\x01')) {
      iVar5 = get_scan_tab_by_wdev(param_1,param_2);
      memmove((void *)(param_2 + 0x1331),(void *)(iVar5 + iVar4 * 0xaf4 + 0xe),6);
      *(undefined1 *)(iVar3 + 0x4165) = *(undefined1 *)(iVar5 + iVar4 * 0xaf4 + 0x14);
    }
    CntlWscIterate(param_1,iVar3);
    return;
  }
LAB_00129d48:
  if (*(char *)(iVar3 + 0x213172) == '\0') {
    local_44 = (uint)*(byte *)(iVar3 + 0x4160);
    if (local_44 < 0x21) {
      if (local_44 == 0) {
LAB_00129dec:
        memmove(auStack_40,(void *)(iVar3 + 0x4140),local_44);
        cntl_connect_request(param_2,0,0x24,&local_44);
      }
      else if (0x1f < *(byte *)(iVar3 + 0x4140)) {
        pbVar6 = (byte *)(iVar3 + 0x4141);
        do {
          if (pbVar6 == (byte *)(iVar3 + 0x4140 + local_44)) goto LAB_00129dec;
          bVar2 = *pbVar6;
          pbVar6 = pbVar6 + 1;
        } while (0x1f < bVar2);
      }
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("Driver auto reconnect to last OID_802_11_BSSID setting - %02x:%02x:%02x:%02x:%02x:%02x\n"
             ,*(undefined1 *)(iVar3 + 0x413a),*(undefined1 *)(iVar3 + 0x413b),
             *(undefined1 *)(iVar3 + 0x413c),*(undefined1 *)(iVar3 + 0x413d),
             *(undefined1 *)(iVar3 + 0x413e),*(undefined1 *)(iVar3 + 0x413f));
    }
    *(undefined1 *)(iVar3 + 0x4165) = *(undefined1 *)(iVar3 + 0x1a);
    cntl_connect_request(param_2,1,6,iVar3 + 0x413a);
  }
  return;
}

