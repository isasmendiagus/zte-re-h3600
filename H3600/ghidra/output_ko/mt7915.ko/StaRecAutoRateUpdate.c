// module: mt7915.ko
// function: StaRecAutoRateUpdate @ 0x1d95c0
// size: 592 bytes
//

undefined4 StaRecAutoRateUpdate(int param_1,undefined4 param_2,int param_3,undefined2 *param_4)

{
  undefined1 uVar1;
  uint uVar2;
  
  param_4[1] = 0x1c;
  *param_4 = 3;
  uVar2 = *(uint *)(param_3 + 4);
  if (uVar2 == 1) {
    *(undefined1 *)(param_4 + 4) = *(undefined1 *)(param_1 + 0x28);
    *(undefined1 *)((int)param_4 + 9) = *(undefined1 *)(param_1 + 0x29);
    *(undefined1 *)(param_4 + 5) = *(undefined1 *)(param_1 + 0x2a);
    uVar1 = *(undefined1 *)(param_1 + 0x2b);
    *(undefined4 *)(param_4 + 2) = 1;
    *(undefined1 *)((int)param_4 + 0xb) = uVar1;
    return 0;
  }
  if ((uVar2 == 2) || (uVar2 == 6)) {
LAB_001d9694:
    *(uint *)(param_4 + 2) = uVar2;
    return 0;
  }
  if (uVar2 == 5) {
    uVar1 = *(undefined1 *)(param_1 + 0xf);
    *(undefined4 *)(param_4 + 2) = 5;
    *(undefined1 *)(param_4 + 0xc) = uVar1;
    return 0;
  }
  if (uVar2 == 3) {
    *(undefined4 *)(param_4 + 2) = 3;
    *(undefined1 *)(param_4 + 6) = *(undefined1 *)(param_3 + 0xc);
    *(undefined1 *)(param_4 + 7) = *(undefined1 *)(param_3 + 0xe);
    *(undefined1 *)((int)param_4 + 0xf) = *(undefined1 *)(param_3 + 0xf);
    *(undefined1 *)(param_4 + 8) = *(undefined1 *)(param_3 + 0x10);
    *(undefined1 *)((int)param_4 + 0x11) = *(undefined1 *)(param_3 + 0x11);
    *(undefined1 *)(param_4 + 10) = *(undefined1 *)(param_3 + 0x14);
    *(undefined1 *)(param_4 + 9) = *(undefined1 *)(param_3 + 0x12);
    *(undefined1 *)((int)param_4 + 0x13) = *(undefined1 *)(param_3 + 0x13);
    *(undefined1 *)(param_4 + 0xb) = *(undefined1 *)(param_3 + 0x16);
    *(undefined1 *)((int)param_4 + 0x15) = *(undefined1 *)(param_3 + 0x15);
    return 0;
  }
  if (uVar2 == 4) {
    *(undefined4 *)(param_4 + 2) = 4;
    *(undefined1 *)(param_4 + 6) = *(undefined1 *)(param_3 + 0xc);
    *(undefined1 *)(param_4 + 7) = *(undefined1 *)(param_3 + 0xe);
    *(undefined1 *)((int)param_4 + 0xf) = *(undefined1 *)(param_3 + 0xf);
    *(undefined1 *)(param_4 + 8) = *(undefined1 *)(param_3 + 0x10);
    *(undefined1 *)((int)param_4 + 0x11) = *(undefined1 *)(param_3 + 0x11);
    *(undefined1 *)(param_4 + 9) = *(undefined1 *)(param_3 + 0x12);
    *(undefined1 *)((int)param_4 + 0x13) = *(undefined1 *)(param_3 + 0x13);
    *(undefined1 *)(param_4 + 0xb) = *(undefined1 *)(param_3 + 0x16);
    *(undefined1 *)((int)param_4 + 0x15) = *(undefined1 *)(param_3 + 0x15);
    *(undefined1 *)((int)param_4 + 0x17) = *(undefined1 *)(param_3 + 0x17);
    return 0;
  }
  if (uVar2 == 7) {
LAB_001d96c4:
    *(uint *)(param_4 + 2) = uVar2;
    *(undefined1 *)(param_4 + 10) = *(undefined1 *)(param_3 + 0x14);
    return 0;
  }
  if (uVar2 == 8) {
LAB_001d96b4:
    *(uint *)(param_4 + 2) = uVar2;
    *(undefined1 *)(param_4 + 9) = *(undefined1 *)(param_3 + 0x12);
    return 0;
  }
  if (uVar2 == 9) {
LAB_001d97b0:
    *(uint *)(param_4 + 2) = uVar2;
    *(undefined1 *)((int)param_4 + 0x13) = *(undefined1 *)(param_3 + 0x13);
    return 0;
  }
  if (uVar2 == 10) {
    *(undefined4 *)(param_4 + 2) = 10;
    *(undefined1 *)(param_4 + 8) = *(undefined1 *)(param_3 + 0x10);
    return 0;
  }
  if (uVar2 == 0xb) {
LAB_001d97c0:
    *(uint *)(param_4 + 2) = uVar2;
    *(undefined1 *)((int)param_4 + 0xf) = *(undefined1 *)(param_3 + 0xf);
  }
  else {
    if (uVar2 == 0xc) {
LAB_001d97e0:
      *(uint *)(param_4 + 2) = uVar2;
      *(undefined1 *)((int)param_4 + 0x11) = *(undefined1 *)(param_3 + 0x11);
      return 0;
    }
    if (uVar2 != 0xd) {
      if (uVar2 == 0xe) goto LAB_001d96c4;
      if (uVar2 == 0xf) goto LAB_001d96b4;
      if (uVar2 == 0x10) goto LAB_001d97b0;
      if (uVar2 == 0x11) goto LAB_001d97c0;
      if (uVar2 == 0x12) goto LAB_001d97e0;
      if (uVar2 != 0x13) {
        if (uVar2 == 0x14) {
          *(undefined4 *)(param_4 + 2) = 0x14;
          return 0;
        }
        if (uVar2 != 0x15) {
          if (uVar2 == 0x16) {
            *(undefined4 *)(param_4 + 2) = 0x16;
            *(undefined1 *)((int)param_4 + 0x15) = *(undefined1 *)(param_3 + 0x15);
            return 0;
          }
          if (uVar2 < 0x18) {
            return 0;
          }
        }
        goto LAB_001d9694;
      }
    }
    *(uint *)(param_4 + 2) = uVar2;
    *(undefined1 *)(param_4 + 7) = *(undefined1 *)(param_3 + 0xe);
  }
  return 0;
}

