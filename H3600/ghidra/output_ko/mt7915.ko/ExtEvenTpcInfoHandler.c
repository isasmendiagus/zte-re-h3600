// module: mt7915.ko
// function: ExtEvenTpcInfoHandler @ 0x1a8a38
// size: 28 bytes
//

void ExtEvenTpcInfoHandler(undefined4 param_1,char *param_2)

{
  if (*param_2 == '\0') {
    EventTpcDownLinkTbl();
    return;
  }
  if (*param_2 != '\x01') {
    return;
  }
  EventTpcUpLinkTbl();
  return;
}

