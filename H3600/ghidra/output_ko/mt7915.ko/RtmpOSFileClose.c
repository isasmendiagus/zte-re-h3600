// module: mt7915.ko
// function: RtmpOSFileClose @ 0x243d6c
// size: 20 bytes
//

undefined4
RtmpOSFileClose(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  filp_close(param_1,0,param_3,param_4,param_4);
  return 0;
}

