// module: mt7915.ko
// function: BigInteger_record_time_begin @ 0x1faf2c
// size: 20 bytes
//

void BigInteger_record_time_begin(int param_1)

{
  *(undefined4 *)(param_1 + 4) = jiffies;
  return;
}

