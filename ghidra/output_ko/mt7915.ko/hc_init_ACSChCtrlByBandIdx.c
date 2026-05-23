// module: mt7915.ko
// function: hc_init_ACSChCtrlByBandIdx @ 0xaa7f4
// size: 80 bytes
//

undefined4 hc_init_ACSChCtrlByBandIdx(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xa797a0);
  iVar2 = iVar1 + 0x1000 + param_2 * 0x354;
  *(undefined4 *)(iVar2 + 0x36c) = 0;
  *(undefined1 *)(iVar2 + 0x370) = 0;
  *(undefined1 *)(iVar2 + 0x372) = 0;
  *(undefined4 *)(iVar2 + 0x374) = 0;
  os_zero_mem(iVar1 + param_2 * 0x354 + 0x13d8,0x1e0);
  return 0;
}

