// module: mt7915.ko
// function: ConvertToSnr @ 0x10328c
// size: 108 bytes
//

int ConvertToSnr(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar2 + 0x98) == '\x01') {
    return (int)(char)((uint)(((short)param_2 * 3 + 8) * 0x100000) >> 0x18);
  }
  if (*(char *)(iVar2 + 0x98) == '\x02') {
    cVar1 = (char)((uint)(param_2 * 0x300000) >> 0x18);
  }
  else {
    iVar2 = (0xeb - param_2) * 3;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xf;
    }
    cVar1 = (char)((uint)(iVar2 << 0x14) >> 0x18);
  }
  return (int)cVar1;
}

