// module: mt7915.ko
// function: hqa_open_adapter @ 0x2474cc
// size: 40 bytes
//

undefined4 hqa_open_adapter(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = mt_serv_start();
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

