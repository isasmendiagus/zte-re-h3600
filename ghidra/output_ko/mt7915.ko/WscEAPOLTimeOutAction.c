// module: mt7915.ko
// function: WscEAPOLTimeOutAction @ 0x1ea1d4
// size: 2044 bytes
//

void WscEAPOLTimeOutAction(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 uStack_29;
  int local_28;
  int *local_24;
  
  local_28 = 0;
  local_24 = (int *)0x0;
  if (2 < DebugLevel) {
    printk("-----> WscEAPOLTimeOutAction\n");
  }
  if (param_2 == 0) {
    printk(&_LC201,0xfd7);
    dump_stack();
    return;
  }
  iVar6 = *(int *)(param_2 + 0x29e8);
  if (iVar6 == 0) {
    printk(&_LC202,0xfde);
    dump_stack();
  }
  iVar4 = *(int *)(param_2 + 0x29ec);
  if (iVar4 == 0) {
    printk(&_LC68,0xfe0);
    dump_stack();
  }
  (**(code **)(*(int *)(iVar4 + 0x904) + 0xb8))(iVar6,param_2 + 0x1c55,iVar4,&local_24);
  if (*(int *)(iVar4 + 0x14) == 1 || *(int *)(iVar4 + 0x14) == 0x20) {
    if (local_24 == (int *)0x0) {
      iVar4 = *(int *)(param_2 + 0x10);
      if (iVar4 - 0x18U < 2) {
        *(undefined4 *)(param_2 + 0xc) = 0x22;
        *(undefined1 *)(param_2 + 0x29e4) = 0;
        *(undefined1 *)(param_2 + 0x418) = 1;
        if (*(char *)(param_2 + 0x1c5b) != '\0') {
          *(undefined1 *)(param_2 + 0x1c5b) = 0;
          RTMPCancelTimer(param_2 + 0x1c5c,&uStack_29);
          iVar4 = *(int *)(param_2 + 0x10);
        }
        WscTimeOutProcess(iVar6,0,iVar4,param_2);
      }
LAB_001ea460:
      *(undefined1 *)(param_2 + 0x27c8) = 0;
      __memzero(param_2 + 0x1c55,6);
      if (DebugLevel < 3) {
        return;
      }
      printk("sta is left.\n");
      goto joined_r0x001ea49c;
    }
    iVar7 = 0;
    iVar5 = 0;
  }
  else {
    iVar7 = GetStaCfgByWdev(iVar6,iVar4);
    if (iVar7 == 0) {
      return;
    }
    if (((*(uint *)(iVar6 + 0x795124) & 2) != 0) && (local_24 == (int *)0x0)) goto LAB_001ea460;
    iVar5 = 2;
  }
  if (*(char *)(param_2 + 0x27c8) == '\0') {
    *(undefined1 *)(param_2 + 0x1c53) = 0;
  }
  else {
    if (*(char *)(param_2 + 0x27c9) != '\0') {
      RTMPModTimer(param_2 + 0x27cc,5000);
      if (DebugLevel < 3) {
        return;
      }
      printk("EapolTimer Pending......\n");
      goto joined_r0x001ea49c;
    }
    os_alloc_mem(0,&local_28,*(ushort *)(param_2 + 0x2b26) + 0x400);
    if (local_28 != 0) {
      __memzero(local_28,0x400);
    }
    if (((iVar5 == 0) && (local_24 != (int *)0x0)) && (*local_24 == 0x20001)) {
      iVar2 = *(int *)(param_2 + 0x10);
      if ((iVar2 < 5) && (*(int *)(param_2 + 0x2a20) != 2)) {
        WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,10,param_2);
        goto switchD_001ea2f4_caseD_a;
      }
    }
    else {
      iVar2 = *(int *)(param_2 + 0x10);
    }
    if (2 < DebugLevel) {
      printk("WscState = %d\n");
      iVar2 = *(int *)(param_2 + 0x10);
    }
    iVar1 = DebugLevel;
    switch(iVar2) {
    case 9:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) {
        *(byte *)(param_2 + 0x1c53) = bVar3 + 1;
        if (iVar7 != 0) {
LAB_001ea728:
          if (*(char *)(iVar7 + 0x4060) == '\x01' && iVar5 != 0) goto LAB_001ea918;
        }
      }
      else {
        if (iVar7 != 0) {
          if (*(char *)(iVar7 + 0x4060) != '\x01') {
            *(byte *)(param_2 + 0x1c53) = bVar3 + 1;
            goto LAB_001ea728;
          }
          WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,9,param_2);
          break;
        }
        *(byte *)(param_2 + 0x1c53) = bVar3 + 1;
      }
      WscSendEapolStart(iVar6,local_24 + 0x3b,iVar5,iVar4);
