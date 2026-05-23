// module: mt7915.ko
// function: InitSkuRateDiffTable @ 0x100a84
// size: 188 bytes
//

void InitSkuRateDiffTable(int param_1)

{
  short sVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  short local_1a;
  
  chip_eeprom_read16(param_1,0xe2,&local_1a);
  pcVar3 = (char *)(param_1 + 0xa78640);
  cVar5 = (char)((ushort)local_1a >> 8);
  if ('\x1f' < cVar5) {
    cVar5 = cVar5 + -0x40;
  }
  do {
    chip_eeprom_read16(param_1,pcVar3 + (-0xa78562 - param_1),&local_1a);
    cVar2 = (char)((ushort)local_1a >> 8);
    sVar1 = local_1a;
    if ('\x1f' < (char)local_1a) {
      sVar1 = local_1a + -0x40;
    }
    if ('\x1f' < cVar2) {
      cVar2 = cVar2 + -0x40;
    }
    pcVar3[-1] = (char)sVar1 - cVar5;
    pcVar4 = pcVar3 + 2;
    *pcVar3 = cVar2 - cVar5;
    pcVar3 = pcVar4;
  } while (pcVar4 != (char *)(param_1 + 0xa78652));
  return;
}

