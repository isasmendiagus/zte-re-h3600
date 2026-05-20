// module: mt7915.ko
// function: Mumimo_scenario_maintain @ 0xce764
// size: 612 bytes
//

void Mumimo_scenario_maintain(int param_1)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  byte bVar6;
  
  if (*(short *)(param_1 + 0x285920) != 0) {
    bVar6 = 0;
    uVar4 = 1;
    do {
      bVar2 = bVar6 + 1;
      if (*(char *)(uVar4 * 0x14c0 + param_1 + 0xa295c) != '\0') {
        if (1 < DebugLevel) {
          printk("at 1\n");
        }
        bVar6 = bVar2;
        if (1 < bVar2) {
          if ((1 < DebugLevel) && (printk("at 2\n"), 1 < DebugLevel)) {
            printk("value of pAd->MUMIMO_TxOP_Value = %d\n",*(undefined2 *)(param_1 + 0xa7c2fc));
          }
          if (*(short *)(param_1 + 0xa7c2fc) == 0xc0) {
            return;
          }
          piVar5 = (int *)(param_1 + 0xc);
          goto LAB_000ce834;
        }
      }
      uVar4 = uVar4 + 1 & 0xffff;
    } while (uVar4 <= *(ushort *)(param_1 + 0x285920));
  }
  if (*(short *)(param_1 + 0xa7c2fc) == txop0) {
    return;
  }
  piVar5 = (int *)(param_1 + 0xc);
  do {
    if (DebugLevel < 2) {
      iVar3 = *piVar5;
      if (iVar3 != 0) {
LAB_000ce8d0:
        sVar1 = txop0;
        *(short *)(param_1 + 0xa7c2fc) = txop0;
        disable_tx_burst(param_1,iVar3,2,5,sVar1);
      }
    }
    else {
      printk("at 5\n");
      iVar3 = *piVar5;
      if (iVar3 != 0) {
        if (1 < DebugLevel) {
          printk("at 6\n");
        }
        goto LAB_000ce8d0;
      }
    }
    piVar5 = piVar5 + 1;
    if (piVar5 == (int *)(param_1 + 0x1ac)) {
      return;
    }
  } while( true );
LAB_000ce834:
  if (DebugLevel < 2) {
    iVar3 = *piVar5;
    if (iVar3 != 0) {
LAB_000ce84c:
      *(undefined2 *)(param_1 + 0xa7c2fc) = 0xc0;
      enable_tx_burst(param_1,iVar3,2,5,0xc0);
    }
  }
  else {
    printk("at 3\n");
    iVar3 = *piVar5;
    if (iVar3 != 0) {
      if (1 < DebugLevel) {
        printk("at 4\n");
      }
      goto LAB_000ce84c;
    }
  }
  piVar5 = piVar5 + 1;
  if (piVar5 == (int *)(param_1 + 0x1ac)) {
    return;
  }
  goto LAB_000ce834;
}

