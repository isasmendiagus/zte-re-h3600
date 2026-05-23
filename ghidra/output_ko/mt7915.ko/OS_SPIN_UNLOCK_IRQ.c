// module: mt7915.ko
// function: OS_SPIN_UNLOCK_IRQ @ 0x2451c4
// size: 4 bytes
//

void OS_SPIN_UNLOCK_IRQ(void)

{
  _raw_spin_unlock_irq();
  return;
}

