// module: mt7915.ko
// function: show_mem_proc @ 0xe1728
// size: 160 bytes
//

undefined4 show_mem_proc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 auStack_58 [68];
  
  puVar2 = auStack_58;
  iVar1 = os_str_tol(param_2,0,0x10);
  os_zero_mem(auStack_58,0x40);
  iVar3 = iVar1 - (int)puVar2;
  MtCmdMemDump(param_1,iVar1,auStack_58);
  do {
    if (0 < DebugLevel) {
      printk("addr 0x%08x: 0x%02x%02x%02x%02x\n",puVar2 + iVar3,puVar2[3],puVar2[2],puVar2[1],
             *puVar2);
    }
    puVar2 = puVar2 + 4;
  } while (puVar2 != auStack_58 + 0x40);
  return 1;
}

