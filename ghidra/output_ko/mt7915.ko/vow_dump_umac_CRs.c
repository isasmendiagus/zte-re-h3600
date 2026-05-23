// module: mt7915.ko
// function: vow_dump_umac_CRs @ 0x423d0
// size: 104 bytes
//

void vow_dump_umac_CRs(int param_1)

{
  int iVar1;
  undefined4 local_1c [2];
  
  iVar1 = 0x8340;
  do {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar1,local_1c);
    if (2 < DebugLevel) {
      printk("0x%0x -> 0x%0x\n",iVar1,local_1c[0]);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0x83c0);
  return;
}

