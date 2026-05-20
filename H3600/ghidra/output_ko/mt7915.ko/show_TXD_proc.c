// module: mt7915.ko
// function: show_TXD_proc @ 0xe16b8
// size: 252 bytes
//

undefined4 show_TXD_proc(undefined4 param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 auStack_58 [72];
  
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    uVar1 = simple_strtol(param_2,0,0x10);
    if (0xffe < uVar1) {
      return 0;
    }
    os_zero_mem(auStack_58,0x40);
    iVar2 = 0;
    puVar3 = auStack_58;
    MtCmdMemDump(param_1,uVar1 << 0x10 | 0xa0000000);
    do {
      if (0 < DebugLevel) {
        printk("DW%02d: 0x%02x%02x%02x%02x\n",iVar2 >> 2,puVar3[3],puVar3[2],puVar3[1],
               auStack_58[iVar2]);
      }
      iVar2 = iVar2 + 4;
      puVar3 = puVar3 + 4;
    } while (iVar2 != 0x40);
    asic_dump_tmac_info(param_1,auStack_58);
    return 1;
  }
  return 0;
}

