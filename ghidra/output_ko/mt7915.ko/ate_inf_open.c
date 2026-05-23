// module: mt7915.ko
// function: ate_inf_open @ 0x27f8dc
// size: 144 bytes
//

undefined4 ate_inf_open(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  iVar1 = wifi_sys_open();
  if (iVar1 != 1) {
    if (0 < DebugLevel) {
      printk("%s() open fail!!!\n","ate_inf_open");
    }
    return 0;
  }
  if (0 < DebugLevel) {
    printk("ATE inf up for ra_%x(func_idx) OmacIdx=%d\n",*(undefined1 *)(param_1 + 0xe),
           *(undefined1 *)(param_1 + 0x29));
  }
  MlmeRadioOn(uVar2,param_1);
  *(undefined1 *)(param_1 + 0xb1c) = 0;
  return 1;
}

