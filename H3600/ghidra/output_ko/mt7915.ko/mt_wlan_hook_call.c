// module: mt7915.ko
// function: mt_wlan_hook_call @ 0x246a14
// size: 120 bytes
//

undefined4 mt_wlan_hook_call(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined8 *puVar1;
  
  if (((undefined8 *)wlan_hook != (undefined8 *)0x0) && ((undefined8 *)wlan_hook != &wlan_hook)) {
    puVar1 = (undefined8 *)wlan_hook;
    do {
      while ((1 << (param_1 & 0xff) & (uint)*(ushort *)((int)puVar1 + 0x8e)) != 0) {
        (**(code **)(puVar1 + 0x11))(param_1,param_2,param_3,*(code **)(puVar1 + 0x11),param_4);
        puVar1 = *(undefined8 **)puVar1;
        if (puVar1 == &wlan_hook) {
          return 0;
        }
      }
      puVar1 = *(undefined8 **)puVar1;
    } while (puVar1 != &wlan_hook);
  }
  return 0;
}

