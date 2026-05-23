// module: mt7915.ko
// function: RtmpRaDevCtrlExit @ 0x13cbbc
// size: 84 bytes
//

undefined4 RtmpRaDevCtrlExit(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0xa77c4c);
  do {
    iVar1 = *piVar2;
    piVar2 = piVar2 + 2;
    if (iVar1 != 0) {
      os_free_mem();
    }
  } while (piVar2 != (int *)(param_1 + 0xa7844c));
  wpf_config_exit(param_1);
  RTMPFreeAdapter(param_1);
  return 1;
}

