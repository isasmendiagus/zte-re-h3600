// module: mt7915.ko
// function: mtf_txpower_boost_rate_type @ 0x1a1800
// size: 300 bytes
//

undefined4 mtf_txpower_boost_rate_type(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = 0;
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar6 = (char *)(param_1 + param_2 * 0xa1 + 0x794d68);
  do {
    if (((iVar1 != 0) && (*(code **)(iVar1 + 0x200) != (code *)0x0)) &&
       (iVar3 = (**(code **)(iVar1 + 0x200))(param_1,iVar7), iVar3 == 0)) {
      return 0;
    }
    iVar4 = *(int *)(iVar2 + 0x20c);
    iVar3 = DebugLevel;
    if (*(char *)(iVar4 + iVar7) != '\0') {
      iVar8 = 1 - (int)pcVar6;
      do {
        if (0 < iVar3) {
          printk("(%2d) ",(int)*pcVar6);
          iVar4 = *(int *)(iVar2 + 0x20c);
          iVar3 = DebugLevel;
        }
        pcVar5 = pcVar6 + iVar8;
        pcVar6 = pcVar6 + 1;
      } while (((uint)pcVar5 & 0xff) < (uint)*(byte *)(iVar4 + iVar7));
    }
    if ((0 < iVar3) && (printk(&_LC288), 0 < DebugLevel)) {
      printk("-------------------------------------------------------\n");
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0xf);
  return 1;
}

