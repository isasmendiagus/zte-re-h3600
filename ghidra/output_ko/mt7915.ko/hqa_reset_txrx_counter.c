// module: mt7915.ko
// function: hqa_reset_txrx_counter @ 0x247400
// size: 40 bytes
//

undefined4 hqa_reset_txrx_counter(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = mt_serv_reset_txrx_counter();
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

