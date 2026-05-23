// module: mt7915.ko
// function: chip_show_txcmdq_info @ 0x18af58
// size: 300 bytes
//

void chip_show_txcmdq_info(int param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  uint local_28;
  uint local_24 [2];
  
  if (0 < DebugLevel) {
    printk("Nonempty TXCMD Q info:\n");
  }
  piVar2 = &DAT_0029c0c8;
  uVar1 = 0;
  do {
    local_28 = (param_2 & 1 << (uVar1 & 0xff)) >> (uVar1 & 0xff);
    if (local_28 == 0) {
      if (*piVar2 != 0) {
        local_24[0] = local_28;
        if (0 < DebugLevel) {
          printk("\t%s: ");
        }
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01b0);
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01b8,&local_28);
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01bc,local_24);
        if (0 < DebugLevel) {
          printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = 0x%03x\n",(local_28 << 4) >> 0x14,
                 local_28 & 0xfff,local_24[0] & 0xfff);
        }
      }
    }
    uVar1 = uVar1 + 1;
    piVar2 = piVar2 + 3;
  } while (uVar1 != 0x1f);
  return;
}

