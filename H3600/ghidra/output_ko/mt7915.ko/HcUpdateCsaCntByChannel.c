// module: mt7915.ko
// function: HcUpdateCsaCntByChannel @ 0xa9240
// size: 228 bytes
//

undefined4
HcUpdateCsaCntByChannel(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = RcGetHdevByChannel(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): Update Channel %d faild, not support this RF\n","HcUpdateCsaCntByChannel",
             param_2,DebugLevel,param_4);
    }
    return 0xffffffff;
  }
  piVar3 = *(int **)(iVar1 + 0xc);
  do {
    if ((int *)(iVar1 + 0xc) == piVar3) {
      return 0;
    }
    iVar2 = *(int *)(param_1 + (uint)*(byte *)(piVar3 + -5) * 4 + 0xc);
    if (iVar2 != 0) {
      iVar4 = *(int *)(iVar2 + 0x3fe4);
      if (iVar4 == 0) {
        return 0xffffffff;
      }
      if (*(char *)(iVar4 + 4) != '\x02') {
        (&DAT_0036b830)[param_1] = 1;
        *(short *)(iVar4 + 0x18) = *(short *)(iVar4 + 0x18) + 1;
        *(undefined1 *)(iVar2 + 0x944) = *(undefined1 *)(iVar4 + 1);
        UpdateBeaconHandler(param_1,iVar2,8);
      }
    }
    piVar3 = (int *)*piVar3;
  } while( true );
}

