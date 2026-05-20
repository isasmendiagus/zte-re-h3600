// module: mt7915.ko
// function: hqa_close_adapter @ 0x2474a4
// size: 40 bytes
//

undefined4 hqa_close_adapter(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = mt_serv_stop();
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

