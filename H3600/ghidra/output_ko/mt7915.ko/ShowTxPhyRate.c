// module: mt7915.ko
// function: ShowTxPhyRate @ 0x153030
// size: 184 bytes
//

bool ShowTxPhyRate(int *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if ((uint)*(byte *)(*param_1 + 0x3c) < (uint)*(byte *)((int)param_1 + 0x2b7242)) {
    HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    uVar3 = HcGetBandByWdev(param_1 + 0xdb6d6);
    uVar1 = (uint)uVar3;
    if (uVar1 < 2) {
      if (0 < DebugLevel) {
        printk("(PHY STATE INFO)\n",(int)((ulonglong)uVar3 >> 0x20),uVar1);
      }
      if (param_3 == 0) {
        iVar2 = MtCmdPhyShowInfo(param_1,0,uVar1);
        return iVar2 == 0;
      }
    }
  }
  return false;
}

