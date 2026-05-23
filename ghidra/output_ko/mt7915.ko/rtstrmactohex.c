// module: mt7915.ko
// function: rtstrmactohex @ 0xee14c
// size: 212 bytes
//

bool rtstrmactohex(byte *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  char *pcVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  
  sVar1 = strlen((char *)param_1);
  if (sVar1 == 0x11) {
    iVar4 = 0;
    while (*param_1 != 0) {
      pcVar2 = strchr((char *)param_1,0x3a);
      iVar5 = iVar4 + 1;
      pbVar6 = (byte *)(pcVar2 + 1);
      if (pcVar2 == (char *)0x0) {
        pbVar6 = (byte *)0x0;
      }
      else {
        *pcVar2 = '\0';
      }
      sVar1 = strlen((char *)param_1);
      if (sVar1 != 2) {
        return false;
      }
      if (((&_ctype)[*param_1] & 0x44) == 0) {
        return (bool)((&_ctype)[*param_1] & 0x44);
      }
      bVar3 = (&_ctype)[param_1[1]] & 0x44;
      if (((&_ctype)[param_1[1]] & 0x44) == 0) {
        return (bool)bVar3;
      }
      AtoH(param_1,param_2 + iVar4,1,bVar3,param_4);
      if (pbVar6 == (byte *)0x0) {
        return iVar5 == 6;
      }
      iVar4 = iVar5;
      param_1 = pbVar6;
      if (iVar5 == 6) {
        return true;
      }
    }
  }
  return false;
}

