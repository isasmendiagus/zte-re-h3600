// module: mt7915.ko
// function: vow_show_sta_dtoken @ 0x46e14
// size: 416 bytes
//

undefined4 vow_show_sta_dtoken(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  if (param_2 != (char *)0x0) {
    iVar1 = sscanf(param_2,"%u",&local_2c);
    if ((iVar1 == 0) ||
       (uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar3 <= local_2c)) {
      uVar2 = 0;
    }
    else {
      uVar3 = local_2c << 2;
      bVar8 = *(char *)(param_1 + 0xa797a4) != '\x03';
      uVar2 = 0x40388;
      if (bVar8) {
        uVar2 = 0x8388;
      }
      uVar5 = 0x40358;
      if (bVar8) {
        uVar5 = 0x8358;
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,uVar3 | 0x80000000);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_28);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,uVar3 | 0x80000001);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_24);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,uVar3 | 0x80000003);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_20);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,uVar3 | 0x80000003);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_1c);
      uVar3 = local_28;
      if (local_28 >> 0x11 != 0) {
        uVar3 = local_28 - 0x3ffff;
      }
      uVar7 = local_24;
      if (local_24 >> 0x11 != 0) {
        uVar7 = local_24 - 0x3ffff;
      }
      uVar6 = local_20;
      if (local_20 >> 0x11 != 0) {
        uVar6 = local_20 - 0x3ffff;
      }
      uVar4 = local_1c;
      if (local_1c >> 0x11 != 0) {
        uVar4 = local_1c - 0x3ffff;
      }
      if (DebugLevel < 0) {
        uVar2 = 1;
      }
      else {
        printk("Sta%d deficit token: ac0 %d(0x%08X), ac1 %d(0x%08X), ac2 %d(0x%08X), ac3 %d(0x%08X)\n"
               ,local_2c,uVar3,local_28,uVar7,local_24,uVar6,local_20,uVar4,local_1c);
        uVar2 = 1;
      }
    }
    return uVar2;
  }
  return 0;
}