LAB_001ea694:
      RTMPModTimer(param_2 + 0x27cc,5000);
      break;
    case 0xb:
      if (*(byte *)(param_2 + 0x1c53) < 2) {
        *(byte *)(param_2 + 0x1c53) = *(byte *)(param_2 + 0x1c53) + 1;
        RTMPModTimer(param_2 + 0x27cc,5000);
      }
      else {
        WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0xb,param_2);
      }
      break;
    case 0xc:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) {
        if (iVar5 == 0) {
          WscSendMessage(*(undefined4 *)(param_2 + 0x29e8),1,0,0,param_2,0,1);
          bVar3 = *(byte *)(param_2 + 0x1c53);
        }
        else if (iVar5 == 2) {
          WscSendEapRspId(iVar6,local_24,param_2);
          bVar3 = *(byte *)(param_2 + 0x1c53);
        }
        goto LAB_001ea794;
      }
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0xc,param_2);
      break;
    case 0xd:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) {
LAB_001ea7b0:
        if (*(int *)(param_2 + 0x2a20) == 1) {
          if (iVar5 == 0) {
            if (*local_24 == 0x20001) {
              WscSendMessage(*(undefined4 *)(param_2 + 0x29e8),4,param_2 + 0xae0,
                             *(undefined4 *)(param_2 + 0xadc),param_2,0,1);
            }
            else if (*local_24 == 2) {
              WscSendMessage(*(undefined4 *)(param_2 + 0x29e8),4,param_2 + 0xae0,
                             *(undefined4 *)(param_2 + 0xadc),param_2,1,2);
            }
          }
          else {
            if (iVar5 != 2) goto LAB_001ea794;
LAB_001ea814:
            WscSendMessage(*(undefined4 *)(param_2 + 0x29e8),4,param_2 + 0xae0,
                           *(undefined4 *)(param_2 + 0xadc),param_2,iVar5,iVar5);
          }
          bVar3 = *(byte *)(param_2 + 0x1c53);
        }
LAB_001ea794:
        *(byte *)(param_2 + 0x1c53) = bVar3 + 1;
        RTMPModTimer(param_2 + 0x27cc,5000);
      }
      else {
        WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0xf,param_2);
      }
      break;
    case 0x10:
      if (*(byte *)(param_2 + 0x1c53) < 3) {
        *(byte *)(param_2 + 0x1c53) = *(byte *)(param_2 + 0x1c53) + 1;
        if (iVar7 != 0 && iVar5 != 0) {
LAB_001ea918:
          WscSendEapolStart(iVar6,iVar7 + 0x212428,2,iVar4);
        }
        goto LAB_001ea694;
      }
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x10,param_2);
      break;
    case 0x11:
      if (*(byte *)(param_2 + 0x1c53) < 2) {
        *(byte *)(param_2 + 0x1c53) = *(byte *)(param_2 + 0x1c53) + 1;
        if (2 < iVar1) {
          printk("No PIN CODE, cannot send M2 out!\n");
        }
        goto LAB_001ea694;
      }
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x11,param_2);
      break;
    case 0x12:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) {
LAB_001ea788:
        if (*(int *)(param_2 + 0x2a20) == 4) {
          if (iVar5 == 0) {
LAB_001ea93c:
            WscSendMessage(*(undefined4 *)(param_2 + 0x29e8),4,param_2 + 0xae0,
                           *(undefined4 *)(param_2 + 0xadc),param_2,iVar5,1);
            bVar3 = *(byte *)(param_2 + 0x1c53);
          }
          else if (iVar5 == 2) {
            if ((*(uint *)(iVar6 + 0x795124) & 2) != 0) goto LAB_001ea93c;
            goto LAB_001ea814;
          }
        }
        goto LAB_001ea794;
      }
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x12,param_2);
      break;
    case 0x13:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea7b0;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x13,param_2);
      break;
    case 0x14:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea788;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x14,param_2);
      break;
    case 0x15:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea7b0;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x15,param_2);
      break;
    case 0x16:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea788;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x16,param_2);
      break;
    case 0x17:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea7b0;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x17,param_2);
      break;
    case 0x18:
      bVar3 = *(byte *)(param_2 + 0x1c53);
      if (bVar3 < 2) goto LAB_001ea788;
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x18,param_2);
      break;
    case 0x19:
      WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x19,param_2);
      break;
    case 0x1a:
      if (*(char *)(param_2 + 0x1c53) == '\0') {
        RTMPModTimer(param_2 + 0x27cc,1000);
        *(char *)(param_2 + 0x1c53) = *(char *)(param_2 + 0x1c53) + '\x01';
      }
      else {
        WscTimeOutProcess(*(undefined4 *)(param_2 + 0x29e8),local_24,0x1a,param_2);
      }
    }
  }
switchD_001ea2f4_caseD_a:
  if (local_28 != 0) {
    os_free_mem();
  }
joined_r0x001ea49c:
  if (2 < DebugLevel) {
    printk("<----- WscEAPOLTimeOutAction\n");
  }
  return;
}

