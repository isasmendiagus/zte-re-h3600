// module: tm.ko
// function: sadm_set_indreg_wr_cfg @ 0x25a3c
// size: 84 bytes
//

uint sadm_set_indreg_wr_cfg(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = sadm_access_timeout(param_3);
  uVar2 = sadm_set_indacs_cmd(param_1,param_2,0,0,0);
  uVar3 = sadm_access_timeout(param_3);
  return uVar2 | uVar1 | uVar3;
}

