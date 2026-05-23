// module: mt7915.ko
// function: OS_SPIN_LOCK_IRQSAVE @ 0x245194
// size: 20 bytes
//

void OS_SPIN_LOCK_IRQSAVE(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = _raw_spin_lock_irqsave();
  *param_2 = uVar1;
  return;
}

