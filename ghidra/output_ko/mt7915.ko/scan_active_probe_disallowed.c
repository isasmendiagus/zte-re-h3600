// module: mt7915.ko
// function: scan_active_probe_disallowed @ 0x1435d8
// size: 28 bytes
//

bool scan_active_probe_disallowed
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = CHAN_PropertyCheck(param_1,param_2,2,param_4,param_4);
  return iVar1 == 1;
}

