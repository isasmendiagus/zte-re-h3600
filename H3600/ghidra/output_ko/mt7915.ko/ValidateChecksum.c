// module: mt7915.ko
// function: ValidateChecksum @ 0x1e5320
// size: 364 bytes
//

bool ValidateChecksum(uint param_1)

{
  uint uVar1;
  
  uVar1 = (param_1 / 1000000) % 10 + (param_1 / 10000) % 10 + param_1 % 10 + (param_1 / 100) % 10 +
          ((param_1 / 100000) % 10 + (param_1 / 10000000) % 10 + (param_1 / 1000) % 10 +
          (param_1 / 10) % 10) * 3;
  return uVar1 == (uVar1 / 10) * 10;
}

