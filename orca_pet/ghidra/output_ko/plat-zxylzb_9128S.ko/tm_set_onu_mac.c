// module: plat-zxylzb_9128S.ko
// function: tm_set_onu_mac @ 0x10000
// size: 140 bytes
//

undefined4 tm_set_onu_mac(uint param_1,undefined1 *param_2)

{
  if (param_1 < 5 && param_2 != (undefined1 *)0x0) {
    *(uint *)(npp_base + (short)param_1 * 8 + 0x120) =
         (uint)(byte)param_2[3] << 0x10 | (uint)(byte)param_2[2] << 0x18 | (uint)(byte)param_2[5] |
         (uint)(byte)param_2[4] << 8;
    *(uint *)(npp_base + (short)param_1 * 8 + 0x124) = (uint)CONCAT11(*param_2,param_2[1]);
    return 0;
  }
  return 0xffffffff;
}

