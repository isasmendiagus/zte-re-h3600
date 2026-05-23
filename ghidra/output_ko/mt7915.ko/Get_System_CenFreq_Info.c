// module: mt7915.ko
// function: Get_System_CenFreq_Info @ 0xeb71c
// size: 540 bytes
//

undefined2 Get_System_CenFreq_Info(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  ushort uVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 auStack_1b [6];
  byte local_15;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    uVar2 = HcGetRadioChannel(param_1);
    if (0xe < uVar2) goto LAB_000eb8e4;
LAB_000eb7e0:
    uVar5 = 1;
  }
  else {
    if ((((*(int *)(iVar1 + 0x194) == param_2) || (*(int *)(iVar1 + 0x198) == param_2)) ||
        (*(int *)(iVar1 + 0x1a4) == param_2)) ||
       ((((*(int *)(iVar1 + 0x1a8) == param_2 || (*(int *)(iVar1 + 0x1b4) == param_2)) ||
         (*(int *)(iVar1 + 0x1b8) == param_2)) ||
        (((*(int *)(iVar1 + 0x19c) != param_2 && (*(int *)(iVar1 + 0x1a0) != param_2)) &&
         ((*(int *)(iVar1 + 0x1ac) != param_2 &&
          (((*(int *)(iVar1 + 0x1b0) != param_2 && (*(int *)(iVar1 + 0x1bc) != param_2)) &&
           (*(int *)(iVar1 + 0x1c0) != param_2)))))))))) goto LAB_000eb7e0;
LAB_000eb8e4:
    uVar5 = 2;
  }
  iVar1 = hc_radio_query_by_rf(param_1,uVar5,auStack_1b);
  if (iVar1 == 0) {
LAB_000eb890:
    uVar4 = (ushort)local_15;
    if (DebugLevel < 1) goto joined_r0x000eb8b8;
    printk("%s : CentralCh = %d\n","Get_System_CenFreq_Info",uVar4);
    if (CH_HZ_ID_MAP_NUM == 0) {
      uVar3 = 0;
      goto LAB_000eb868;
    }
  }
  else {
    if (0 < DebugLevel) {
      printk("%s : can\'t find radio for RFIC:%d\n","Get_System_CenFreq_Info",uVar5);
      goto LAB_000eb890;
    }
    uVar4 = (ushort)local_15;
joined_r0x000eb8b8:
    if (CH_HZ_ID_MAP_NUM == 0) {
      return 0;
    }
  }
  puVar6 = CH_HZ_ID_MAP;
  if (CH_HZ_ID_MAP._0_2_ == uVar4) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      if (CH_HZ_ID_MAP_NUM <= uVar2) {
        uVar3 = 0;
        goto LAB_000eb868;
      }
      puVar6 = (undefined1 *)((int)puVar6 + 4);
    } while (*(ushort *)puVar6 != uVar4);
  }
  uVar3 = *(undefined2 *)(CH_HZ_ID_MAP + uVar2 * 4 + 2);
LAB_000eb868:
  if (0 < DebugLevel) {
    printk("%s : CentralFreq = %d\n","Get_System_CenFreq_Info",uVar3);
  }
  return uVar3;
}

