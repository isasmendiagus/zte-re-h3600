// module: mt7915.ko
// function: DfsDedicatedOutBandRDDStop @ 0x236118
// size: 36 bytes
//

void DfsDedicatedOutBandRDDStop(undefined4 param_1)

{
  mtRddControl(param_1,0,2,0,0);
  return;
}

