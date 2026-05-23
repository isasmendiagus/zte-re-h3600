// module: mt7915.ko
// function: HwCtrlUpdateProtect @ 0xaeb2c
// size: 20 bytes
//

undefined4 HwCtrlUpdateProtect(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  AsicUpdateProtect(param_1,*(undefined4 *)(param_2 + 8),param_3,param_4,param_4);
  return 0;
}

