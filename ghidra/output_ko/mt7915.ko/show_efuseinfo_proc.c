// module: mt7915.ko
// function: show_efuseinfo_proc @ 0x1d3954
// size: 248 bytes
//

undefined4 show_efuseinfo_proc(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort local_22;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = *(ushort *)(iVar2 + 0xf4);
  if (uVar1 != 0) {
    uVar3 = 0;
    do {
      if (0 < DebugLevel) {
        printk("offset 0x%04x: ",uVar3);
      }
      uVar4 = uVar3;
      do {
        uVar5 = uVar4 + 2;
        iVar2 = rtmp_ee_efuse_read16(param_1,uVar4,&local_22);
        if (iVar2 != 0) {
          local_22 = 0xffff;
        }
        if (0 < DebugLevel) {
          printk("%02x ",(undefined1)local_22);
          if (0 < DebugLevel) {
            printk("%02x ",local_22 >> 8);
          }
        }
        uVar4 = uVar5;
      } while (uVar5 != uVar3 + 0x10);
      if (0 < DebugLevel) {
        printk(&_LC19);
      }
      uVar3 = uVar3 + 0x10 & 0xffff;
    } while (uVar3 < uVar1);
  }
  return 1;
}

