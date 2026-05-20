// module: mt7915.ko
// function: RTMPIoctlQueryStaAid @ 0x37f08
// size: 468 bytes
//

void RTMPIoctlQueryStaAid(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_30;
  uint uStack_2c;
  uint local_28;
  uint local_24;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  byte local_17;
  byte local_16;
  byte local_15;
  uint local_14;
  
  if (*(short *)(param_2 + 0x14) != 10) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s : the length is mis-match\n","RTMPIoctlQueryStaAid");
    return;
  }
  uVar2 = *(uint *)(param_2 + 0x10);
  uVar5 = *(uint *)(((uint)&local_30 & 0xffffe000) + 8);
  uVar3 = uVar2 + 10;
  uVar4 = uVar3;
  if (uVar2 < 0xfffffff6) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (uVar2 < 0xfffffff6 && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar1 = __copy_from_user(&local_1a,uVar2,10);
    if (iVar1 == 0) {
      iVar1 = MacTableLookup(param_1,&local_1a);
      if (iVar1 == 0) {
        if (DebugLevel < 3) {
          return;
        }
        local_30 = (uint)local_17;
        uStack_2c = (uint)local_16;
        local_28 = (uint)local_15;
        printk("Query::OID_802_DOT1X_QUERY_STA_AID(%02x:%02x:%02x:%02x:%02x:%02x, Not Found)\n",
               local_1a,local_19,local_18);
        return;
      }
      *(undefined2 *)(param_2 + 0x14) = 10;
      local_14 = (uint)*(ushort *)(iVar1 + 0xf8);
      uVar4 = *(uint *)(param_2 + 0x10);
      uVar2 = *(uint *)(((uint)&local_30 & 0xffffe000) + 8);
      if (uVar4 < 0xfffffff6 && uVar4 + 10 <= uVar2) {
        uVar2 = 0;
      }
      if ((uVar2 != 0) || (iVar1 = __copy_to_user(uVar4,&local_1a,10), iVar1 != 0)) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s: copy_to_user() fail\n","RTMPIoctlQueryStaAid");
      }
      if (DebugLevel < 3) {
        return;
      }
      local_30 = (uint)local_17;
      uStack_2c = (uint)local_16;
      local_28 = (uint)local_15;
      local_24 = local_14;
      printk("Query::OID_802_DOT1X_QUERY_STA_AID(%02x:%02x:%02x:%02x:%02x:%02x, AID=%d)\n",local_1a,
             local_19,local_18);
      return;
    }
  }
  else {
    __memzero(&local_1a,10,uVar4);
  }
  if (-1 < DebugLevel) {
    printk("%s: copy_to_user() fail\n","RTMPIoctlQueryStaAid");
  }
  return;
}

