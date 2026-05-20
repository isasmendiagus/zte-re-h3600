// module: mt7915.ko
// function: MT_MPSTxStop @ 0x27d2cc
// size: 292 bytes
//

undefined4 MT_MPSTxStop(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  uVar3 = (uint)*(byte *)(param_1 + 0xa3ae36);
  iVar2 = net_ad_wrap_service();
  uVar4 = *(uint *)(iVar2 + uVar3 * 0xd18 + 0x4e0);
  iVar2 = net_ad_wrap_service(param_1);
  uVar5 = uVar4 & 0xfffffffd;
  iVar2 = iVar2 + uVar3 * 0xd18;
  iVar6 = *(int *)(iVar2 + 0x11cc);
  if (2 < DebugLevel) {
    printk("%s: control_band_idx:%u, Mode:%x, inuse:%x, setting_addr:%p\n","MT_MPSTxStop",uVar3,
           uVar5,*(undefined1 *)(iVar2 + 0x11c4),iVar6);
  }
  iVar1 = DebugLevel;
  if ((((uint)(iVar6 != 0) & (uVar4 ^ 0x40) >> 6) != 0) && (*(char *)(iVar2 + 0x11c4) == '\0')) {
    *(undefined4 *)(iVar2 + 0x11b8) = 0;
    if ((0 < iVar1) && (printk("%s: bf free mem %p\n","MT_MPSTxStop",iVar6), 0 < DebugLevel)) {
      printk("%s: af free mem %p\n","MT_MPSTxStop",iVar6);
    }
    os_free_mem(*(undefined4 *)(iVar2 + 0x11cc));
    *(undefined4 *)(iVar2 + 0x11cc) = 0;
  }
  iVar2 = net_ad_wrap_service(param_1);
  *(uint *)(uVar3 * 0xd18 + iVar2 + 0x4e0) = uVar5;
  return 0;
}

