// module: mt7915.ko
// function: Set_TxBfDynamicDisable_Proc @ 0xe5a28
// size: 44 bytes
//

undefined4 Set_TxBfDynamicDisable_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = simple_strtol(param_2,0,10);
  DynamicTxBfDisable(param_1,uVar1);
  return 1;
}

