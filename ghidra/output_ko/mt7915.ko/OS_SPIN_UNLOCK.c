// module: mt7915.ko
// function: OS_SPIN_UNLOCK @ 0x2451b4
// size: 4 bytes
//

void OS_SPIN_UNLOCK(void)

{
  _raw_spin_unlock();
  return;
}

