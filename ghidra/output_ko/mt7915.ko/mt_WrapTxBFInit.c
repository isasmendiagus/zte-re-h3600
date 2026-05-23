// module: mt7915.ko
// function: mt_WrapTxBFInit @ 0x8a3c8
// size: 56 bytes
//

void mt_WrapTxBFInit(int param_1,int param_2)

{
  undefined1 local_3a [2];
  undefined1 auStack_38 [6];
  undefined1 local_32;
  
  local_32 = (undefined1)*(undefined4 *)(param_1 + 0x79599c);
  mt_TxBFInit(param_1,auStack_38,local_3a);
  *(undefined1 *)(param_2 + 0xc10) = local_3a[0];
  return;
}

