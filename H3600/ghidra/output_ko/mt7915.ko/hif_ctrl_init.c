// module: mt7915.ko
// function: hif_ctrl_init @ 0x1df6b8
// size: 48 bytes
//

undefined1 hif_ctrl_init(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 + -4;
  iVar1 = param_2;
  if (param_2 != 1) {
    iVar1 = iVar2;
  }
  if (iVar1 != 0 && (param_2 != 1 && iVar2 != 1)) {
    return 2;
  }
  iVar1 = multi_hif_entry_alloc(param_1,0x6e0,param_3,iVar2,param_4);
  return iVar1 != 0;
}

