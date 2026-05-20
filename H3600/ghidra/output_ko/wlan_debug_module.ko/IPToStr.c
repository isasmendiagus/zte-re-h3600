// module: wlan_debug_module.ko
// function: IPToStr @ 0x12af0
// size: 92 bytes
//

undefined4 IPToStr(uint *param_1,char *param_2,size_t param_3)

{
  uint uVar1;
  
  uVar1 = *param_1;
  if (param_2 == (char *)0x0 || param_3 < 0xf) {
    return 0;
  }
  snprintf(param_2,param_3,"%d.%d.%d.%d",uVar1 >> 0x18,(uVar1 << 8) >> 0x18,(uVar1 << 0x10) >> 0x18,
           uVar1 & 0xff);
  return 1;
}

