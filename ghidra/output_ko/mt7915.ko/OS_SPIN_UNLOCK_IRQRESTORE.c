// module: mt7915.ko
// function: OS_SPIN_UNLOCK_IRQRESTORE @ 0x2451a8
// size: 8 bytes
//

void OS_SPIN_UNLOCK_IRQRESTORE(undefined4 param_1,undefined4 *param_2)

{
  _raw_spin_unlock_irqrestore(param_1,*param_2);
  return;
}

