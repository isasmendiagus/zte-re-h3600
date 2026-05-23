// module: mt7915.ko
// function: RoutingTabLookup @ 0xa1120
// size: 260 bytes
//

int RoutingTabLookup(int param_1,undefined4 param_2,void *param_3,int param_4,undefined2 *param_5)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  iVar2 = RoutingTabGetEntryCount();
  if (iVar2 != 0) {
    if (param_3 == (void *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: Hash Id isn\'t correct!\n","RoutingTabLookup");
        return 0;
      }
    }
    else {
      for (piVar3 = (int *)GetRoutingTabHead(param_1,param_2,*(byte *)((int)param_3 + 5) & 0x3f);
          piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
        if ((*(char *)((int)piVar3 + 0x11) != '\0') &&
           (iVar2 = memcmp(param_3,piVar3 + 6,6), iVar2 == 0)) {
          uVar1 = *(ushort *)((int)piVar3 + 0x12);
          uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if (uVar4 <= uVar1) {
            return 0;
          }
          if (param_4 != 0) {
            RoutingEntryRefresh(param_1,param_2,piVar3);
            *(undefined1 *)(piVar3 + 4) = 0;
            *(undefined1 *)((int)piVar3 + 0x1e) = 0;
          }
          if (param_5 != (undefined2 *)0x0) {
            *param_5 = *(undefined2 *)((int)piVar3 + 0x12);
          }
          return (int)piVar3;
        }
      }
    }
  }
  return 0;
}

