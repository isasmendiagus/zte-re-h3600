// module: mt7915.ko
// function: WPAConstructKdeHdr @ 0x11cf14
// size: 68 bytes
//

void WPAConstructKdeHdr(undefined1 param_1,char param_2,undefined1 *param_3)

{
  __memzero(param_3,6);
  param_3[1] = param_2 + '\x04';
  *param_3 = 0xdd;
  memmove(param_3 + 2,&OUI_WPA2,3);
  param_3[5] = param_1;
  return;
}

