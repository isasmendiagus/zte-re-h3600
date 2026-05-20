// module: mt7915.ko
// function: OS_SPIN_UNLOCK_BH @ 0x2451bc
// size: 4 bytes
//

void OS_SPIN_UNLOCK_BH(void)

{
  _raw_spin_unlock_bh();
  return;
}

