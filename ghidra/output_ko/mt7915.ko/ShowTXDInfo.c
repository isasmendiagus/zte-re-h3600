// module: mt7915.ko
// function: ShowTXDInfo @ 0xe1710
// size: 24 bytes
//

undefined4 ShowTXDInfo(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 auStack_58 [68];
  
  if (0xffe < param_2) {
    return 0;
  }
  os_zero_mem(auStack_58,0x40);
  iVar1 = 0;
  puVar2 = auStack_58;
  MtCmdMemDump(param_1,param_2 << 0x10 | 0xa0000000);
  do {
    if (0 < DebugLevel) {
      printk("DW%02d: 0x%02x%02x%02x%02x\n",iVar1 >> 2,puVar2[3],puVar2[2],puVar2[1],
             auStack_58[iVar1]);
    }
    iVar1 = iVar1 + 4;
    puVar2 = puVar2 + 4;
  } while (iVar1 != 0x40);
  asic_dump_tmac_info(param_1,auStack_58);
  return 1;
}

