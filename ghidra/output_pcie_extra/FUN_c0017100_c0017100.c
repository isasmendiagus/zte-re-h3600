// FUN_c0017100 @ c0017100

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0017100(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  FUN_c046ab98(s_board_id__d__boardname__s__hardv_c0585eb0,*(undefined4 *)(_DAT_c069ea88 + 0x20),
               *(undefined4 *)(_DAT_c069ea88 + 0x24),*(undefined4 *)(_DAT_c069ea88 + 0x28));
  iVar3 = 0;
  do {
    iVar2 = iVar3 + 1;
    FUN_c046ab98(s_mux__d___x_c0585edc,iVar3,*(undefined4 *)(_DAT_c069ea88 + (iVar3 + 0x10) * 4));
    iVar3 = iVar2;
  } while (iVar2 != 6);
  FUN_c046ab98(s_gpio_nr__d_c0585ee8,*(undefined4 *)(_DAT_c069ea88 + 0x58));
  if (*(int *)(_DAT_c069ea88 + 0x58) != 0) {
    iVar3 = 0;
    uVar4 = 0;
    do {
      iVar2 = *(int *)(_DAT_c069ea88 + 100) + iVar3;
      if (*(int *)(iVar2 + 0xc) != 0) {
        FUN_c046ab98(s_i__d__d__d__d__d_c0585ef4,uVar4,
                     *(undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + iVar3),
                     *(undefined1 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),*(int *)(iVar2 + 0xc));
      }
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x1c;
    } while (uVar4 < *(uint *)(_DAT_c069ea88 + 0x58));
  }
  FUN_c046ab98(s_cpu_id__d__vendor__s_c0585f08,*(undefined4 *)(_DAT_c069ea88 + 0x2c),
               *(undefined4 *)(_DAT_c069ea88 + 0x30));
  FUN_c046ab98(s_gpio_nr__x_c0585f20,*(undefined4 *)(_DAT_c069ea88 + 0x58));
  FUN_c046ab98(s_led_nr__x_c0585f2c,*(undefined4 *)(_DAT_c069ea88 + 0x5c));
  if (*(int *)(_DAT_c069ea88 + 0x58) != 0) {
    iVar3 = 0;
    uVar4 = 0;
    do {
      iVar2 = *(int *)(_DAT_c069ea88 + 100) + iVar3;
      uVar5 = uVar4 + 1;
      puVar1 = (undefined4 *)(*(int *)(_DAT_c069ea88 + 100) + iVar3);
      iVar3 = iVar3 + 0x1c;
      FUN_c046ab98(s_i__d__d__d__d__d_c0585ef4,uVar4,*puVar1,*(undefined1 *)(iVar2 + 4),
                   *(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc));
      uVar4 = uVar5;
    } while (uVar5 < *(uint *)(_DAT_c069ea88 + 0x58));
  }
  return;
}

