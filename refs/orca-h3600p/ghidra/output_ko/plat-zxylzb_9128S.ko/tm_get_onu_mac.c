// module: plat-zxylzb_9128S.ko
// function: tm_get_onu_mac @ 0x1008c
// size: 140 bytes
//

undefined4 tm_get_onu_mac(uint param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  
  if (4 < param_1 || param_2 == (undefined1 *)0x0) {
    return 0xffffffff;
  }
  uVar1 = *(undefined4 *)(npp_base + (short)param_1 * 8 + 0x124);
  param_2[1] = (char)uVar1;
  *param_2 = (char)((uint)uVar1 >> 8);
  uVar1 = *(undefined4 *)(npp_base + (short)param_1 * 8 + 0x120);
  param_2[5] = (char)uVar1;
  param_2[2] = (char)((uint)uVar1 >> 0x18);
  param_2[3] = (char)((uint)uVar1 >> 0x10);
  param_2[4] = (char)((uint)uVar1 >> 8);
  return 0;
}

