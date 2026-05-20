// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_int @ 0x1a690
// size: 116 bytes
//

void pon_tm_net_int(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = tm_base;
  *(int *)(param_1 + 0xe0) = *(int *)(param_1 + 0xe0) + 1;
  *(uint *)(tm_base + 0x104) = *(uint *)(iVar1 + 0x104) | 7;
  *(undefined4 *)(param_1 + 0xc) = param_2;
  if (-1 < *(int *)(param_1 + 0x78) << 0x1e) {
    iVar1 = _test_and_set_bit(0,param_1 + 0x78);
    if (iVar1 == 0) {
      __napi_schedule(param_1 + 0x70);
      return;
    }
  }
  *(int *)(param_1 + 0xe4) = *(int *)(param_1 + 0xe4) + 1;
  return;
}

