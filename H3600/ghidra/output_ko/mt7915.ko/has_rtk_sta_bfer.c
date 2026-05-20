// module: mt7915.ko
// function: has_rtk_sta_bfer @ 0x88bf0
// size: 336 bytes
//

bool has_rtk_sta_bfer(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  char local_1a;
  char local_19;
  
  uVar3 = 1;
  bVar4 = false;
  while ((uVar1 = HcGetMaxStaNum(param_1), uVar3 < uVar1 && (bVar4 == false))) {
    iVar2 = uVar3 * 0x14c0 + param_1;
    if ((*(int *)(iVar2 + 0xa1d20) == 0x20001) && (*(int *)(iVar2 + 0xa1e1c) == 2)) {
      if (2 < DebugLevel) {
        printk("STA[%d] has_oui:%d\n",uVar3,*(undefined1 *)(iVar2 + 0xa2986));
      }
      if ((*(char *)(param_1 + uVar3 * 0x14c0 + 0xa2986) == '\0') &&
         (iVar2 = FUN_00084dc0(param_1 + uVar3 * 0x14c0 + 0xa1d20,&local_19,&local_1a), iVar2 != 0))
      {
        if (local_19 != '\0') {
          bVar4 = local_1a == '\x02';
        }
        if (2 < DebugLevel) {
          printk("%s sta %d BFer:%d, Nr=%d\n","has_rtk_sta_bfer",uVar3,local_19,local_1a);
        }
      }
    }
    uVar3 = uVar3 + 1 & 0xffff;
  }
  if (2 < DebugLevel) {
    printk("%s found_rtk_sta_bfer=%d\n","has_rtk_sta_bfer",bVar4);
  }
  return bVar4;
}

