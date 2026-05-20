// module: mt7915.ko
// function: ap_mlme_search_wcid @ 0x1e188
// size: 332 bytes
//

undefined2
ap_mlme_search_wcid(int param_1,byte *param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  ushort uVar1;
  int *piVar2;
  short *psVar3;
  uint uVar4;
  
  uVar4 = (uint)*(ushort *)(param_5 + 0x10);
  if (uVar4 == 0xffff) {
    if (2 < DebugLevel) {
      printk("wdev not initailized\n");
    }
  }
  else {
    if ((*(int *)(param_5 + 0x14) == 1) && ((*param_2 & 1) != 0)) {
      if (0x11f < uVar4) {
        return 0;
      }
      piVar2 = (int *)(uVar4 * 0x14c0 + param_1 + 0xa1d20);
    }
    else {
      piVar2 = (int *)MacTableLookup(param_1);
    }
    if (piVar2 != (int *)0x0) {
      if (*piVar2 == 2 || *piVar2 == 0x40001) {
        psVar3 = (short *)lookup_rept_entry(param_1,param_3);
        if (psVar3 == (short *)0x0) {
          if ((piVar2[2] == 0) ||
             (uVar4 = (uint)*(byte *)(piVar2[2] + 0xe), (byte)(&DAT_003678f9)[param_1] <= uVar4)) {
            uVar1 = *(ushort *)(&DAT_00580e38 + param_1);
          }
          else {
            uVar1 = *(ushort *)(&DAT_00580e38 + param_1 + uVar4 * 0x2137b0);
          }
          piVar2 = (int *)((uint)uVar1 * 0x14c0 + param_1 + 0xa1d20);
        }
        else {
          if (*psVar3 != 0x101) goto LAB_0001e1e0;
          piVar2 = *(int **)(psVar3 + 0x20a2);
        }
        if (piVar2 == (int *)0x0) {
          return 0;
        }
      }
LAB_0001e1e0:
      return (short)piVar2[0x38];
    }
  }
  return 0;
}

