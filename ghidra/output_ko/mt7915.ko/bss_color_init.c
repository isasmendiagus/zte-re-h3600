// module: mt7915.ko
// function: bss_color_init @ 0x206bf0
// size: 156 bytes
//

void bss_color_init(int param_1,int param_2)

{
  int iVar1;
  
  os_zero_mem(param_2 + 0xb0,0x40);
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 == 1) {
    iVar1 = FUN_002067d0(param_1,param_2 + 0xb1);
    if (iVar1 == 0) {
      wlan_operate_set_he_bss_color(param_1,0,1);
      return;
    }
    wlan_operate_set_he_bss_color
              (param_1,*(undefined1 *)(param_2 + 0xb1),*(undefined1 *)(param_2 + 0xb0));
    *(undefined1 *)(param_2 + 0xb8) = 10;
    *(undefined1 *)(param_2 + 0xb9) = 0x32;
    iVar1 = *(int *)(param_1 + 0x14);
  }
  if (iVar1 == 2) {
    *(undefined1 *)(param_2 + 0xb9) = 5;
    iVar1 = *(int *)(param_1 + 0x14);
  }
  iVar1 = is_testmode_wdev(iVar1);
  if (iVar1 != 0) {
    *(undefined1 *)(param_2 + 0xb1) = 0x2e;
    *(undefined1 *)(param_2 + 0xb0) = 0;
  }
  return;
}

