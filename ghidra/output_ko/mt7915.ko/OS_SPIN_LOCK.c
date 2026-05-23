// module: mt7915.ko
// function: OS_SPIN_LOCK @ 0x2451b0
// size: 4 bytes
//

void OS_SPIN_LOCK(void)

{
  _raw_spin_lock();
  return;
}

