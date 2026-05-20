// module: mt7915.ko
// function: Set_TxBfProfilePnRead @ 0xe8774
// size: 40 bytes
//

void Set_TxBfProfilePnRead(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  TxBfProfilePnRead(param_1,uVar1);
  return;
}

