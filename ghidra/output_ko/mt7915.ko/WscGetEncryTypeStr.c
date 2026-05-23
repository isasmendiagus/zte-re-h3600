// module: mt7915.ko
// function: WscGetEncryTypeStr @ 0x1e5fa4
// size: 40 bytes
//

char * WscGetEncryTypeStr(int param_1)

{
  uint uVar1;
  char *pcVar2;
  
  uVar1 = param_1 - 1U & 0xffff;
  if (uVar1 < 8) {
    pcVar2 = *(char **)(&DAT_002a10d8 + uVar1 * 4);
  }
  else {
    pcVar2 = "TKIPAES";
  }
  return pcVar2;
}

