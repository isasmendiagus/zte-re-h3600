// vmlinux.bin: FUN_c001605c @ 0xc001605c
// matched strings: synopsys pcie%d controller setting, not find pcie port:%d
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c001605c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  FUN_c046ab98(s_synopsys_pcie_d_controller_setti_c0585bec,param_1,param_3,param_4,param_4);
  if (param_1 * 0x38 == 0x3f9615e8) {
    FUN_c046ab98(s_not_find_pcie_port__d_c0585c10,param_1);
  }
  if (param_1 == 0) {
    uVar2 = *(uint *)(_DAT_c069ea24 + 0x70);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea24 + 0x70) = uVar2 | 0xb5;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea28 + 8);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea28 + 8) = uVar2 | 0x8000;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea28 + 8);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea28 + 8) = uVar2 | 0x2000;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea28 + 8);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea28 + 8) = uVar2 | 0x4000;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea24 + 0x74);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea24 + 0x74) = uVar2 & 0xfffffffe;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      uVar2 = uRamf060000c;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    uRamf060000c = uVar2 & 0xffffbfff;
    iVar3 = 500;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea28 + 0x24);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea28 + 0x24) = uVar2 & 0xfbffffff;
    iVar3 = 0x32;
    do {
      (*DAT_c068531c)(0x66665b0);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(uint *)(_DAT_c069ea24 + 0x74);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea24 + 0x74) = uVar2 | 1;
    uVar2 = *(uint *)(_DAT_c069ea24 + 0x70);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea24 + 0x70) = uVar2 & 0xfffffeff;
    uVar2 = *_DAT_c069ea2c;
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *_DAT_c069ea2c = uVar2 | 0x20;
    uVar2 = *(uint *)(_DAT_c069ea20 + 0xa0);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea20 + 0xa0) = uVar2 & 0xfffffff0 | 1;
    uVar2 = *(uint *)(_DAT_c069ea20 + 0x80);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(_DAT_c069ea20 + 0x80) = uVar2 | 0x20;
    return;
  }
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x70);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x70) = uVar2 | 0x1aa00;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8) = uVar2 | 0x8000000;
  iVar3 = 0x32;
  do {
    uVar4 = (*DAT_c068531c)(0x66665b0);
    uVar1 = (undefined4)uVar4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    uVar1 = (*DAT_c066d2b8)(uVar1,(int)((ulonglong)uVar4 >> 0x20),
                            *(undefined4 *)(*(int *)(&DAT_c069ea2c + param_1 * 0x38) + 0x1b4));
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea2c + param_1 * 0x38) + 0x1b4) = 0x202d5a;
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)(uVar1,0x202d5a,*(undefined4 *)(*(int *)(&DAT_c069ea2c + param_1 * 0x38) + 0x1b0)
                   );
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea2c + param_1 * 0x38) + 0x1b0) = 0x46c24a;
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8) = uVar2 | 0x2000000;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 8) = uVar2 | 0x4000000;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x74);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x74) = uVar2 & 0xfffffff7;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    uVar2 = uRamf060000c;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  uRamf060000c = uVar2 & 0xfffffffd;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 0x24);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea28 + param_1 * 0x38) + 0x24) = uVar2 & 0xfbffffff;
  iVar3 = 0x32;
  do {
    (*DAT_c068531c)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x74);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x74) = uVar2 | 8;
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x70);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x70) = uVar2 & 0xfffdffff;
  uVar2 = **(uint **)(&DAT_c069ea2c + param_1 * 0x38);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  **(uint **)(&DAT_c069ea2c + param_1 * 0x38) = uVar2 | 0x20;
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0xa0);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0xa0) = uVar2 & 0xfffffff0 | 1;
  uVar2 = *(uint *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0x80);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0x80) = uVar2 | 0x20;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea24 + param_1 * 0x38) + 0x74) = 0x3f;
  return;
}

