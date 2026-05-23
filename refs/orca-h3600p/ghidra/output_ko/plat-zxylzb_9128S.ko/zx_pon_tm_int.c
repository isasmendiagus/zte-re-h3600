// module: plat-zxylzb_9128S.ko
// function: zx_pon_tm_int @ 0x18ff4
// size: 84 bytes
//

undefined4 zx_pon_tm_int(undefined4 param_1,undefined4 *param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(tm_base + 0x100) & 3 & ~*(uint *)(tm_base + 0x104);
  if (uVar1 != 0) {
    pon_tm_net_int(*param_2,uVar1);
    param_2[1] = param_2[1] + 1;
    return 1;
  }
  return 1;
}

