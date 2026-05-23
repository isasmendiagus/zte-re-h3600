// module: mt7915.ko
// function: set_ap_wireless @ 0xcf590
// size: 88 bytes
//

undefined4 set_ap_wireless(undefined4 param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 *puVar2;
  
  puVar2 = ap_set_wireless_capi;
  do {
    iVar1 = strcmp(*(char **)puVar2,param_2);
    if (iVar1 == 0) {
      (**(code **)((int)puVar2 + 4))(param_1,param_3);
      return 0;
    }
    puVar2 = (undefined1 *)((int)puVar2 + 8);
  } while (puVar2 != fp_qm_ops + 0x38);
  return 0;
}

