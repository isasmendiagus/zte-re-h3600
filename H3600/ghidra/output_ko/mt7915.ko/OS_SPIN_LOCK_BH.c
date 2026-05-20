// module: mt7915.ko
// function: OS_SPIN_LOCK_BH @ 0x2451b8
// size: 4 bytes
//

void OS_SPIN_LOCK_BH(void)

{
  _raw_spin_lock_bh();
  return;
}

