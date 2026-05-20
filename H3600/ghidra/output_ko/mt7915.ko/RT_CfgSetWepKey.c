// module: mt7915.ko
// function: RT_CfgSetWepKey @ 0xb8864
// size: 348 bytes
//

undefined4 RT_CfgSetWepKey(undefined4 param_1,char *param_2,void *param_3,undefined4 param_4)

{
  bool bVar1;
  size_t __n;
  char *pcVar2;
  undefined1 uVar3;
  byte *pbVar4;
  int iVar5;
  
  __memzero(param_3,0x49);
  __n = strlen(param_2);
  switch(__n) {
  case 5:
  case 0xd:
  case 0x10:
    *(char *)((int)param_3 + 0x41) = (char)__n;
    memmove(param_3,param_2,__n);
    bVar1 = false;
    break;
  default:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("RT_CfgSetWepKey(keyIdx=%d):Invalid argument (arg=%s)\n",param_4,param_2);
    return 0;
  case 10:
  case 0x1a:
  case 0x20:
    pbVar4 = (byte *)(param_2 + -1);
    iVar5 = 0;
    do {
      pbVar4 = pbVar4 + 1;
      iVar5 = iVar5 + 1;
      if (((&_ctype)[*pbVar4] & 0x44) == 0) {
        return 0;
      }
    } while (iVar5 < (int)__n);
    *(char *)((int)param_3 + 0x41) = (char)((int)__n >> 1);
    AtoH(param_2,param_3);
    bVar1 = true;
  }
  if (__n == ((int)__n / 5) * 5) {
    uVar3 = 1;
  }
  else {
    uVar3 = 2;
  }
  if (__n == 0x20) {
    uVar3 = 9;
  }
  *(undefined1 *)((int)param_3 + 0x40) = uVar3;
  if (DebugLevel < 3) {
    return 1;
  }
  pcVar2 = "Hex";
  if (!bVar1) {
    pcVar2 = "Ascii";
  }
  printk("RT_CfgSetWepKey:(KeyIdx=%d,type=%s, Alg=%s)\n",param_4,pcVar2,
         *(undefined4 *)(CipherName + (uint)*(byte *)((int)param_3 + 0x40) * 4));
  return 1;
}

