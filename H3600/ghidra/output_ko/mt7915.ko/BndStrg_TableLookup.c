// module: mt7915.ko
// function: BndStrg_TableLookup @ 0x9ad60
// size: 128 bytes
//

char * BndStrg_TableLookup(int param_1,byte *param_2)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = *(char **)(param_1 + (uint)(byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^
                                             param_2[4] ^ param_2[5]) * 4 + 0xc14);
  while (((pcVar2 != (char *)0x0 && (*pcVar2 != '\0')) &&
         (iVar1 = memcmp(pcVar2 + 8,param_2,6), iVar1 != 0))) {
    pcVar2 = *(char **)(pcVar2 + 0x14);
  }
  return pcVar2;
}

