// module: mt7915.ko
// function: WPA_ConstructKdeHdr @ 0x11ca80
// size: 68 bytes
//

void WPA_ConstructKdeHdr(undefined1 param_1,char param_2,undefined1 *param_3)

{
  __memzero(param_3,6);
  param_3[1] = param_2 + '\x04';
  *param_3 = 0xdd;
  memmove(param_3 + 2,&OUI_WPA2,3);
  param_3[5] = param_1;
  return;
}

