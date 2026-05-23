// module: mt7915.ko
// function: FirstBgndScanChannel @ 0x22d174
// size: 156 bytes
//

void FirstBgndScanChannel(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  code *UNRECOVERED_JUMPTABLE_00;
  
  uVar7 = *(byte *)(param_1 + 0xa78ad1) - 1;
  if ((int)uVar7 < 1) {
    return;
  }
  if (*(char *)(param_1 + 0xa78ad9) == '\x01') {
    uVar5 = 0;
    pcVar4 = (char *)(param_1 + 0xa78af1);
    do {
      uVar5 = uVar5 + 1;
      if (uVar5 == uVar7) {
                    /* WARNING: Could not recover jumptable at 0x0022d1c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE_00)();
        return;
      }
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 0x18;
    } while (cVar1 == '\x01');
    uVar7 = uVar5 & 0xff;
  }
  else {
    uVar7 = 0;
    uVar5 = uVar7;
  }
  iVar6 = param_1 + uVar5 * 0x18;
  uVar2 = *(undefined1 *)(iVar6 + 0xa78ad5);
  *(undefined1 *)(param_1 + 0xa7905c) = uVar2;
  uVar3 = *(undefined1 *)(iVar6 + 0xa78ad6);
  *(undefined1 *)(param_1 + 0xa7922e) = uVar2;
  *(char *)(param_1 + 0xa7922f) = (char)uVar7;
  *(undefined1 *)(param_1 + 0xa7905d) = uVar3;
                    /* WARNING: Could not recover jumptable at 0x0022d200. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}

