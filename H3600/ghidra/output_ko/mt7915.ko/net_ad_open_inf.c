// module: mt7915.ko
// function: net_ad_open_inf @ 0x25a400
// size: 140 bytes
//

bool net_ad_open_inf(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  printk("%s --->\n","net_ad_open_inf");
  iVar1 = wifi_sys_open(param_1);
  if (iVar1 == 1) {
    printk("%s: inf up for ra_%x(func_idx) OmacIdx=%d\n","net_ad_open_inf",
           *(undefined1 *)(param_1 + 0xe),*(undefined1 *)(param_1 + 0x29));
    MlmeRadioOn(uVar2,param_1);
    *(undefined1 *)(param_1 + 0xb1c) = 0;
    printk("%s <---\n","net_ad_open_inf");
  }
  else {
    printk("%s: open fail!!!\n","net_ad_open_inf");
  }
  return iVar1 == 1;
}

