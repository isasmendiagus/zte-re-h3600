// module: mt7915.ko
// function: Set_TxPower_Proc @ 0xd9a20
// size: 368 bytes
//

undefined4 Set_TxPower_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  cVar1 = *(char *)((int)param_1 + 0x286285);
  if (cVar1 == '\x01') {
    if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
      return 0;
    }
    uVar5 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    cVar1 = *(char *)((int)param_1 + 0x286285);
  }
  else {
    uVar5 = 0;
  }
  if (cVar1 == '\0') {
    uVar5 = HcGetBandByWdev(param_1 + 0xdb6d6);
  }
  if (0 < DebugLevel) {
    printk("%s: BandIdx = %d\n","Set_TxPower_Proc",uVar5);
  }
  if (1 < uVar5) {
    return 0;
  }
  iVar3 = simple_strtol(param_2,0,10);
  if (iVar3 < 0x65) {
    uVar2 = (undefined1)iVar3;
    if (*(char *)((int)param_1 + 0x286285) == '\x01') {
      *(undefined1 *)((int)param_1 + uVar5 + 0x794cd8) = uVar2;
      uVar4 = 1;
    }
    else if (*(char *)((int)param_1 + 0x286285) == '\0') {
      uVar4 = 1;
      *(undefined1 *)((int)param_1 + uVar5 + 0x795041) = uVar2;
      *(undefined1 *)((int)param_1 + uVar5 + 0x794cd8) = uVar2;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 0;
  }
  if (2 < DebugLevel) {
    printk("Set_TxPower_Proc: BandIdx: %d, (TxPowerPercentage=%d)\n",uVar5,
           *(undefined1 *)((int)param_1 + uVar5 + 0x794cd8));
    return uVar4;
  }
  return uVar4;
}

