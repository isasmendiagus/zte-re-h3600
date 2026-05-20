// module: mt7915.ko
// function: WscGetXmlEncr @ 0x200468
// size: 320 bytes
//

undefined4 WscGetXmlEncr(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  int iVar2;
  char *__s2;
  undefined4 *puVar3;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  *param_2 = 0;
  local_1a = 0;
  local_18 = 0;
  local_16 = 0;
  local_14 = 0;
  local_12 = 0;
  iVar1 = rtstrstr(param_1,"<encryption>");
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("WscGetXmlEncr: missing %s\n","<encryption>");
    }
  }
  else {
    iVar1 = iVar1 + 0xc;
    iVar2 = rtstrstr(iVar1,"</encryption>");
    if (iVar2 == 0) {
      if (2 < DebugLevel) {
        printk("WscGetXmlEncr: missing %s\n","</encryption>");
      }
    }
    else if ((iVar2 - iVar1) - 1U < 10) {
      RTMPMoveMemory(&local_1a,iVar1);
      DAT_005f4ac0 = &DAT_005dfe20;
      puVar3 = DAT_005f4ac0;
      __s2 = DAT_005dfe20;
      while (DAT_005f4ac0 = puVar3, __s2 != (char *)0x0) {
        iVar1 = strcmp((char *)&local_1a,__s2);
        if (iVar1 == 0) {
          *param_2 = *(undefined2 *)(puVar3 + 1);
          return 1;
        }
        puVar3 = puVar3 + 2;
        __s2 = (char *)*puVar3;
      }
    }
  }
  return 0;
}

