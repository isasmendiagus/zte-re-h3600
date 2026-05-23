// module: mt7915.ko
// function: hc_init_ACSChCtrl @ 0xaa78c
// size: 104 bytes
//

undefined4 hc_init_ACSChCtrl(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xa797a0);
  *(undefined4 *)(iVar1 + 0x136c) = 0;
  *(undefined1 *)(iVar1 + 0x1370) = 0;
  *(undefined1 *)(iVar1 + 0x1372) = 0;
  *(undefined4 *)(iVar1 + 0x1374) = 0;
  os_zero_mem(iVar1 + 0x13d8,0x1e0,param_3,iVar1 + 0x1000,param_4);
  iVar1 = *(int *)(param_1 + 0xa797a0);
  *(undefined4 *)(iVar1 + 0x16c0) = 0;
  *(undefined1 *)(iVar1 + 0x16c4) = 0;
  *(undefined1 *)(iVar1 + 0x16c6) = 0;
  *(undefined4 *)(iVar1 + 0x16c8) = 0;
  os_zero_mem(iVar1 + 0x172c,0x1e0);
  return 0;
}

