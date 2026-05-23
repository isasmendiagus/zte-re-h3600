// module: plat-zxylzb_9128S.ko
// function: sadm_port_limit @ 0x17ddc
// size: 140 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 sadm_port_limit(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c [3];
  
  if (param_1 < 8) {
    local_1c[0] = (uint)((*(int *)(pp_base + 0x4024) + 1) * param_2 * 0x20) / 250000;
    iVar1 = sadm_ram_set(param_1,local_1c,2);
    if (-1 < iVar1) {
      local_1c[1] = 1;
      uVar2 = sadm_ram_set(param_1,local_1c + 1,0);
      return uVar2;
    }
  }
  return 0xffffffff;
}

