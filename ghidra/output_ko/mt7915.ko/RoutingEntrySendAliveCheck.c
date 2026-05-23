// module: mt7915.ko
// function: RoutingEntrySendAliveCheck @ 0xa1290
// size: 312 bytes
//

undefined4
RoutingEntrySendAliveCheck(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (param_4 == 0 || param_3 == 0) {
    return 0;
  }
  uVar2 = *(ushort *)(param_3 + 0x12);
  uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((((param_5 != 0 && uVar2 < uVar3) && (*(int *)(param_3 + 0x14) != 0)) &&
      (iVar4 = RoutingTabGetEntryCount(param_1,param_2), iVar4 != 0)) &&
     (puVar5 = *(undefined4 **)((uint)*(ushort *)(param_3 + 0x12) * 0x14c0 + param_1 + 0xa1d28),
     puVar5 != (undefined4 *)0x0)) {
    iVar4 = arp_create(1,0x806,*(undefined4 *)(param_3 + 0x14),*puVar5,param_5,&BROADCAST_ADDR,
                       param_4,&ZERO_MAC_ADDR);
    if (iVar4 != 0) {
      *(undefined2 *)(iVar4 + 0x42) = *(undefined2 *)(param_3 + 0x12);
      uVar1 = *(undefined1 *)(puVar5 + 3);
      *(undefined1 *)(iVar4 + 0x2f) = 0;
      *(undefined1 *)(iVar4 + 0x2d) = uVar1;
      RoutingHardTransmit(param_1,puVar5,iVar4);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: Fail to alloc memory for arp request!\n","RoutingEntrySendAliveCheck");
      return 0;
    }
  }
  return 0;
}

