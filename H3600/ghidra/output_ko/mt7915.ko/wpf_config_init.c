// module: mt7915.ko
// function: wpf_config_init @ 0x105cc8
// size: 192 bytes
//

void wpf_config_init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  os_zero_mem(param_1 + 0xa7c558,0x680,param_3,param_4,param_4);
  iVar3 = param_1 + 0xa7c560;
  iVar4 = 0;
  iVar2 = param_1 + 0xa7c564;
  do {
    *(char *)(iVar2 + -0xc) = (char)iVar4;
    os_alloc_mem(0,iVar3,0x8c);
    iVar4 = iVar4 + 1;
    if (*(int *)(iVar2 + -4) != 0) {
      os_zero_mem(*(int *)(iVar2 + -4),0x8c);
      iVar5 = *(int *)(iVar2 + -4);
      phy_cfg_init(iVar5);
      ht_cfg_init(iVar5 + 0x14);
      vht_cfg_init(iVar5 + 0x5c);
      he_cfg_init(iVar5 + 100);
    }
    os_alloc_mem(0,iVar2,0x70);
    piVar1 = (int *)(iVar3 + 4);
    iVar3 = iVar3 + 0x10;
    if (*piVar1 != 0) {
      os_zero_mem(*piVar1,0x70);
    }
    iVar2 = iVar2 + 0x10;
  } while (iVar4 != 0x68);
  return;
}

