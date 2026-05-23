// module: mt7915.ko
// function: add_assoc_reassoc_rsp_twt_ie @ 0x20517c
// size: 20 bytes
//

int add_assoc_reassoc_rsp_twt_ie(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = build_twt_ie();
  return iVar1 - param_3;
}

