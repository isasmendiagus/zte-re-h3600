// module: mt7915.ko
// function: tm_exit @ 0x15096c
// size: 20 bytes
//

void tm_exit(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0015097c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10) + 4))();
  return;
}

