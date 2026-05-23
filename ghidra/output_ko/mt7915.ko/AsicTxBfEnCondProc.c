// module: mt7915.ko
// function: AsicTxBfEnCondProc @ 0x852d0
// size: 316 bytes
//

undefined4 AsicTxBfEnCondProc(int param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar4 = 0;
  do {
    uVar3 = uVar4 & 0xffff;
    uVar1 = HcGetMaxStaNum(param_1);
    if (uVar1 <= uVar3) {
      return 1;
    }
    if (*(int *)(uVar3 * 0x14c0 + param_1 + 0xa1d20) != 0) {
      if (((*param_2 & 0x20) == 0) || (*(ushort *)(param_2 + 2) < 0xf)) {
        iVar2 = mt_WrapClientSupportsETxBF(param_1,*(undefined4 *)(param_2 + 0x14));
        bVar5 = iVar2 != 0;
        if (2 < DebugLevel) {
          printk("HT mode!\n");
          goto LAB_000853f0;
        }
      }
      else {
        iVar2 = mt_WrapClientSupportsVhtETxBF(param_1,*(undefined4 *)(param_2 + 0x18));
        bVar5 = iVar2 != 0;
        if ((2 < DebugLevel) && (printk("VHT mode!\n"), 2 < DebugLevel)) {
          printk("STA : Bfee Cap =%d, Bfer Cap =%d!\n",
                 ((uint)*(byte *)(*(int *)(param_2 + 0x18) + 1) << 0x1b) >> 0x1f,
                 ((uint)*(byte *)(*(int *)(param_2 + 0x18) + 1) << 0x1c) >> 0x1f);
LAB_000853f0:
          if (2 < DebugLevel) {
            printk("Final ETxBF status =%d!\n",bVar5);
          }
        }
      }
      if (bVar5 != false) {
        CmdTxBfTxApplyCtrl(param_1,uVar3,1,0,1,0);
      }
    }
    uVar4 = uVar4 + 1;
  } while( true );
}

