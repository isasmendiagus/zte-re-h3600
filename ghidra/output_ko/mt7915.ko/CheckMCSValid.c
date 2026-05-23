// module: mt7915.ko
// function: CheckMCSValid @ 0x261d60
// size: 176 bytes
//

undefined4 CheckMCSValid(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  
  switch(param_2) {
  case 0:
    pcVar2 = &_LANCHOR1;
    break;
  case 1:
    pcVar2 = &DAT_005e1ccc;
    break;
  case 2:
  case 3:
    pcVar2 = &DAT_005e1cd8;
    break;
  case 4:
    pcVar2 = &DAT_005e1cfc;
    break;
  default:
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    printk("%s: Unrecognizable Tx Mode %d\n","CheckMCSValid",param_2,DebugLevel,param_4);
    return 0xffffffff;
  case 8:
    pcVar2 = &DAT_005e1d08;
    break;
  case 9:
    pcVar2 = &DAT_005e1d18;
  }
  iVar1 = (int)*pcVar2;
  if (iVar1 != -1) {
    do {
      if (iVar1 == param_3) {
        return 0;
      }
      pcVar2 = pcVar2 + 1;
      iVar1 = (int)*pcVar2;
    } while (iVar1 != -1);
    return 0xffffffff;
  }
  return 0xffffffff;
}

