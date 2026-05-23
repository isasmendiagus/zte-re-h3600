// module: mt7915.ko
// function: WpsSmProcess @ 0x1eaa18
// size: 1784 bytes
//

void WpsSmProcess(int param_1,undefined4 *param_2)

{
  byte bVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 *__src;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  size_t sVar8;
  undefined4 *puVar9;
  bool bVar10;
  int *local_3c;
  undefined4 local_35;
  undefined4 local_31;
  uint local_2d;
  char local_29;
  
  iVar5 = param_2[0x24b];
  local_3c = (int *)0x0;
  if (iVar5 == 0) {
    printk(&_LC68,0x2b23);
    dump_stack();
  }
  iVar4 = param_2[0x241];
  if ((*(byte *)((int)param_2 + 1) & 3) == 3) {
    if (iVar4 != 0x24) {
      if (iVar4 == 0x22) {
        uVar6 = 0x2f;
        uVar7 = 0x2f;
        goto LAB_001eabdc;
      }
      if (iVar4 != 0x23) goto LAB_001eaa9c;
      goto LAB_001eaad8;
    }
    uVar6 = 0x29;
    uVar7 = uVar6;
  }
  else {
    uVar6 = 0x29;
    uVar7 = 0x29;
    if (iVar4 == 0x22) {
LAB_001eabdc:
      (**(code **)(*(int *)(iVar5 + 0x904) + 0xb8))(param_1,(int)param_2 + 10,iVar5,&local_3c);
      if (local_3c == (int *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s:: cannot find this entry(%02x:%02x:%02x:%02x:%02x:%02x)\n","WpsSmProcess",
               *(undefined1 *)((int)param_2 + 10),*(undefined1 *)((int)param_2 + 0xb),
               *(undefined1 *)(param_2 + 3),*(undefined1 *)((int)param_2 + 0xd),
               *(undefined1 *)((int)param_2 + 0xe),*(undefined1 *)((int)param_2 + 0xf));
        return;
      }
      iVar4 = param_2[0x241];
    }
    if (iVar4 != 0x24) {
      if (iVar4 != 0x23) {
        if (local_3c != (int *)0x0 && iVar4 == 0x22) {
          if ((*(byte *)((int)param_2 + 1) & 3) == 3) {
            puVar9 = (undefined4 *)((int)param_2 + 0x26);
          }
          else {
            puVar9 = param_2 + 8;
          }
          if (-1 < DebugLevel) {
            printk("%s::  EAPOL Packet.  Code = %d.    Type = %d\n","WpsSmProcess",
                   *(undefined1 *)(puVar9 + 1),*(undefined1 *)(puVar9 + 2));
          }
          if (*(char *)(puVar9 + 1) == '\x04') {
            *param_2 = *(undefined4 *)((int)param_2 + 10);
            local_35._0_1_ = 'E';
            local_35._1_1_ = 'A';
            local_35._2_1_ = 'P';
            local_35._3_1_ = '_';
            local_31._0_1_ = 'F';
            local_31._1_1_ = 'A';
            local_31._2_1_ = 'I';
            local_31._3_1_ = 'L';
            builtin_strncpy((char *)((int)param_2 + 6),"EAP_",4);
            builtin_strncpy((char *)((int)param_2 + 10),"FAIL",4);
            *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)param_2 + 0xe);
            param_2[0x242] = 8;
            local_2d = local_2d & 0xffffff00;
            StateMachinePerformAction
                      (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
            return;
          }
          if (*(char *)(puVar9 + 1) == '\x01') {
            if (*(char *)(puVar9 + 2) == '\x01') {
              local_31 = CONCAT22(local_31._2_2_,0x6f);
              local_35._0_1_ = 'h';
              local_35._1_1_ = 'e';
              local_35._2_1_ = 'l';
              local_35._3_1_ = 'l';
              *(undefined1 *)(iVar5 + 0x2f34) = *(undefined1 *)((int)puVar9 + 5);
              *param_2 = *(undefined4 *)((int)param_2 + 10);
              *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)param_2 + 0xe);
              sVar8 = strlen((char *)&local_35);
              memcpy((void *)((int)param_2 + 6),&local_35,sVar8);
              param_2[0x242] = sVar8;
              StateMachinePerformAction
                        (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
              return;
            }
            if (*(char *)(puVar9 + 2) == -2) {
              uVar3 = param_2[0x242];
              if (uVar7 < uVar3) {
                __src = (undefined4 *)0x372a;
                *(undefined1 *)(iVar5 + 0x2f34) = *(undefined1 *)((int)puVar9 + 5);
                iVar4 = param_2[0x242] - uVar7;
                param_2[0x242] = iVar4;
                if (((uint)*(byte *)((int)puVar9 + 0xb) +
                     ((uint)*(byte *)((int)puVar9 + 10) + (uint)*(byte *)((int)puVar9 + 9) * 0x100)
                     * 0x100 != 0x372a) || (puVar9[3] != 0x1000000)) goto LAB_001eac78;
                *param_2 = *(undefined4 *)((int)param_2 + 10);
                *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)param_2 + 0xe);
                if (*(char *)(puVar9 + 4) == '\x06') goto LAB_001eaf6c;
                if (*(char *)(puVar9 + 4) == '\x01') {
                  param_2[0x242] = 9;
                  local_35._0_1_ = 'W';
                  local_35._1_1_ = 'S';
                  local_35._2_1_ = 'C';
                  local_35._3_1_ = '_';
                  local_31._0_1_ = 'S';
                  local_31._1_1_ = 'T';
                  local_31._2_1_ = 'A';
                  local_31._3_1_ = 'R';
                  local_2d = CONCAT22(local_2d._2_2_,0x54);
                  *(undefined1 *)((int)param_2 + 0xe) = 0x54;
                  builtin_strncpy((char *)((int)param_2 + 6),"WSC_",4);
                  builtin_strncpy((char *)((int)param_2 + 10),"STAR",4);
                  StateMachinePerformAction
                            (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4))
                  ;
                  return;
                }
                bVar10 = (*(byte *)((int)puVar9 + 0x11) & 2) != 0;
                if (bVar10) {
                  iVar4 = iVar4 + -0xb;
                  __src = puVar9 + 5;
                }
                else {
                  iVar4 = iVar4 + -9;
                }
                param_2[0x242] = iVar4;
                if (!bVar10) {
                  __src = (undefined4 *)((int)puVar9 + 0x12);
                }
                sVar8 = param_2[0x242];
                goto LAB_001ead20;
              }
              goto LAB_001eabb4;
            }
          }
          uVar3 = param_2[0x242];
          if (uVar7 < uVar3) {
            sVar8 = uVar3 - uVar7;
            param_2[0x242] = sVar8;
            *param_2 = *(undefined4 *)((int)param_2 + 10);
            *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)param_2 + 0xe);
            if (((*local_3c == 0x20001) && (*(char *)(puVar9 + 1) == '\x02')) &&
               (*(char *)(puVar9 + 2) == '\x01')) {
              pcVar2 = strstr((char *)((int)puVar9 + 9),"SimpleConfig");
              if (pcVar2 != (char *)0x0) {
                memmove((void *)((int)param_2 + 6),(char *)((int)puVar9 + 9),sVar8);
                StateMachinePerformAction
                          (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
                return;
              }
              if (2 < DebugLevel) {
                printk("RTMPCancelTimer EapolTimer!!\n");
              }
              __memzero(iVar5 + 0x2f39,6);
              *(undefined1 *)(iVar5 + 0x3aac) = 0;
              RTMPCancelTimer(iVar5 + 0x3ab0,&local_35);
              return;
            }
            if (((uint)*(byte *)((int)puVar9 + 0xb) +
                 ((uint)*(byte *)((int)puVar9 + 10) + (uint)*(byte *)((int)puVar9 + 9) * 0x100) *
                 0x100 != 0x372a) || (puVar9[3] != 0x1000000)) {
LAB_001eac78:
              if (DebugLevel < 3) {
                return;
              }
              printk("ERROR: WscCheckWSCHeader() return FALSE!\n");
              return;
            }
            if (*(char *)(puVar9 + 4) == '\x06') {
LAB_001eaf6c:
              local_35._0_1_ = 'W';
              local_35._1_1_ = 'S';
              local_35._2_1_ = 'C';
              local_35._3_1_ = '_';
              local_31._0_1_ = 'F';
              local_31._1_1_ = 'R';
              local_31._2_1_ = 'A';
              local_31._3_1_ = 'G';
              local_2d._0_1_ = '_';
              local_2d._1_1_ = 'A';
              local_2d._2_1_ = 'C';
              local_2d._3_1_ = 'K';
              builtin_strncpy((char *)((int)param_2 + 6),"WSC_",4);
              builtin_strncpy((char *)((int)param_2 + 10),"FRAG",4);
              builtin_strncpy((char *)((int)param_2 + 0xe),"_ACK",4);
              param_2[0x242] = 0xc;
              local_29 = '\0';
              StateMachinePerformAction
                        (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
              return;
            }
            if ((*(byte *)((int)puVar9 + 0x11) & 2) == 0) {
              __src = (undefined4 *)((int)puVar9 + 0x12);
              sVar8 = sVar8 - 9;
            }
            else {
              __src = puVar9 + 5;
              sVar8 = sVar8 - 0xb;
            }
            param_2[0x242] = sVar8;
LAB_001ead20:
            if (sVar8 + *(int *)(iVar5 + 0x3ecc) < 0x8fa) {
              memmove((void *)(*(int *)(iVar5 + 0x3ec8) + *(int *)(iVar5 + 0x3ecc)),__src,sVar8);
              *(int *)(iVar5 + 0x3ecc) = *(int *)(iVar5 + 0x3ecc) + param_2[0x242];
            }
            bVar1 = *(byte *)((int)puVar9 + 0x11);
            if ((bVar1 & 1) != 0) {
              WscSendEapFragAck(param_1,iVar5 + 0x12e4,local_3c);
              return;
            }
            memmove((void *)((int)param_2 + 6),*(void **)(iVar5 + 0x3ec8),
                    *(size_t *)(iVar5 + 0x3ecc));
            param_2[0x242] = *(undefined4 *)(iVar5 + 0x3ecc);
            StateMachinePerformAction
                      (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
            *(uint *)(iVar5 + 0x3ecc) = bVar1 & 1;
            __memzero(*(undefined4 *)(iVar5 + 0x3ec8),0x900);
            return;
          }
LAB_001eabb4:
          if (DebugLevel < 0) {
            return;
          }
          printk("Elem->MsgLen(%ld) <= HeaderLen(%d) !!\n",uVar3,uVar6);
          return;
        }
        goto LAB_001eaa9c;
      }
LAB_001eaad8:
      StateMachinePerformAction
                (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
      goto LAB_001eaa9c;
    }
  }
  if (uVar7 < (uint)param_2[0x242]) {
    sVar8 = param_2[0x242] - uVar7;
    param_2[0x242] = sVar8;
    local_35 = param_2[1];
    local_31 = CONCAT22(local_31._2_2_,*(undefined2 *)(param_2 + 2));
    *param_2 = local_35;
    *(undefined2 *)(param_2 + 1) = *(undefined2 *)(param_2 + 2);
    memmove((void *)((int)param_2 + 6),(void *)((int)param_2 + uVar6),sVar8);
    StateMachinePerformAction
              (param_1,param_1 + 0x795bb8,param_2,*(undefined4 *)(param_1 + 0x795bc4));
  }
LAB_001eaa9c:
  if (1 < DebugLevel) {
    printk("Unknow Message Type (=%lu)\n",param_2[0x241]);
  }
  return;
}

