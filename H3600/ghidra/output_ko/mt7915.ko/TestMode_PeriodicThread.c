// module: mt7915.ko
// function: TestMode_PeriodicThread @ 0x27fd98
// size: 936 bytes
//

undefined4 TestMode_PeriodicThread(int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint local_68;
  uint local_64;
  int local_60;
  int local_5c;
  int *local_58;
  int local_54;
  undefined1 auStack_4c [4];
  uint local_48 [3];
  uint local_3c [3];
  undefined4 ****local_30;
  undefined4 ****local_2c;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar5 = *(int *)(param_1 + 0x10);
  if (iVar5 != 0) {
    local_58 = &DebugLevel;
    local_5c = param_1;
    if (3 < DebugLevel) {
      printk("%s: Periodic Thread running \n","TestMode_PeriodicThread");
    }
    complete(iVar5 + 0xa3ba38);
    if (*(char *)(local_5c + 0x18) == '\0') {
      iVar6 = RtmpOSTaskWait(iVar5,local_5c,auStack_4c);
      if (iVar6 == 0) {
        local_60 = iVar5 + 0xa30000;
        iVar6 = iVar5 + 0xa3b000;
        *(uint *)(iVar5 + 0xa39f84) = *(uint *)(iVar5 + 0xa39f84) | 0x40;
      }
      else {
        local_60 = iVar5 + 0xa30000;
        iVar6 = iVar5 + 0xa3b000;
        while (*(char *)(iVar6 + 0xae4) != '\0') {
          while( true ) {
            piVar2 = local_58;
            if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar5 + 0xc) & 0xffff) == 0x7626) {
              bVar1 = false;
              iVar7 = *(int *)(local_60 + 0x9fd4);
              local_48[0] = 0;
              local_3c[0] = 0;
              local_54 = iVar6;
              while( true ) {
                if (bVar1) {
                  uVar8 = 0x12;
                }
                else {
                  uVar8 = 2;
                }
                (**(code **)(iVar7 + 0xb0))(iVar5,uVar8,0xe3c,local_3c);
                (**(code **)(iVar7 + 0xb0))(iVar5,uVar8,0xc,local_48);
                if (3 < *piVar2) {
                  local_64 = (uint)((local_3c[0] & 3) != 0);
                  local_68 = local_48[0];
                  printk("%s(%d), rE3C=%x, regC:%x, unlock:%d\n","mt_ate_sx_inc_cal_ext",0x56c);
                }
                if ((local_3c[0] & 3) != 0) {
                  iVar6 = 0;
                  local_48[0] = local_48[0] | 0x20000;
                  do {
                    (**(code **)(iVar7 + 0xac))(iVar5,uVar8,0xc);
                    local_48[0] = local_48[0] | 0x10000;
                    if (3 < *piVar2) {
                      local_68 = uVar8;
                      local_64 = local_48[0];
                      printk("%s(%d), toggle #%d, WfSel:%d, regC:0x%x\n","mt_ate_sx_inc_cal_ext",
                             0x575,iVar6);
                    }
                    (**(code **)(iVar7 + 0xac))(iVar5,uVar8,0xc,local_48[0]);
                    iVar6 = iVar6 + 1;
                    local_48[0] = local_48[0] & 0xfffeffff;
                    (**(code **)(iVar7 + 0xac))(iVar5,uVar8,0xc);
                  } while (iVar6 != 10);
                  local_48[0] = local_48[0] & 0xfffffffe;
                  if (bVar1) {
                    uVar4 = 0x12;
                  }
                  else {
                    uVar4 = 2;
                  }
                  (**(code **)(iVar7 + 0xac))(iVar5,uVar4,0xc);
                }
                iVar6 = local_54;
                if (bVar1) break;
                bVar1 = true;
              }
            }
            if ((*(uint *)(((uint)&local_68 & 0xffffe000) + 4) & 0x1fff00) == 0) break;
            RtmpusecDelay(1000000);
            if (*(char *)(iVar6 + 0xae4) == '\0') goto LAB_0027fec4;
          }
          __init_waitqueue_head(local_48,"&_wait",&g_EBF_certification);
          iVar7 = 100;
          do {
            local_3c[0] = 0;
            local_30 = &local_30;
            local_2c = &local_30;
            for (iVar9 = 1; iVar3 = prepare_to_wait_event(local_48,local_3c,1),
                iVar9 != 0 && iVar3 == 0; iVar9 = schedule_timeout(iVar9)) {
            }
            finish_wait(local_48,local_3c);
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
LAB_0027fec4:
        schedule();
      }
    }
    else {
      local_60 = iVar5 + 0xa30000;
      iVar6 = iVar5 + 0xa3b000;
    }
    RtmpOSTaskNotifyToExit(local_5c);
    *(undefined1 *)(iVar6 + 0xaac) = 0;
    if (3 < *local_58) {
      printk("%s: leave, service_stat:%d\n","TestMode_PeriodicThread",*(undefined1 *)(iVar6 + 0xae4)
            );
    }
    *(uint *)(local_60 + 0x9f84) = *(uint *)(local_60 + 0x9f84) & 0xffffffbf;
  }
  return 0;
}

