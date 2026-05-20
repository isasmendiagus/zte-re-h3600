// module: mt7915.ko
// function: ParseWebKey @ 0x11379c
// size: 356 bytes
//

undefined4 ParseWebKey(int param_1,char *param_2,int param_3,size_t param_4)

{
  void *__dest;
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  
  __dest = (void *)(param_1 + param_3 * 0x51 + 4);
  if (param_4 == 0) {
    param_4 = strlen(param_2);
  }
  switch(param_4) {
  case 5:
  case 0xd:
  case 0x10:
    __memzero(__dest,0x51);
    *(char *)(param_1 + param_3 * 0x51 + 0x54) = (char)param_4;
    memmove(__dest,param_2,param_4);
    break;
  default:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s::(keyIdx=%d):Invalid argument (arg=%s)\n","ParseWebKey",param_3,param_2);
    return 0;
  case 10:
  case 0x1a:
  case 0x20:
    pbVar2 = (byte *)(param_2 + -1);
    uVar3 = 0;
    do {
      pbVar2 = pbVar2 + 1;
      uVar3 = uVar3 + 1;
      if (((&_ctype)[*pbVar2] & 0x44) == 0) {
        return 0;
      }
    } while (uVar3 < param_4);
    __memzero(__dest,0x51);
    iVar1 = param_1 + param_3 * 0x51;
    *(char *)(iVar1 + 0x54) = (char)(param_4 >> 1);
    AtoH(param_2,__dest,param_4 >> 1);
    *(undefined1 *)(param_1 + param_3 * 0x51 + (uint)*(byte *)(iVar1 + 0x54) + 4) = 0;
  }
  if (2 < DebugLevel) {
    printk("%s::(KeyIdx=%d, Alg=0x%x)\n","ParseWebKey",param_3,*(undefined4 *)(param_1 + 0x148));
    return 1;
  }
  return 1;
}

