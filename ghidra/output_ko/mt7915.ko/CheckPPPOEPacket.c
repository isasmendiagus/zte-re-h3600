// module: mt7915.ko
// function: CheckPPPOEPacket @ 0x1ee38
// size: 112 bytes
//

bool CheckPPPOEPacket(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte *__s2;
  
  if (param_2 == 0) {
    return false;
  }
  iVar2 = *(int *)(param_2 + 0xcc);
  if (iVar2 == 0) {
    return false;
  }
  __s2 = (byte *)(iVar2 + 0xc);
  iVar1 = memcmp(&SNAP_802_1H,__s2,6);
  if (iVar1 == 0) {
    __s2 = (byte *)(iVar2 + 0x12);
  }
  return (ushort)(__s2[1] + 0x779d + (ushort)*__s2 * 0x100) < 2;
}

