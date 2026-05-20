// module: mt7915.ko
// function: wlan_operate_get_he_bss_next_color @ 0x2061d4
// size: 96 bytes
//

undefined4 wlan_operate_get_he_bss_next_color(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xb14);
  if (param_1 == 0 || iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0;
    *param_2 = *(undefined1 *)(iVar2 + 0x60);
    *param_3 = *(undefined1 *)(iVar2 + 0x61);
  }
  if (3 < DebugLevel) {
    printk("%s: next color = %d, countdown = %d\n","wlan_operate_get_he_bss_next_color",
           *(undefined1 *)(iVar2 + 0x60),*(undefined1 *)(iVar2 + 0x61));
  }
  return uVar1;
}

