// module: mt7915.ko
// function: NICLoadFirmware @ 0x1c81e0
// size: 4 bytes
//

int NICLoadFirmware(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  bool bVar6;
  undefined1 auStack_30 [12];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0xb8) != (code *)0x0) {
    (**(code **)(iVar2 + 0xb8))(param_1,1);
  }
  if ((*(code **)(param_1 + 0xa7852c) == (code *)0x0) ||
     (iVar3 = (**(code **)(param_1 + 0xa7852c))(param_1,1), iVar3 == 0)) {
    uVar5 = *(uint *)(iVar1 + 0x100);
    if ((uVar5 == 0) || ((*(int *)(param_1 + 0xa78524) != 0 && (*(int *)(param_1 + 0xa7851c) != 0)))
       ) {
      iVar1 = 0;
      do {
        if (((uVar5 >> iVar1 & 1) != 0) &&
           ((iVar3 = (**(code **)(param_1 + 0xa78524))(param_1,iVar1,auStack_30), iVar3 != 0 ||
            (iVar3 = (**(code **)(param_1 + 0xa7851c))(param_1,iVar1,auStack_30), iVar3 != 0))))
        goto LAB_001c1b88;
        bVar6 = iVar1 != 1;
        iVar1 = 1;
      } while (bVar6);
      iVar3 = 0;
      if (*(code **)(param_1 + 0xa7852c) != (code *)0x0) {
        iVar3 = (**(code **)(param_1 + 0xa7852c))(param_1,3);
      }
    }
    else if (DebugLevel < 1) {
      iVar3 = 1;
    }
    else {
      iVar3 = 1;
      printk("%s: no hook function available\n","mt_load_fw");
    }
  }
LAB_001c1b88:
  if (*(code **)(iVar2 + 0xb8) != (code *)0x0) {
    (**(code **)(iVar2 + 0xb8))(param_1,0);
  }
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = 0;
  piVar4 = (int *)(param_1 + 0xa78530);
  uVar5 = *(uint *)(iVar1 + 0x100);
  do {
    if ((((uVar5 >> iVar2 & 1) != 0) && (*piVar4 == 1)) && (piVar4[4] != 0)) {
      os_free_mem();
      piVar4[4] = 0;
    }
    bVar6 = iVar2 != 1;
    piVar4 = piVar4 + 0xf;
    iVar2 = 1;
  } while (bVar6);
  if (iVar3 != 0) {
    if (0 < DebugLevel) {
      printk("%s: fw download fail\n","mt_load_fw");
    }
    *(undefined4 *)(param_1 + 0xa7861c) = 0;
    show_trinfo_proc(param_1,&_LC54);
    return iVar3;
  }
  *(undefined4 *)(param_1 + 0xa7861c) = 3;
  return 0;
}

