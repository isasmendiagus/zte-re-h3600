// module: mt7915.ko
// function: Set_BeaconReq_RandInt_Proc @ 0x21f5d8
// size: 40 bytes
//

undefined4
Set_BeaconReq_RandInt_Proc
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bcn_rand_int = simple_strtol(param_2,0,10,param_4,param_4);
  return 1;
}

