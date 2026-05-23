// module: mt7915.ko
// function: MtCmdRfTestSolicitICapStatus @ 0x1ade7c
// size: 396 bytes
//

uint MtCmdRfTestSolicitICapStatus(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auStack_d0 [76];
  int *local_84;
  undefined4 local_80;
  int local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined1 auStack_64 [76];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestSolicitICapStatus");
  }
  uVar2 = 1;
  os_zero_mem(&local_70,0x58);
  local_6c = 0xc;
  local_84 = &local_74;
  local_80 = 0x44;
  local_70 = CONCAT31(local_70._1_3_,1);
  memcpy(auStack_d0,auStack_64,0x4c);
  FUN_001abb34(param_1,local_70,local_6c,uStack_68);
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar3 == 0x6867 ||
      ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622 || uVar3 == 0x7663))
  {
    if (local_74 != 0) {
      if (*(code **)(iVar1 + 400) == (code *)0x0) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s : The function is not hooked !!\n","MtCmdRfTestSolicitICapStatus");
      }
      else {
        uVar2 = (**(code **)(iVar1 + 400))(param_1);
      }
    }
  }
  else {
    uVar2 = (uint)(local_74 == 0);
  }
  if ((0 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","MtCmdRfTestSolicitICapStatus",uVar2), 2 < DebugLevel)) {
    printk("%s<-----------------\n","MtCmdRfTestSolicitICapStatus");
  }
  return uVar2;
}

