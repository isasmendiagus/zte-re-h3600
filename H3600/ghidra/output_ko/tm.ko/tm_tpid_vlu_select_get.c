// module: tm.ko
// function: tm_tpid_vlu_select_get @ 0x6519c
// size: 112 bytes
//

undefined4 tm_tpid_vlu_select_get(uint param_1,undefined4 *param_2)

{
  if (param_1 == 0x88a8) {
    *param_2 = 1;
    return 0;
  }
  if (param_1 < 0x88a9) {
    if (param_1 != 0x8100) {
LAB_000651e8:
      printk("tpid is out of range\n");
      return 0;
    }
    *param_2 = 0;
  }
  else if (param_1 == 0x9100) {
    *param_2 = 2;
  }
  else {
    if (param_1 != 0x9200) goto LAB_000651e8;
    *param_2 = 3;
  }
  return 0;
}

