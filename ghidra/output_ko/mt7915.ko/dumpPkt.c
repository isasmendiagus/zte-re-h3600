// module: mt7915.ko
// function: dumpPkt @ 0x79b90
// size: 200 bytes
//

void dumpPkt(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int extraout_r1;
  int iVar1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar2;
  uint uVar3;
  
  if (DebugLevel < 1) {
    iVar1 = param_2;
    if (param_2 < 1) {
      return;
    }
  }
  else {
    printk("--StartDump\n");
    iVar1 = extraout_r1_01;
    iVar2 = DebugLevel;
    if (param_2 < 1) goto LAB_00079bf0;
  }
  uVar3 = 0;
  iVar2 = DebugLevel;
  do {
    if (uVar3 == 0 || (uVar3 & 0xf) != 0) {
LAB_00079c18:
      if (0 < iVar2) {
        printk("%02x ",*(undefined1 *)(param_1 + uVar3));
        iVar1 = extraout_r1_00;
        iVar2 = DebugLevel;
      }
    }
    else if (0 < iVar2) {
      printk(&_LC1);
      iVar1 = extraout_r1;
      iVar2 = DebugLevel;
      goto LAB_00079c18;
    }
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < param_2);
LAB_00079bf0:
  if (0 < iVar2) {
    printk("\n--EndDump\n",iVar1,iVar2,param_4);
    return;
  }
  return;
}

