// module: mt7915.ko
// function: token_rx_dmad_update @ 0x1d4080
// size: 72 bytes
//

undefined4
token_rx_dmad_update
          (int *param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  
  iVar1 = param_2 * 0x20;
  *(undefined4 *)(*param_1 + param_2 * 0x20) = param_3;
  *(undefined4 *)(*param_1 + iVar1 + 4) = param_4;
  *(undefined4 *)(*param_1 + iVar1 + 8) = param_5;
  *(undefined4 *)(*param_1 + iVar1 + 0xc) = param_6;
  return 0;
}

