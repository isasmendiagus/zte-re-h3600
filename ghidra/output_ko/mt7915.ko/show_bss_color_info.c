// module: mt7915.ko
// function: show_bss_color_info @ 0x206f64
// size: 292 bytes
//

void show_bss_color_info(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  piVar4 = (int *)(param_1 + 8);
  iVar3 = 0;
  do {
    piVar4 = piVar4 + 1;
    iVar2 = *piVar4;
    if ((iVar2 != 0) && (*(char *)(iVar2 + 0x28) != '\0')) {
      if (*(int *)(iVar2 + 0x14) - 1U < 2) {
        uVar1 = *(undefined1 *)(iVar2 + 0xa46);
        FUN_00206840(iVar2);
        hc_bcolor_get_bitmap(iVar2,&local_30);
        if (0 < DebugLevel) {
          printk("wdev_idx type dis color next collision running bitmap\n");
          if ((0 < DebugLevel) &&
             (printk("-------- ---- --- ----- ---- --------- ------- ------------------\n"),
             0 < DebugLevel)) {
            printk("%8d %4d %3d %5d %4d %9d %7d 0x%02x%02x%02x%02x%02x%02x%02x%02x\n",iVar3,
                   *(undefined4 *)(iVar2 + 0x14),*(undefined1 *)(iVar2 + 0xa3c),
                   *(undefined1 *)(iVar2 + 0xa3d),*(undefined1 *)(iVar2 + 0xa3e),
                   *(undefined1 *)(iVar2 + 0xa3f),uVar1,local_29,local_2a,local_2b,local_2c,local_2d
                   ,local_2e,local_2f,local_30);
          }
        }
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x68);
  return;
}

