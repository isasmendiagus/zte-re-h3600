// module: mt7915.ko
// function: MtCmdSetRDDTestExt @ 0x1af014
// size: 236 bytes
//

void MtCmdSetRDDTestExt(int param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined1 auStack_c0 [72];
  undefined4 local_78;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [72];
  
  os_zero_mem(&local_6c,0x54);
  if (2 < DebugLevel) {
    printk("%s, rdd_num:%u, IsStart:%d\n","MtCmdSetRDDTestExt",param_2,param_4);
  }
  uVar1 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar1 - 0x7636 < 2 || (uVar1 == 0x7615 || uVar1 == 0x7915)) {
    local_6c = 10;
    local_68._0_3_ = CONCAT12(param_3,CONCAT11((char)param_2,(char)param_4));
    local_78 = 8;
    memcpy(auStack_c0,auStack_60,0x48);
    FUN_001ac150(param_1,local_6c,local_68,uStack_64);
    return;
  }
  MtCmdSetRDDTest(param_1,param_4);
  return;
}

