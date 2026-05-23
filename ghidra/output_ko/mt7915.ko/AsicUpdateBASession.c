// module: mt7915.ko
// function: AsicUpdateBASession @ 0x13373c
// size: 568 bytes
//

void AsicUpdateBASession(int param_1,int param_2,byte param_3,undefined2 param_4,undefined2 param_5,
                        char param_6,int param_7,undefined1 param_8)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_4e;
  undefined4 local_4a;
  undefined4 local_46;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(&local_40,0x18);
  local_3c._0_3_ = CONCAT12(param_6,param_5);
  local_38 = param_7;
  uStack_30 = CONCAT22(param_4,(undefined2)uStack_30);
  iVar3 = param_1 + param_2 * 0x14c0 + 0xa1d20;
  local_40._0_3_ = CONCAT12(param_3,(short)param_2);
  local_2c = CONCAT31(local_2c._1_3_,param_8);
  if ((iVar3 == 0) || (iVar4 = param_1 + param_2 * 0x14c0, *(int *)(iVar4 + 0xa1d28) == 0)) {
    local_3c = (uint)(uint3)local_3c;
    if (3 < DebugLevel) {
      printk("%s(): mac_entry=%p!Set BaCtrl.band_idx=%d\n","AsicUpdateBASession",iVar3);
    }
  }
  else {
    uVar2 = HcGetBandByWdev();
    local_3c = CONCAT13((char)uVar2,(uint3)local_3c);
    if (3 < DebugLevel) {
      printk("%s(): mac_entry=%p!mac_entry->wdev=%p, Set BaCtrl.band_idx=%d\n","AsicUpdateBASession"
             ,iVar3,*(undefined4 *)(iVar4 + 0xa1d28),uVar2);
    }
  }
  if (param_6 != '\0' && param_7 == 2) {
    os_move_mem(&uStack_34,(void *)(param_2 * 0x14c0 + param_1 + 0xa1e0c),6);
  }
  if (*(code **)(iVar1 + 0x140) != (code *)0x0) {
    (**(code **)(iVar1 + 0x140))(param_1,local_40,local_3c,local_38,uStack_34,uStack_30,local_2c);
    if ((iVar3 != 0 && *(code **)(iVar1 + 0x144) != (code *)0x0) &&
       (iVar3 = *(int *)(param_2 * 0x14c0 + param_1 + 0xa1d28), iVar3 != 0)) {
      local_46 = CONCAT22(param_5,param_4);
      local_4a = CONCAT31(CONCAT12(local_4a._3_1_,
                                   CONCAT11(param_6 << (uint)param_3,(undefined1)param_7)),param_3);
      local_4e = CONCAT22((short)param_2,
                          CONCAT11(*(undefined1 *)(iVar3 + 0x999),*(undefined1 *)(iVar3 + 0x29)));
      (**(code **)(iVar1 + 0x144))(param_1,local_4e,local_4a,local_46,param_8);
    }
    return;
  }
  AsicNotSupportFunc(param_1,"AsicUpdateBASession");
  return;
}

