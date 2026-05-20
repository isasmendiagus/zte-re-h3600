// module: mt7915.ko
// function: MtAsicSetWmmParam @ 0x1997c4
// size: 304 bytes
//

undefined4
MtAsicSetWmmParam(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4,undefined2 param_5
                 )

{
  uint uVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined1 auStack_198 [188];
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined1 auStack_d0 [188];
  
  uVar1 = param_3;
  if (param_3 < 4) {
    uVar1 = param_2;
  }
  if (uVar1 < 4) {
    param_3 = param_3 + param_2 * 4;
  }
  else if (2 < DebugLevel) {
    printk("%s(): Non-WMM Queue, WmmIdx/QueIdx=%d/%d!\n","MtAsicSetWmmParam",param_2,param_3);
  }
  uVar2 = (undefined1)param_3;
  os_zero_mem(&local_dc,0xc4);
  uVar3 = CONCAT31(local_d8._1_3_,uVar2);
  local_dc = CONCAT22(local_dc._2_2_,1);
  switch(param_4) {
  case 0:
    local_d4 = CONCAT22(param_5,(undefined2)local_d4);
    local_d8._0_2_ = CONCAT11(8,uVar2);
    break;
  case 1:
    local_d8._0_2_ = CONCAT11(1,uVar2);
    local_d8 = CONCAT22(CONCAT11(local_d8._3_1_,(undefined1)param_5),(undefined2)local_d8);
    break;
  case 2:
    local_d8 = CONCAT13((undefined1)param_5,(int3)uVar3);
    local_d8._0_2_ = CONCAT11(2,uVar2);
    break;
  case 3:
    local_d4 = CONCAT22(local_d4._2_2_,param_5);
    local_d8._0_2_ = CONCAT11(4,uVar2);
    break;
  default:
    local_d8 = uVar3;
    if (0 < DebugLevel) {
      printk("%s(%d): Error type=%d\n","MtAsicSetWmmParam",0x51d,param_4);
    }
  }
  memcpy(auStack_198,auStack_d0,0xb8);
  MtCmdEdcaParameterSet(param_1,local_dc,local_d8,local_d4);
  return 0;
}

