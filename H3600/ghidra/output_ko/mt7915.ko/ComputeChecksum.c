// module: mt7915.ko
// function: ComputeChecksum @ 0xb7be0
// size: 384 bytes
//

int ComputeChecksum(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 * 10;
  return (int)(10 - ((uVar1 / 10000) % 10 + (uVar1 / 1000000) % 10 + (uVar1 / 100) % 10 +
                    ((uVar1 / 100000) % 10 + (uVar1 / 10000000) % 10 + (uVar1 / 1000) % 10 +
                    (uVar1 / 10) % 10) * 3) % 10) % 10;
}

