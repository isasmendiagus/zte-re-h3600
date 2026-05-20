// module: mt7915.ko
// function: OS_SPIN_LOCK_IRQ @ 0x2451c0
// size: 4 bytes
//

void OS_SPIN_LOCK_IRQ(void)

{
  _raw_spin_lock_irq();
  return;
}

