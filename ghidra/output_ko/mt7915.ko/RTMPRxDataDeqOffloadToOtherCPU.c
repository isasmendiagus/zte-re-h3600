// module: mt7915.ko
// function: RTMPRxDataDeqOffloadToOtherCPU @ 0xd34c0
// size: 28 bytes
//

void RTMPRxDataDeqOffloadToOtherCPU(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000d34d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10) + 8))(param_1,1,0);
  return;
}

