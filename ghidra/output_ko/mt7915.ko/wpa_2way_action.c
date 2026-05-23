// module: mt7915.ko
// function: wpa_2way_action @ 0x11fe38
// size: 216 bytes
//

/* WARNING: Removing unreachable block (ram,0x0011fe74) */
/* WARNING: Removing unreachable block (ram,0x0011fec4) */
/* WARNING: Removing unreachable block (ram,0x0011fed0) */

void wpa_2way_action(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x92c) == 0) {
    if (-1 < DebugLevel) {
      printk("%s: 2-way fail due to wdev is null!\n","wpa_2way_action");
    }
  }
  else {
    (**(code **)(*(int *)(*(int *)(param_2 + 0x92c) + 0x904) + 0xb8))();
    if (-1 < DebugLevel) {
      printk("%s: 2-way fail due to pEntry is null!\n","wpa_2way_action");
    }
  }
  return;
}

