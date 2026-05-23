// module: mt7915.ko
// function: mt_TxBFInit @ 0x8540c
// size: 16 bytes
//

void mt_TxBFInit(undefined4 param_1,int param_2,undefined1 *param_3,int param_4)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if (param_4 != 0) {
    uVar1 = *(undefined1 *)(param_2 + 6);
  }
  *param_3 = uVar1;
  return;
}

