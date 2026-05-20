// module: mt7915.ko
// function: Set_TxBfQdRead @ 0xe8ab0
// size: 44 bytes
//

undefined4 Set_TxBfQdRead(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = simple_strtol(param_2,0,10);
  TxBfQdRead(param_1,(int)cVar1);
  return 1;
}

