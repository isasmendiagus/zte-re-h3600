// module: mt7915.ko
// function: NICResetFromError @ 0x13ce7c
// size: 248 bytes
//

void NICResetFromError(int param_1)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar2 != 0x7628 && uVar2 != 0x7603) {
    uVar1 = 0x7606;
    bVar4 = 0x7605 < uVar2;
    bVar3 = uVar2 == 0x7606;
    if (!bVar3) {
      bVar4 = uVar2 != 0x7636;
    }
    if (!bVar4 || (bVar3 || uVar2 == 0x7637)) {
      uVar1 = 1;
    }
    if (bVar4 && (!bVar3 && uVar2 != 0x7637)) {
      uVar1 = 0;
    }
    if (uVar2 == 0x7611) {
      uVar1 = uVar1 | 1;
    }
    if (uVar1 == 0) {
      NICInitializeAdapter();
      NICInitAsicFromEEPROM(param_1);
      if (*(char *)(param_1 + 0x286285) == '\0') {
        AsicStaBbpTuning(param_1,&DAT_0036db58 + param_1);
        AsicStaBbpTuning(param_1,&DAT_00581308 + param_1);
      }
      hc_reset_radio(param_1);
      return;
    }
  }
  if (0 < DebugLevel) {
    printk("%s(): for MT7603\n","NICResetFromError");
  }
  NICInitializeAdapter(param_1);
  NICInitAsicFromEEPROM(param_1);
  RTMPEnableRxTx(param_1);
  return;
}

