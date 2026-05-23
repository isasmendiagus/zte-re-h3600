// module: mt7915.ko
// function: mt_wlan_hook_unregister @ 0x246974
// size: 124 bytes
//

undefined4 mt_wlan_hook_unregister(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  if ((param_1 != (int *)0x0) &&
     (piVar3 = (int *)*(int *)wlan_hook, piVar2 = (int *)wlan_hook,
     (int *)wlan_hook != (int *)&wlan_hook)) {
    do {
      piVar1 = piVar3;
      if (param_1 == piVar2) {
        if (*param_1 != 0) {
          *(int *)(*param_1 + 4) = param_1[1];
        }
        if ((int *)param_1[1] != (int *)0x0) {
          *(int *)param_1[1] = *param_1;
        }
        *param_1 = 0;
        param_1[1] = 0;
        return 0;
      }
      piVar3 = (int *)*piVar1;
      piVar2 = piVar1;
    } while (piVar1 != (int *)&wlan_hook);
  }
  return 0xffffffff;
}

