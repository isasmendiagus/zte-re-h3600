// module: mt7915.ko
// function: IgmpPktClone @ 0x241fa4
// size: 1224 bytes
//

undefined4
IgmpPktClone(int param_1,int param_2,int param_3,int param_4,int param_5,undefined1 param_6,
            undefined1 param_7)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *local_5c;
  void *local_4c;
  undefined1 local_32;
  undefined1 uStack_31;
  undefined1 auStack_30 [2];
  ushort local_2e;
  int local_2c [2];
  
  bVar2 = param_4 == 2;
  local_2c[0] = 2;
  local_2e = 0x4b;
  iVar7 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_32 = 0;
  if (param_5 == 0 && bVar2) {
    return 1;
  }
  local_4c = (void *)(*(int *)(param_3 + 0xcc) + 6);
  iVar3 = RoutingTabLookup(param_1,*(undefined1 *)(param_2 + 0xe),local_4c,0,&local_2e);
  if (((iVar3 != 0) && ((*(uint *)(iVar3 + 4) & 1) != 0)) && (local_2e < 0x4b)) {
    local_4c = (void *)((uint)local_2e * 0x14c0 + param_1 + 0xa1e0c);
  }
  if (bVar2) {
    local_5c = *(int **)(param_5 + 0x18);
    if (local_5c != (int *)0x0) {
      piVar4 = (int *)APSsPsInquiry(param_1,local_5c + 1,local_2c,auStack_30,&local_32,&uStack_31);
LAB_00242194:
LAB_002421ac:
      do {
        if (((piVar4 == (int *)0x0) || (local_2c[0] != 2)) ||
           (uVar1 = *(ushort *)(piVar4 + 0x38),
           *(char *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) != '\x01')) {
LAB_002421c0:
          if (bVar2) {
LAB_00242294:
            local_5c = (int *)*local_5c;
            if (local_5c == (int *)0x0) {
              return 0;
            }
            piVar4 = (int *)APSsPsInquiry(param_1,local_5c + 1,local_2c,auStack_30,&local_32,
                                          &uStack_31);
            goto LAB_002421ac;
          }
          if (param_4 != 3) {
            return 0;
          }
          uVar6 = *(ushort *)(piVar4 + 0x38) + 1;
          if (uVar6 < 0x4b) {
            iVar3 = uVar6 * 0x14c0 + param_1 + 0xa1e0c;
            do {
              piVar4 = (int *)APSsPsInquiry(param_1,iVar3,local_2c,auStack_30,&local_32,&uStack_31);
              iVar3 = iVar3 + 0x14c0;
              if ((((piVar4 != (int *)0x0) && (*piVar4 == 0x20001)) && (param_2 == piVar4[2])) &&
                 (iVar5 = memcmp(local_4c,piVar4 + 0x3b,6), iVar5 != 0)) break;
              uVar6 = uVar6 + 1;
            } while (uVar6 != 0x4b);
          }
        }
        else {
          iVar3 = skb_copy(param_3,0x20);
          g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
          if (iVar3 != 0) {
            if (param_4 == 3) {
              memmove(*(void **)(iVar3 + 0xcc),piVar4 + 0x3b,6);
              *(short *)(iVar3 + 0x42) = (short)piVar4[0x38];
LAB_00242388:
              *(byte *)(iVar3 + 0x4e) = *(byte *)(iVar3 + 0x4e) | 4;
            }
            else {
              *(short *)(iVar3 + 0x42) = (short)piVar4[0x38];
              if ((bVar2) && (*(char *)((int)local_5c + 10) == '\0')) goto LAB_00242388;
            }
            *(undefined1 *)(iVar3 + 0x2a) = param_7;
            (**(code **)(iVar7 + 0x24))(param_1,param_2,iVar3,param_6);
            ba_ori_session_start(param_1,param_1 + (uint)uVar1 * 0x620 + 0x2f6a0,param_7);
            goto LAB_002421c0;
          }
          if (bVar2) goto LAB_00242294;
          if (param_4 != 3) {
            return 0;
          }
          uVar6 = *(ushort *)(piVar4 + 0x38) + 1;
          if (uVar6 < 0x4b) {
            iVar3 = uVar6 * 0x14c0 + param_1 + 0xa1e0c;
            do {
              piVar4 = (int *)APSsPsInquiry(param_1,iVar3,local_2c,auStack_30,&local_32,&uStack_31);
              iVar3 = iVar3 + 0x14c0;
              if (((piVar4 != (int *)0x0) && (*piVar4 == 0x20001)) &&
                 ((param_2 == piVar4[2] && (iVar5 = memcmp(local_4c,piVar4 + 0x3b,6), iVar5 != 0))))
              break;
              uVar6 = uVar6 + 1;
            } while (uVar6 != 0x4b);
          }
        }
      } while (uVar6 != 0x4b);
    }
  }
  else {
    if (param_4 != 3) {
      return 1;
    }
    iVar3 = param_1 + 0xa32cc;
    do {
      piVar4 = (int *)APSsPsInquiry(param_1,iVar3,local_2c,auStack_30,&local_32,&uStack_31);
      iVar3 = iVar3 + 0x14c0;
      if (((piVar4 != (int *)0x0) && (*piVar4 == 0x20001)) &&
         ((param_2 == piVar4[2] && (iVar5 = memcmp(local_4c,piVar4 + 0x3b,6), iVar5 != 0)))) {
        local_5c = (int *)0x0;
        goto LAB_00242194;
      }
    } while (iVar3 != param_1 + 0x10324c);
  }
  return 0;
}

