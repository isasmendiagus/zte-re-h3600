// module: mt7915.ko
// function: RTMPIoctlQueryStaRsn @ 0x380e0
// size: 524 bytes
//

void RTMPIoctlQueryStaRsn(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_38;
  uint local_34;
  uint local_30;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  
  if (*(short *)(param_2 + 0x14) != 0x16) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s : the length is mis-match\n","RTMPIoctlQueryStaRsn");
    return;
  }
  uVar2 = *(uint *)(param_2 + 0x10);
  uVar5 = *(uint *)(((uint)&local_38 & 0xffffe000) + 8);
  uVar3 = uVar2 + 0x16;
  uVar4 = uVar3;
  if (uVar2 < 0xffffffea) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (uVar2 < 0xffffffea && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar1 = __copy_from_user(&local_26,uVar2,0x16);
    if (iVar1 == 0) {
      iVar1 = MacTableLookup(param_1,&local_26);
      if (iVar1 == 0) {
        if (DebugLevel < 3) {
          return;
        }
        local_38 = (uint)local_23;
        local_34 = (uint)local_22;
        local_30 = (uint)local_21;
        printk("Query::OID_802_DOT1X_QUERY_STA_RSN(%02x:%02x:%02x:%02x:%02x:%02x, Not Found)\n",
               local_26,local_25,local_24);
        return;
      }
      *(undefined2 *)(param_2 + 0x14) = 0x16;
      local_1c = *(undefined4 *)(iVar1 + 0x2c4);
      local_18 = *(uint *)(iVar1 + 0x3a4);
      local_20 = *(undefined4 *)(iVar1 + 0x17c);
      uVar2 = *(uint *)(((uint)&local_38 & 0xffffe000) + 8);
      local_14 = *(undefined4 *)(iVar1 + 0x563);
      uVar4 = *(uint *)(param_2 + 0x10);
      if (uVar4 < 0xffffffea && uVar4 + 0x16 <= uVar2) {
        uVar2 = 0;
      }
      if ((uVar2 != 0) || (iVar1 = __copy_to_user(uVar4,&local_26,0x16), iVar1 != 0)) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s: copy_to_user() fail\n","RTMPIoctlQueryStaRsn");
      }
      if (DebugLevel < 3) {
        return;
      }
      local_38 = (uint)local_23;
      local_34 = (uint)local_22;
      local_30 = (uint)local_21;
      printk("Query::OID_802_DOT1X_QUERY_STA_RSN(%02x:%02x:%02x:%02x:%02x:%02x)\n",local_26,local_25
             ,local_24);
      if (DebugLevel < 3) {
        return;
      }
      local_38 = local_18;
      local_34 = local_14;
      printk("%s: AKM=%x, pairwise=%x, group_cipher=%x, group_mgmt_cipher=%x\n",
             "RTMPIoctlQueryStaRsn",local_20,local_1c);
      return;
    }
  }
  else {
    __memzero(&local_26,0x16,uVar4);
  }
  if (-1 < DebugLevel) {
    printk("%s: copy_to_user() fail\n","RTMPIoctlQueryStaRsn");
  }
  return;
}

