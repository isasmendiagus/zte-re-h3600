// module: mt7915.ko
// function: HwCtrlUpdateRtsThreshold @ 0xaeb40
// size: 32 bytes
//

undefined4
HwCtrlUpdateRtsThreshold(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_2 + 8);
  AsicUpdateRtsThld(param_1,*puVar1,*(undefined1 *)(puVar1 + 1),puVar1[2],param_4);
  return 0;
}

