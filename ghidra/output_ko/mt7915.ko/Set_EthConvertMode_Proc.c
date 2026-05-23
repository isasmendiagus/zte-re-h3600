// module: mt7915.ko
// function: Set_EthConvertMode_Proc @ 0xdfbd0
// size: 272 bytes
//

undefined4
Set_EthConvertMode_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = rtstrcasecmp(param_2,"dongle",param_3,param_4,param_4);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0xa77bcf) = 1;
    *(undefined4 *)(param_1 + 0xa77bc9) = *(undefined4 *)(param_1 + 0x794b5b);
    *(undefined2 *)(param_1 + 0xa77bcd) = *(undefined2 *)(param_1 + 0x794b5f);
    *(undefined1 *)(param_1 + 0xa77bd0) = 1;
  }
  else {
    iVar1 = rtstrcasecmp(param_2,"clone");
    if (iVar1 == 1) {
      *(undefined1 *)(param_1 + 0xa77bcf) = 2;
      *(undefined1 *)(param_1 + 0xa77bd0) = 0;
    }
    else {
      iVar1 = rtstrcasecmp(param_2,"hybrid");
      if (iVar1 == 1) {
        *(undefined1 *)(param_1 + 0xa77bcf) = 3;
      }
      else {
        *(undefined1 *)(param_1 + 0xa77bcf) = 0;
      }
      *(undefined1 *)(param_1 + 0xa77bd0) = 0;
    }
  }
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa77bf2) = 0;
  if (2 < iVar1) {
    printk("Set_EthConvertMode_Proc(): EthConvertMode=%d!\n",*(undefined1 *)(param_1 + 0xa77bcf));
  }
  return 1;
}

