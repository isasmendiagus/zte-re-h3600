// module: tm.ko
// function: sbrg_get_indreg_wr_cfg @ 0x1c87c
// size: 68 bytes
//

uint sbrg_get_indreg_wr_cfg
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = sbrg_access_timeout(param_3);
  uVar2 = sbrg_set_indreg_cmd(0,1,param_1,param_2,param_4);
  uVar3 = sbrg_access_timeout(param_3);
  return uVar2 | uVar1 | uVar3;
}

