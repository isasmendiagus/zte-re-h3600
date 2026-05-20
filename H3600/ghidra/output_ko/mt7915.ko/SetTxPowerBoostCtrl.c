// module: mt7915.ko
// function: SetTxPowerBoostCtrl @ 0xc2e7c
// size: 812 bytes
//

undefined4 SetTxPowerBoostCtrl(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  uint uVar10;
  undefined2 local_3a;
  char *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar8 = 0;
  local_38 = (char *)0x0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_3a = 0;
  iVar2 = hc_get_arch_ops(param_1[0x29e5e8]);
  iVar3 = hc_get_chip_cap(param_1[0x29e5e8]);
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    uVar8 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    if (*(char *)((int)param_1 + 0x286285) == '\0') goto LAB_000c3044;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') goto joined_r0x000c3064;
LAB_000c3044:
    uVar8 = HcGetBandByWdev(param_1 + 0xdb6d6);
  }
  if (1 < uVar8) {
    return 0;
  }
joined_r0x000c3064:
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","SetTxPowerBoostCtrl");
    return 0;
  }
  local_38 = (char *)rstrtok(param_2,&_LC409);
  if (local_38 == (char *)0x0) {
    uVar10 = 0;
  }
  else {
    cVar9 = '\0';
    uVar10 = 0;
    do {
      if (cVar9 == '\0') {
        uVar10 = simple_strtol(local_38,0,10);
        uVar10 = uVar10 & 0xff;
        if (0 < DebugLevel) {
          printk("%s: ucBandIdx: %d, cPwrUpCat: %d\n","SetTxPowerBoostCtrl",uVar8,uVar10);
        }
      }
      else {
        pcVar4 = strsep(&local_38,":");
        if (pcVar4 != (char *)0x0) {
          uVar7 = 0;
          do {
            uVar1 = simple_strtol(pcVar4,0,10);
            *(undefined1 *)((int)&local_3a + uVar7) = uVar1;
            pcVar4 = strsep(&local_38,":");
            uVar6 = uVar7 ^ 1;
            uVar7 = 1;
            if (pcVar4 == (char *)0x0) {
              uVar6 = 0;
            }
          } while (uVar6 != 0);
        }
        if ((uint)*(byte *)(*(int *)(iVar3 + 0x20c) + uVar10) <= (uint)(byte)local_3a) {
          if (DebugLevel < 0) {
            return 0xffffffff;
          }
          printk("%s: set wrong parameters\n","SetTxPowerBoostCtrl");
          return 0xffffffff;
        }
        *(undefined1 *)((int)&local_34 + (uint)(byte)local_3a) = local_3a._1_1_;
      }
      cVar9 = cVar9 + '\x01';
      local_38 = (char *)rstrtok(0,&_LC409);
    } while (local_38 != (char *)0x0);
  }
  local_38 = (char *)0x0;
  if (iVar2 != 0) {
    if (*(code **)(iVar2 + 500) != (code *)0x0) {
      (**(code **)(iVar2 + 500))(param_1,uVar8,(int)(char)uVar10,&local_34);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: cPwrUpValue: (%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)-(%d)\n",
           "SetTxPowerBoostCtrl",(int)(char)local_34,(int)local_34._1_1_,(int)local_34._2_1_,
           (int)local_34._3_1_,(int)(char)local_30,(int)local_30._1_1_,(int)local_30._2_1_,
           (int)local_30._3_1_,(int)(char)local_2c,(int)local_2c._1_1_,(int)local_2c._2_1_,
           (int)local_2c._3_1_);
  }
  uVar5 = TxPwrUpCtrl(param_1,uVar8,(int)(char)uVar10,&local_34);
  return uVar5;
}

