// module: mt7915.ko
// function: MlmeCheckPsmChange @ 0x129eb4
// size: 312 bytes
//

void MlmeCheckPsmChange(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    printk(&_LC14,0xb79);
    dump_stack();
    return;
  }
  iVar3 = *(int *)(iVar1 + 0x2124ac);
  if (*(short *)(iVar1 + 0x2124a4) != 0) {
    *(short *)(iVar1 + 0x2124a4) = *(short *)(iVar1 + 0x2124a4) + -1;
  }
  if (iVar3 != 0) {
    if (2 < DebugLevel) {
      uVar4 = *(uint *)(iVar1 + 0x212464);
      uVar2 = cntl_idle(param_2);
      printk("%s:(%d,%ld,%d,%d,%d)\n","MlmeCheckPsmChange",uVar4 & 1,iVar3,uVar2,
             *(undefined2 *)(iVar1 + 0x2124a4),*(undefined2 *)(iVar1 + 0x2124b8));
    }
    if (((((*(uint *)(iVar1 + 0x212464) & 1) != 0) && (iVar3 = cntl_idle(param_2), iVar3 != 0)) &&
        (*(short *)(iVar1 + 0x2124a4) == 0)) && (*(short *)(iVar1 + 0x2124b8) == 0)) {
      *(undefined4 *)(param_1 + 0x7960ec) = jiffies;
      *(undefined4 *)(param_1 + 0xa39e64) = 0;
      RTMP_SLEEP_FORCE_AUTO_WAKEUP(param_1,iVar1);
      return;
    }
  }
  return;
}

