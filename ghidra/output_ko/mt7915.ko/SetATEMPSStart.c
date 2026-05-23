// module: mt7915.ko
// function: SetATEMPSStart @ 0x260c88
// size: 116 bytes
//

bool SetATEMPSStart(int param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATEMPSStart",param_2);
  }
  iVar1 = simple_strtol(param_2,0,10);
  if (iVar1 == 0) {
    pcVar2 = *(code **)(iVar3 + 0xd4);
  }
  else {
    pcVar2 = *(code **)(iVar3 + 0xd0);
  }
  iVar3 = (*pcVar2)(param_1);
  return iVar3 == 0;
}

