// module: mt7915.ko
// function: MtCmdRfTestUnSolicitICapStatus @ 0x1adda0
// size: 216 bytes
//

undefined4 MtCmdRfTestUnSolicitICapStatus(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 auStack_c8 [76];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined1 auStack_64 [80];
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestUnSolicitICapStatus");
  }
  os_zero_mem(&local_70,0x58);
  local_6c = 0xc;
  local_70 = CONCAT31(local_70._1_3_,1);
  local_7c = 0;
  local_78 = 8;
  memcpy(auStack_c8,auStack_64,0x4c);
  uVar1 = FUN_001abb34(param_1,local_70,local_6c,uStack_68);
  if (0 < DebugLevel) {
    printk("%s:(Status = %d)\n","MtCmdRfTestUnSolicitICapStatus",uVar1);
    if (2 < DebugLevel) {
      printk("%s<-----------------\n","MtCmdRfTestUnSolicitICapStatus");
    }
  }
  return uVar1;
}

