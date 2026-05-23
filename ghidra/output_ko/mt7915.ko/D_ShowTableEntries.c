// module: mt7915.ko
// function: D_ShowTableEntries @ 0x9b480
// size: 252 bytes
//

void D_ShowTableEntries(undefined4 *param_1)

{
  undefined *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_58 [68];
  
  if (0 < DebugLevel) {
    puVar1 = &_LC13;
    if (*(char *)((int)param_1 + 0x106e) != '\x02') {
      puVar1 = &_LC14;
    }
    printk("\t%s Accessible Clients:\n",puVar1);
  }
  iVar3 = 0;
  puVar2 = param_1;
  do {
    if ((*(char *)(puVar2 + 5) != '\0') && (0 < DebugLevel)) {
      printk("\t%d: %02x:%02x:%02x:%02x:%02x:%02x Control_Flags:0x%x\n",iVar3,
             *(undefined1 *)(puVar2 + 7),*(undefined1 *)((int)puVar2 + 0x1d),
             *(undefined1 *)((int)puVar2 + 0x1e),*(undefined1 *)((int)puVar2 + 0x1f),
             *(undefined1 *)(puVar2 + 8),*(undefined1 *)((int)puVar2 + 0x21),puVar2[6]);
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 6;
  } while (iVar3 != 0x80);
  local_58[0] = 10;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_58,0x40);
  return;
}

