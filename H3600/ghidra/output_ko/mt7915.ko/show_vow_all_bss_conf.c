// module: mt7915.ko
// function: show_vow_all_bss_conf @ 0x475d0
// size: 76 bytes
//

undefined4 show_vow_all_bss_conf(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  char acStack_14 [8];
  
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    snprintf(acStack_14,4,"%d",iVar1);
    show_vow_bss_conf(param_1,acStack_14);
    iVar1 = iVar2;
  } while (iVar2 != 0x10);
  return 1;
}

