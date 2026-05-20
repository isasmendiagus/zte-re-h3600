// module: mt7915.ko
// function: Dot1xIoctlRadiusData @ 0x11504c
// size: 360 bytes
//

void Dot1xIoctlRadiusData(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined1 auStack_20 [4];
  int local_1c [2];
  
  iVar4 = *param_1;
  if (2 < DebugLevel) {
    printk("%s, IF(ra%d)\n","Dot1xIoctlRadiusData",*(undefined4 *)(iVar4 + 0x3c));
  }
  if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) < *(int *)(iVar4 + 0x3c)) {
    if (-1 < DebugLevel) {
      printk("%s():Invalid MBSSID index(%d)!\n","Dot1xIoctlRadiusData");
    }
    return;
  }
  os_alloc_mem(param_1,local_1c,*(undefined2 *)(param_2 + 0x14));
  if (local_1c[0] == 0) {
    return;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar1 = __copy_from_user(local_1c[0]);
    if (iVar1 != 0) goto LAB_00115134;
  }
  else if (uVar2 != 0) {
    __memzero(local_1c[0],uVar2);
    goto LAB_00115134;
  }
  if (((param_1[*(int *)(iVar4 + 0x3c) * 0x160d + 0xadc9d] & 0x10048U) != 0) ||
     ((char)param_1[*(int *)(iVar4 + 0x3c) * 0x160d + 0xade02] == '\x01')) {
    WpaSend(param_1,local_1c[0],*(undefined2 *)(param_2 + 0x14));
  }
LAB_00115134:
  os_free_mem(local_1c[0]);
  return;
}

