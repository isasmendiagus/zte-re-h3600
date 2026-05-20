// module: mt7915.ko
// function: vow_show_bss_atoken @ 0x469f0
// size: 352 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 vow_show_bss_atoken(int param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  bool bVar7;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [8];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u",&local_34);
  if ((iVar2 != 0) && (local_34 < 0x10)) {
    bVar7 = *(char *)(param_1 + 0xa797a4) == '\x03';
    uVar3 = 0x40388;
    if (!bVar7) {
      uVar3 = 0x8388;
    }
    uVar6 = 0x8358;
    uVar1 = 0x835c;
    if (bVar7) {
      uVar6 = 0x40358;
      uVar1 = 0x4035c;
    }
    uVar4 = 0x40354;
    uVar5 = 0x40350;
    if (!bVar7) {
      uVar4 = 0x8354;
      uVar5 = 0x8350;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar3,
                   local_34 + *(int *)(param_1 + 0xa797bc) | 0x80440000);
    (*_memcpy)(0xa3d6f8);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_30);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4,&local_2c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6,auStack_28);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,auStack_24);
    if (-1 < DebugLevel) {
      printk("Group%d airtime token: max 0x%08X, min 0x%08X.\n",local_34,local_2c,local_30);
    }
    return 1;
  }
  return 0;
}

