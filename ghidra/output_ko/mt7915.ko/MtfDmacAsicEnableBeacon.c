// module: mt7915.ko
// function: MtfDmacAsicEnableBeacon @ 0x196f7c
// size: 360 bytes
//

/* WARNING: Removing unreachable block (ram,0x00194fc4) */
/* WARNING: Removing unreachable block (ram,0x00195024) */
/* WARNING: Removing unreachable block (ram,0x00194fcc) */

undefined4 MtfDmacAsicEnableBeacon(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint local_3c [9];
  
  uVar2 = (uint)*(byte *)(param_2 + 0x29);
  uVar1 = HcGetBandByWdev(param_2);
  if (*(char *)(param_2 + 0x988) != '\x01') {
    return 1;
  }
  local_3c[0] = 0;
  local_3c[1] = 0x820f3110;
  local_3c[2] = 0x820f3118;
  local_3c[3] = 0x820f3130;
  local_3c[4] = 0x820f3138;
  local_3c[5] = 0x820f3114;
  local_3c[6] = 0x820f311c;
  local_3c[7] = 0x820f3134;
  local_3c[8] = 0x820f313c;
  if (1 < uVar1) {
    if (-1 < DebugLevel) {
      printk("%s: BandIdx >= 2\n","MtDmacAsicSetBeaconQ");
    }
    return 0;
  }
  if (uVar2 < 5) {
    uVar1 = local_3c[uVar1 * 4 + 1];
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,local_3c);
    local_3c[0] = local_3c[0] | 1 << (uVar2 + 0x10 & 0xff);
  }
  else {
    uVar1 = local_3c[uVar1 * 4 + 2];
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,local_3c);
    local_3c[0] = local_3c[0] | 1 << uVar2;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  return 1;
}

