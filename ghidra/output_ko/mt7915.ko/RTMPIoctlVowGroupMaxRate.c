// module: mt7915.ko
// function: RTMPIoctlVowGroupMaxRate @ 0x36984
// size: 324 bytes
//

undefined4 RTMPIoctlVowGroupMaxRate(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 auStack_30 [4];
  byte *local_2c;
  char acStack_28 [16];
  
  os_alloc_mem(param_1,&local_2c,*(undefined2 *)(param_2 + 0x14));
  if (local_2c == (byte *)0x0) {
    return 0xfffffff4;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar1 = __copy_from_user(local_2c);
    if (iVar1 == 0) goto LAB_000369e4;
  }
  else {
    if (uVar2 == 0) {
LAB_000369e4:
      if (*local_2c == 0) {
        uVar4 = 0;
      }
      else {
        uVar2 = 0;
        do {
          sprintf(acStack_28,"%d-%d",uVar2,(uint)*(ushort *)(local_2c + uVar2 * 2 + 2));
          set_vow_max_rate(param_1,acStack_28);
          if (2 < DebugLevel) {
            printk("OID_802_11_VOW_GROUP_MAX_RATE(0x%08x) -> val %d\n",param_3,
                   *(undefined2 *)(local_2c + uVar2 * 2 + 2));
          }
          uVar2 = uVar2 + 1 & 0xff;
        } while (uVar2 < *local_2c);
        uVar4 = 0;
      }
      goto LAB_00036a50;
    }
    __memzero(local_2c,uVar2);
  }
  uVar4 = 0xfffffff2;
LAB_00036a50:
  os_free_mem(local_2c);
  return uVar4;
}

