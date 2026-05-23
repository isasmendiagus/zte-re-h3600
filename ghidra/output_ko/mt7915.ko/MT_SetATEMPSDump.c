// module: mt7915.ko
// function: MT_SetATEMPSDump @ 0x28a7c4
// size: 236 bytes
//

undefined4 MT_SetATEMPSDump(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  iVar1 = net_ad_wrap_service();
  iVar1 = param_2 * 0xd18 + iVar1;
  iVar5 = *(int *)(iVar1 + 0x11cc);
  if (0 < DebugLevel) {
    printk("%s-band[%u]::\n","MT_SetATEMPSDump",param_2);
  }
  if (iVar5 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar3 = *(uint *)(iVar1 + 0x11b8);
    if (uVar3 != 0) {
      uVar6 = 1;
      do {
        uVar4 = *(uint *)(iVar5 + 0x18);
        if (0 < DebugLevel) {
          printk("Item[%d], PhyMode:%x, TxPath:%x, Rate:%x, PktLen:%u, PktCount:%u, Pwr:%x Nss:%u, Bw:%u\n"
                 ,uVar6,(uVar4 << 4) >> 0x1c,(uVar4 << 8) >> 0x10,uVar4 & 0xff,
                 *(undefined4 *)(iVar5 + 0x1c),*(undefined4 *)(iVar5 + 0x20),
                 *(undefined4 *)(iVar5 + 0x24),*(undefined4 *)(iVar5 + 0x28),
                 *(undefined4 *)(iVar5 + 0x2c));
          uVar3 = *(uint *)(iVar1 + 0x11b8);
        }
        uVar6 = uVar6 + 1;
        iVar5 = iVar5 + 0x18;
      } while (uVar6 <= uVar3);
    }
    uVar2 = 0;
  }
  return uVar2;
}

