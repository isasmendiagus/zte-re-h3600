// FUN_c0016c68 @ c0016c68

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0016c68(void)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  DataSynchronizationBarrier(0xf);
  uVar2 = uRamf0600004 | 0xc00000;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  DataSynchronizationBarrier(0xf);
  uVar3 = uRamf060000c | 0xf80;
  DataSynchronizationBarrier(0xe);
  uRamf0600004 = uVar2;
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  uRamf060000c = uVar3;
  uVar1 = FUN_c0016b20();
  DAT_c069ea8c = (byte)uVar1;
  FUN_c046ab98(s_product_vid____d_c0585dc0,uVar1);
  if (0x21 < DAT_c069ea8c) {
    FUN_c046ab98(s_<_s>__d__invalid_vid____use_defa_c0585dd4,s_zte_gpio_init_c04756f4,0x84c);
    DAT_c069ea8c = 0;
  }
  FUN_c046ab98(s_product_vid____d_c0585dc0,DAT_c069ea8c);
  _DAT_c069ea88 = &DAT_c0676bbc + (uint)DAT_c069ea8c * 0x128;
  FUN_c046ab98(s_current_board__x_c0585dfc);
  if (((uint)DAT_c069ea8c != *(uint *)(_DAT_c069ea88 + 0x20)) ||
     (*(int *)(_DAT_c069ea88 + 0x24) == 0)) {
    FUN_c046ab98(s_<_s>__d__invalid_current_board___c0585e10,s_zte_gpio_init_c04756f4,0x855);
    _DAT_c069ea88 = &DAT_c0676bbc;
    DAT_c069ea8c = 0;
  }
  puVar5 = (undefined4 *)0xf0600000;
  iVar6 = 0;
  do {
    *puVar5 = *(undefined4 *)(_DAT_c069ea88 + (iVar6 + 0x10) * 4);
    DataSynchronizationBarrier(0xf);
    iVar4 = iVar6 + 1;
    FUN_c046ab98(s__d__x__x_c0585d64,iVar6,*(undefined4 *)(_DAT_c069ea88 + (iVar6 + 0x10) * 4),
                 *puVar5);
    puVar5 = puVar5 + 1;
    iVar6 = iVar4;
  } while (iVar4 != 6);
  if (*(int *)(_DAT_c069ea88 + 0x58) != 0) {
    uVar3 = 0;
    uVar2 = uVar3;
    do {
      puVar5 = (undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3);
      if (puVar5[3] == 1) {
        if (*(char *)(puVar5 + 1) == '\x01') {
          FUN_c046ab98(s_output_gpio__d_c0585e44,*puVar5,0x88b);
          (*DAT_c068531c)(0x66665b0);
          FUN_c01b14fc(*(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3));
          (*DAT_c068531c)(0x66665b0);
          FUN_c01b1418(*(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3),
                       *(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3 + 8));
          (*DAT_c068531c)(0x66665b0);
          iVar6 = FUN_c01b13a0(*(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3));
          iVar4 = *(int *)(*(int *)(_DAT_c069ea88 + 100) + uVar3 + 8);
          if (iVar4 != iVar6) {
            FUN_c046ab98(s_output_gpio__d__value__d___d_c0585e54,
                         *(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3),iVar4,iVar6);
          }
        }
        else if (*(char *)(puVar5 + 1) == '\0') {
          FUN_c046ab98(s_input_gpio__d_c0585e74,*puVar5,0x88b);
          (*DAT_c068531c)(0x66665b0);
          FUN_c01b1498(*(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + uVar3));
        }
        else {
          FUN_c046ab98(s_<_s>__d__invalid_gpio_att____c0585e84,s_zte_gpio_init_c04756f4,0x88b);
        }
      }
      uVar2 = uVar2 + 1;
      uVar3 = uVar3 + 0x1c;
    } while (uVar2 < *(uint *)(_DAT_c069ea88 + 0x58));
    if (*(uint *)(_DAT_c069ea88 + 0x58) != 0) {
      iVar6 = 0;
      uVar2 = 0;
      do {
        puVar5 = (undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + iVar6);
        iVar6 = iVar6 + 0x1c;
        if ((puVar5[3] == 1) && (uVar2 == 0x29 && *(char *)(puVar5 + 1) == '\x01')) {
          FUN_c01b1418(*puVar5);
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(_DAT_c069ea88 + 0x58));
    }
  }
  DataSynchronizationBarrier(0xf);
  _DAT_c069ea90 = (uint)(iRamf0400040 << 0x18) >> 0x1e;
  if (_DAT_c069ea90 == 1) {
    uRamf0600008 = 0;
  }
  FUN_c046ab98(s_bootsel__d_c0585ea4,_DAT_c069ea90);
  return;
}

