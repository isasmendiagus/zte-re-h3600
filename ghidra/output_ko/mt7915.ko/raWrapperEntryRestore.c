// module: mt7915.ko
// function: raWrapperEntryRestore @ 0x1d9b70
// size: 344 bytes
//

void raWrapperEntryRestore(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = *(byte *)(param_2 + 0xbf);
  bVar1 = *(char *)(param_3 + 0x30) << 5;
  *(byte *)(param_2 + 0xbf) = bVar2 & 0x1f | bVar1;
  *(byte *)(param_2 + 0xbf) = bVar2 & 0x1b | bVar1 | (*(byte *)(param_3 + 0x32) & 1) << 2;
  *(byte *)(param_2 + 0xbf) =
       *(byte *)(param_2 + 0xbf) & 0xfd | (*(char *)(param_3 + 0x33) != '\0') << 1;
  *(ushort *)(param_2 + 0xbe) =
       *(ushort *)(param_2 + 0xbe) & 0xfe7f | (*(byte *)(param_3 + 0x34) & 3) << 7;
  bVar2 = *(byte *)(param_2 + 0xbe);
  bVar1 = (*(char *)(param_3 + 0x35) != '\0') << 6;
  *(byte *)(param_2 + 0xbe) = bVar2 & 0xbf | bVar1;
  if ((*(byte *)(param_2 + 0xbf) & 0xc0) == 0x80) {
    *(byte *)(param_2 + 0xbe) =
         bVar2 & 0x80 | bVar1 |
         *(char *)(param_3 + 0x36) + (*(char *)(param_3 + 0x37) - 1U & 3) * '\x10' & 0x3f;
  }
  else {
    *(byte *)(param_2 + 0xbe) = *(byte *)(param_2 + 0xbe) & 0xc0 | *(byte *)(param_3 + 0x36) & 0x3f;
  }
  bVar2 = *(byte *)(param_2 + 0xbd);
  bVar1 = *(char *)(param_3 + 0x39) << 5;
  *(byte *)(param_2 + 0xbd) = bVar2 & 0x1f | bVar1;
  *(byte *)(param_2 + 0xbd) = bVar2 & 0x1b | bVar1 | (*(byte *)(param_3 + 0x3b) & 1) << 2;
  *(byte *)(param_2 + 0xbd) =
       *(byte *)(param_2 + 0xbd) & 0xfd | (*(char *)(param_3 + 0x3c) != '\0') << 1;
  *(ushort *)(param_2 + 0xbc) =
       *(ushort *)(param_2 + 0xbc) & 0xfe7f | (*(byte *)(param_3 + 0x3d) & 3) << 7;
  bVar2 = *(byte *)(param_2 + 0xbc);
  bVar1 = (*(char *)(param_3 + 0x3e) != '\0') << 6;
  *(byte *)(param_2 + 0xbc) = bVar2 & 0xbf | bVar1;
  *(byte *)(param_2 + 0xbc) = bVar2 & 0x80 | bVar1 | *(byte *)(param_3 + 0x3f) & 0x3f;
  if (*(byte *)(param_3 + 0x39) - 4 < 2) {
    *(byte *)(param_2 + 0xbc) =
         *(byte *)(param_2 + 0xbc) & 0xc0 |
         *(char *)(param_3 + 0x3f) + (*(char *)(param_3 + 0x40) - 1U & 3) * '\x10' & 0x3f;
  }
  else {
    *(byte *)(param_2 + 0xbc) = *(byte *)(param_2 + 0xbc) & 0xc0 | *(byte *)(param_3 + 0x3f) & 0x3f;
  }
  *(uint *)(param_2 + 0x134) = (uint)*(ushort *)(param_2 + 0xbc);
  return;
}

