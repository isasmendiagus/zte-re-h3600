// module: mt7915.ko
// function: RTMPIoctlVendorIeRemove @ 0x3700c
// size: 388 bytes
//

uint RTMPIoctlVendorIeRemove(int *param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  
  iVar4 = *(int *)(*param_1 + 0x3c);
  local_1c = 0;
  os_alloc_mem(param_1,&local_20,*(undefined2 *)(param_2 + 0x14));
  if (local_20 == (undefined4 *)0x0) {
    return 0;
  }
  uVar1 = *(uint *)(param_2 + 0x10);
  uVar5 = (uint)*(ushort *)(param_2 + 0x14);
  uVar6 = *(uint *)(((uint)&local_28 & 0xffffe000) + 8);
  uVar2 = uVar1 + uVar5;
  uVar3 = uVar2;
  if (!CARRY4(uVar1,uVar5)) {
    uVar3 = uVar2 - (uVar6 + 1);
  }
  if (!CARRY4(uVar1,uVar5) && uVar2 <= uVar6) {
    uVar6 = 0;
  }
  if (uVar6 == 0) {
    uVar5 = __copy_from_user(local_20,uVar1,uVar5);
  }
  else if (uVar5 != 0) {
    __memzero(local_20,uVar5,uVar3);
  }
  local_1c = local_20[2];
  local_28 = local_20[1];
  local_24 = local_20 + 3;
  if ((param_3 & 0x7fff) == 3) {
    iVar4 = remove_vie(param_1,param_1 + iVar4 * 0x160d + 0xadc92,*local_20,local_1c);
    if (iVar4 != 1) goto LAB_000370d4;
    if (-1 < DebugLevel) {
      printk("%s(): OID_802_11_VENDOR_IE_REMOVE failed.\n","RTMPIoctlVendorIeRemove");
      uVar5 = 1;
      goto LAB_000370d4;
    }
  }
  else {
    iVar4 = add_vie();
    if (iVar4 != 1) goto LAB_000370d4;
    if (-1 < DebugLevel) {
      printk("%s(): OID_802_11_VENDOR_IE_ADD failed.\n","RTMPIoctlVendorIeRemove");
      uVar5 = 1;
      goto LAB_000370d4;
    }
  }
  uVar5 = 1;
LAB_000370d4:
  os_free_mem(local_20);
  return uVar5;
}

