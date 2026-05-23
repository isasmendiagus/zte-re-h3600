// module: mt7915.ko
// function: TRTableInsertEntry @ 0x1483e0
// size: 616 bytes
//

void TRTableInsertEntry(int param_1,uint param_2,undefined4 *param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  
  uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < 0x120 && param_2 < uVar1) {
    *(short *)((int)param_3 + 0xe2) = (short)param_2;
    iVar6 = param_2 * 0x620;
    iVar4 = param_1 + iVar6;
    iVar7 = param_1 + 0x1c0 + iVar6;
    *(undefined4 *)(iVar4 + 0x2f6a0) = *param_3;
    *(undefined4 *)(iVar4 + 0x2f6a4) = param_3[2];
    *(undefined1 *)(iVar4 + 0x2f6aa) = *(undefined1 *)(param_3 + 0x39);
    *(undefined2 *)(iVar7 + 0x2f4e8) = *(undefined2 *)(param_3 + 0x38);
    memmove((void *)(iVar7 + 0x2f4eb),param_3 + 0x3b,6);
    puVar5 = (undefined2 *)(param_1 + iVar6 + 0x2f6b2);
    *(undefined2 *)(iVar7 + 0x2f4f2) = 0;
    do {
      puVar5 = puVar5 + 1;
      *puVar5 = 0;
    } while (puVar5 != (undefined2 *)(param_1 + iVar6 + 0x2f6c2));
    iVar4 = 0;
    puVar3 = (undefined1 *)(param_1 + iVar6 + 0x2f977);
    puVar2 = (undefined4 *)(param_1 + iVar6 + 0x2f9cc);
    puVar8 = (undefined4 *)(param_1 + iVar6 + 0x2f988);
    do {
      iVar4 = iVar4 + 1;
      puVar2 = puVar2 + 1;
      *puVar2 = 0xffffffff;
      puVar8 = puVar8 + 1;
      *puVar8 = 0xffffffff;
      puVar3 = puVar3 + 1;
      *puVar3 = 0;
    } while (iVar4 != 0x11);
    iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar4 == 2) {
      iVar4 = param_1 + param_2 * 0x620;
      if (*(int *)(iVar4 + 0x2f6a4) == 0) {
        if (-1 < DebugLevel) {
          printk("%s: wdev == NULL\n","TRTableInsertEntry",0,DebugLevel,param_4);
        }
      }
      else {
        *(undefined1 *)(iVar4 + 0x2fa7d) = *(undefined1 *)(param_3[2] + 0x29);
      }
    }
    iVar4 = 0;
    iVar7 = param_1 + param_2 * 0x620;
    puVar8 = (undefined4 *)(param_1 + iVar6 + 0x2f6c8);
    puVar2 = (undefined4 *)(param_1 + iVar6 + 0x2f730);
    *(undefined1 *)(iVar7 + 0x2f762) = 2;
    *(undefined1 *)(iVar7 + 0x2f763) = 0;
    *(undefined1 *)(iVar7 + 0x2f761) = 0;
    *(undefined1 *)(iVar7 + 0x2f766) = *(undefined1 *)((int)param_3 + 0xb7f);
    do {
      iVar4 = iVar4 + 1;
      *puVar8 = 0;
      puVar8[-1] = 0;
      puVar8[1] = 0;
      puVar2 = puVar2 + 1;
      *puVar2 = 0;
      puVar8 = puVar8 + 4;
    } while (iVar4 != 4);
    iVar6 = param_1 + param_2 * 0x620;
    *(undefined4 *)(iVar6 + 0x2f708) = 0;
    *(undefined4 *)(iVar6 + 0x2f704) = 0;
    *(undefined4 *)(iVar6 + 0x2f70c) = 0;
    *(undefined4 *)(iVar6 + 0x2f744) = 0;
    *(undefined4 *)(iVar6 + 0x2f748) = 0;
    *(undefined4 *)(iVar6 + 0x2f74c) = 0;
    *(undefined4 *)(iVar6 + 0x2f750) = 0;
    *(undefined4 *)(iVar6 + 0x2f754) = 0;
    *(undefined1 *)(iVar6 + 0x2f758) = 1;
    *(undefined1 *)(iVar6 + 0x2f759) = 1;
    memmove((void *)(param_1 + 0x1c0 + param_2 * 0x620 + 0x2f59a),(void *)(param_3[2] + 0x21),6);
    return;
  }
  return;
}

