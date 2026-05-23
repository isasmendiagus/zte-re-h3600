// module: mt7915.ko
// function: Update2040CoexistFrameAndNotify @ 0xa3bdc
// size: 120 bytes
//

void Update2040CoexistFrameAndNotify
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (0 < DebugLevel) {
    printk("%s(): ACT -BSSCoexist2040 = %x. EventANo = %d.\n","Update2040CoexistFrameAndNotify",
           *(undefined1 *)(param_1 + 0x7956b5),*(undefined1 *)(param_1 + 0x7956b8));
  }
  *(undefined1 *)(param_1 + 0x7956b5) = 0;
  if (*(int *)(param_1 + 0x79593c) != 0) {
    *(undefined1 *)(param_1 + 0x7956b5) = 4;
  }
  Send2040CoexistAction(param_1,param_2,param_3,param_4);
  return;
}

