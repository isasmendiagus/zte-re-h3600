// module: mt7915.ko
// function: AddTxSStatus @ 0x1e01b4
// size: 220 bytes
//

uint AddTxSStatus(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                 undefined1 param_5,undefined2 param_6,undefined4 param_7)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  iVar2 = DebugLevel;
  pcVar4 = &DAT_002965f9 + param_1;
  uVar3 = 0;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 0xc;
    if (cVar1 == '\0') {
      iVar2 = uVar3 * 0xc + param_1;
      (&DAT_002965f4)[param_1] = (char)uVar3;
      (&UNK_00296000)[iVar2 + 0x5f8] = (char)uVar3;
      (&UNK_00296000)[iVar2 + 0x5fc] = param_4;
      (&UNK_00296000)[iVar2 + 0x5fa] = param_2;
      (&UNK_00296000)[iVar2 + 0x5fb] = param_3;
      (&UNK_00296000)[iVar2 + 0x5fd] = param_5;
      (&UNK_00296000)[iVar2 + 0x5f9] = 1;
      *(undefined2 *)(&UNK_00296000 + iVar2 + 0x5fe) = param_6;
      *(undefined4 *)(&UNK_00296000 + iVar2 + 0x600) = param_7;
      return uVar3 & 0xff;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x80);
  *(int *)(&DAT_002965f0 + param_1) = *(int *)(&DAT_002965f0 + param_1) + 1;
  if (iVar2 < 1) {
    return 0x7f;
  }
  printk("%s():Cannot get empty TxSPid, use default(%d)\n","AddTxSStatus",0x7f);
  return 0x7f;
}

