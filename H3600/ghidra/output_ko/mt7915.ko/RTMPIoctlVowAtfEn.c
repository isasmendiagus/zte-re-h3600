// module: mt7915.ko
// function: RTMPIoctlVowAtfEn @ 0x36784
// size: 256 bytes
//

undefined4 RTMPIoctlVowAtfEn(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined1 auStack_28 [4];
  byte *local_24;
  char acStack_20 [16];
  
  os_alloc_mem(param_1,&local_24,*(undefined2 *)(param_2 + 0x14));
  if (local_24 == (byte *)0x0) {
    return 0xfffffff4;
  }
  uVar2 = *(uint *)(param_2 + 0x10);
  uVar7 = (uint)*(ushort *)(param_2 + 0x14);
  uVar5 = *(uint *)(((uint)auStack_28 & 0xffffe000) + 8);
  uVar3 = uVar2 + uVar7;
  uVar4 = uVar3;
  if (!CARRY4(uVar2,uVar7)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(uVar2,uVar7) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar1 = __copy_from_user(local_24,uVar2,uVar7);
    if (iVar1 == 0) goto LAB_000367e4;
  }
  else {
    if (uVar7 == 0) {
LAB_000367e4:
      sprintf(acStack_20,"%d",(uint)*local_24);
      set_vow_airtime_fairness_en(param_1,acStack_20);
      if (DebugLevel < 3) {
        uVar6 = 0;
      }
      else {
        uVar6 = 0;
        printk("OID_802_11_VOW_ATF_EN(0x%08x) -> val %d\n",param_3,*local_24);
      }
      goto LAB_0003681c;
    }
    __memzero(local_24,uVar7,uVar4);
  }
  uVar6 = 0xfffffff2;
LAB_0003681c:
  os_free_mem(local_24);
  return uVar6;
}

