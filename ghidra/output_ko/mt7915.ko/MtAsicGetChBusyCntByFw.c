// module: mt7915.ko
// function: MtAsicGetChBusyCntByFw @ 0x199a44
// size: 28 bytes
//

undefined4 MtAsicGetChBusyCntByFw(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_c [2];
  
  MtCmdGetChBusyCnt(param_1,param_2,local_c);
  return local_c[0];
}

