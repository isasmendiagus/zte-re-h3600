// module: mt7915.ko
// function: mt_wlan_hook_register @ 0x2468e0
// size: 148 bytes
//

undefined4 mt_wlan_hook_register(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  bool bVar4;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0xffffffff;
  }
  if ((undefined8 *)wlan_hook != (undefined8 *)0x0) {
    puVar2 = (undefined8 *)wlan_hook;
    puVar3 = *(undefined8 **)(undefined8 *)wlan_hook;
    if ((undefined8 *)wlan_hook != &wlan_hook) {
      do {
        if ((puVar2 != (undefined8 *)0x0) &&
           (*(ushort *)((int)puVar2 + 0x8c) < *(ushort *)(param_1 + 0x23))) {
          *param_1 = puVar3;
          *(undefined4 **)puVar2 = param_1;
          return 0;
        }
        bVar4 = puVar3 != &wlan_hook;
        puVar2 = puVar3;
        puVar3 = *(undefined8 **)puVar3;
      } while (bVar4);
    }
    *param_1 = (undefined8 *)wlan_hook;
    param_1[1] = &wlan_hook;
    puVar1 = (undefined4 *)((int)(undefined8 *)wlan_hook + 4);
    wlan_hook._0_4_ = (undefined8 *)param_1;
    *puVar1 = param_1;
    return 0;
  }
  return 0;
}

