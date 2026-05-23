// module: mt7915.ko
// function: Set_Antenna_Proc @ 0xba690
// size: 340 bytes
//

undefined4 Set_Antenna_Proc(int param_1,byte *param_2)

{
  byte bVar1;
  size_t sVar2;
  int iVar3;
  byte *pbVar4;
  
  if (0 < DebugLevel) {
    printk("==> Set_Antenna_Proc *******************\n");
  }
  sVar2 = strlen((char *)param_2);
  pbVar4 = param_2;
  while (pbVar4 != param_2 + sVar2) {
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    if (((&_ctype)[bVar1] & 4) == 0) {
      return 0xffffffea;
    }
  }
  iVar3 = os_str_tol(param_2,0,10);
  if (iVar3 == 2) {
    AsicSetRxAnt(param_1,0,2);
    if (0 < DebugLevel) {
      printk("<== Set_Antenna_Proc(Fix in Ant CON1), (%d,%d)\n","RadarStateCheck"[param_1 + 0xe],
             "RadarStateCheck"[param_1 + 0xf]);
    }
  }
  else if (iVar3 == 3) {
    AsicSetRxAnt(param_1,1,3);
    if (0 < DebugLevel) {
      printk("<== %s(Fix in Ant CON2), (%d,%d)\n","Set_Antenna_Proc",
             "RadarStateCheck"[param_1 + 0xe],"RadarStateCheck"[param_1 + 0xf]);
      return 1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("<== %s(N/A cmd: %d), (%d,%d)\n","Set_Antenna_Proc",iVar3,
           "RadarStateCheck"[param_1 + 0xe],"RadarStateCheck"[param_1 + 0xf]);
    return 1;
  }
  return 1;
}

