// module: mt7915.ko
// function: qm_exit @ 0xd3890
// size: 64 bytes
//

void qm_exit(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  unregister_wsys_notifier(param_1 + 0xa7bed4,"Get_RBIST_IQ_Data" + param_1);
                    /* WARNING: Could not recover jumptable at 0x000d38cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 4))(param_1);
  return;
}

