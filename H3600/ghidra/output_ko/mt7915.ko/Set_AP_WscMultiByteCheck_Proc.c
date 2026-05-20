// module: mt7915.ko
// function: Set_AP_WscMultiByteCheck_Proc @ 0x27fa8
// size: 284 bytes
//

undefined4
Set_AP_WscMultiByteCheck_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = *(uint *)(*param_1 + 0x3c) & 0xff;
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    piVar3 = param_1 + uVar4 * 0x84dec + 0xdbb8f;
    if (2 < DebugLevel) {
      printk("IF(apcli%d) Set_WscConfMode_Proc:: This command is from apcli interface now.\n",uVar4,
             DebugLevel,param_1 + uVar4 * 0x84dec,param_4);
    }
  }
  else {
    piVar3 = param_1 + uVar4 * 0x160d + 0xae14b;
    if (2 < DebugLevel) {
      printk("IF(ra%d) Set_WscConfMode_Proc:: This command is from ra interface now.\n",uVar4,
             DebugLevel,param_1 + uVar4 * 0x160d,param_4);
    }
  }
  iVar2 = strcmp(param_2,"0");
  cVar1 = '\0';
  if (iVar2 != 0) {
    iVar2 = strcmp(param_2,"1");
    if (iVar2 != 0) {
      return 0;
    }
    cVar1 = '\x01';
  }
  iVar2 = DebugLevel;
  if (*(char *)((int)piVar3 + 0x2b21) != cVar1) {
    *(char *)((int)piVar3 + 0x2b21) = cVar1;
  }
  if (iVar2 < 3) {
    return 1;
  }
  printk("IF(ra%d) Set_AP_WscMultiByteCheck_Proc::(bCheckMultiByte=%d)\n",uVar4,
         *(undefined1 *)((int)piVar3 + 0x2b21),iVar2,param_4);
  return 1;
}

