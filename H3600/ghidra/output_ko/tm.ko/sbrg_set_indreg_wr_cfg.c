// module: tm.ko
// function: sbrg_set_indreg_wr_cfg @ 0x1c848
// size: 52 bytes
//

uint sbrg_set_indreg_wr_cfg(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = sbrg_access_timeout(param_3);
  uVar2 = sbrg_set_indreg_cmd(0,0,param_1,param_2);
  return uVar2 | uVar1;
}

