// module: mt7915.ko
// function: Set_ApCli_Twt_Proc @ 0x30a74
// size: 1088 bytes
//

undefined4 Set_ApCli_Twt_Proc(int *param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort local_82 [4];
  short local_7a;
  ushort local_78;
  short local_76;
  undefined2 local_74;
  undefined2 local_72;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_4e;
  int *local_4d;
  undefined1 local_49;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar3 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  memset(&local_4e,0,0x26);
  if (((*(int *)(*param_1 + 0x38) == 0x400) &&
      (uVar4 = (uint)*(byte *)(*param_1 + 0x3c), param_1[uVar4 * 0x84dec + 0x15fff1] != 0)) &&
     (iVar2 = rstrtok(param_2,&_LC194), iVar2 != 0)) {
    do {
      uVar1 = simple_strtol(iVar2,0,10);
      local_82[uVar3] = uVar1;
      iVar2 = rstrtok(0,&_LC194);
      uVar3 = uVar3 + 1 & 0xff;
    } while (iVar2 != 0);
    if (uVar3 == 2 || uVar3 == 9) {
      uVar5 = (uint)local_82[0];
      if (uVar5 - 5 < 3 && uVar3 == 2) {
        if (((0 < DebugLevel) && (printk("Action=%d\n",uVar5), 0 < DebugLevel)) &&
           (printk("TWT Flow ID=%d\n",local_82[1]), 0 < DebugLevel)) {
          printk("ucBssIdx=%d\n",*(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x36e4f1));
        }
        if (7 < local_82[1]) {
          return 0;
        }
        local_49 = (undefined1)local_82[1];
        local_70 = CONCAT31(CONCAT21(CONCAT11(local_70._3_1_,local_49),(char)local_82[0]),
                            *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x36e4f1));
      }
      else {
        if (uVar3 != 9) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("wrong argc for update agrt: %d\n",uVar3);
          return 0;
        }
        if (((-1 < DebugLevel) && (printk("Action bitmap=%d\n",uVar5), 0 < DebugLevel)) &&
           ((printk("TWT Flow ID=%d Setup Command=%d Trig enabled=%d\n",local_82[1],local_82[2],
                    local_82[3]), 0 < DebugLevel &&
            (((printk("Unannounced enabled=%d Wake Interval Exponent=%d\n",local_7a,local_78),
              0 < DebugLevel &&
              (printk("Protection enabled=%d Duration=%d\n",local_76,local_74), 0 < DebugLevel)) &&
             (printk("Wake Interval Mantissa=%d\n",local_72), 0 < DebugLevel)))))) {
          printk("ucBssIdx=%d\n",*(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x36e4f1));
        }
        if (((7 < local_82[1]) || (2 < local_82[2])) || (0x1f < local_78)) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("Invalid TWT Params\n");
          return 0;
        }
        __memzero(&local_68,0x18);
        local_49 = (undefined1)local_82[1];
        local_70 = CONCAT31(CONCAT21(CONCAT11(local_70._3_1_,local_49),(char)local_82[0]),
                            *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x36e4f1));
        local_64 = CONCAT22(CONCAT11(local_64._3_1_,(char)local_78),
                            CONCAT11((undefined1)local_74,(char)local_82[2]));
        local_60 = CONCAT22(local_60._2_2_,local_72);
        local_68 = CONCAT31(CONCAT12(local_7a != 0,CONCAT11(local_76 != 0,local_82[3] != 0)),1);
      }
      local_48 = local_70;
      local_44 = local_6c;
      local_4d = param_1 + uVar4 * 0x84dec + 0xdb6d6;
      local_40 = local_68;
      local_3c = local_64;
      local_38 = local_60;
      local_34 = local_5c;
      local_30 = local_58;
      local_2c = local_54;
      local_4e = 9;
      MlmeEnqueueWithWdev(param_1,9,0x1e,0x26,&local_4e,0,local_4d);
      RtmpOsMlmeUp(param_1 + 0xa18a6);
    }
  }
  return 0;
}

