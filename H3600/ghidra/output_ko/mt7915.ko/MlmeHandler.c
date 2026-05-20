// module: mt7915.ko
// function: MlmeHandler @ 0x12ec88
// size: 1232 bytes
//

void MlmeHandler(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_40;
  void *local_3c;
  int local_38;
  int local_34;
  void *local_2c [2];
  
  local_40 = param_1 + 0x790000;
  iVar6 = param_1 + 0x7960f4;
  local_2c[0] = (void *)0x0;
  _raw_spin_lock_bh(iVar6);
  if (*(char *)(param_1 + 0x7960f0) != '\0') {
    _raw_spin_unlock_bh(iVar6);
    return;
  }
  *(undefined1 *)(param_1 + 0x7960f0) = 1;
  _raw_spin_unlock_bh(iVar6);
  local_38 = param_1 + 0x7960c8;
  local_34 = param_1 + 0x79541c;
  uVar4 = 0;
LAB_0012ed1c:
  do {
    _raw_spin_lock_bh(param_1 + 0x796104);
    iVar5 = *(int *)(param_1 + 0x7960f8);
    _raw_spin_unlock_bh(param_1 + 0x796104);
    if (iVar5 == 0) {
LAB_0012ef08:
      _raw_spin_lock_bh(iVar6);
      *(undefined1 *)(local_40 + 0x60f0) = 0;
      _raw_spin_unlock_bh(iVar6);
      return;
    }
    if ((*(uint *)(param_1 + 0xa39f84) & 0x30000140) != 0x10000000) {
      if (2 < DebugLevel) {
        printk("System halted, removed or MlmeRest, exit MlmeTask!(QNum = %ld)\n",
               *(undefined4 *)(param_1 + 0x7960f8));
      }
      goto LAB_0012ef08;
    }
    if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
       ((*(int *)(param_1 + 0xa77bb4) == 1 &&
        ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
      if (3 < DebugLevel) {
        printk("%s(): Driver is in ATE mode\n","MlmeHandler");
      }
      goto LAB_0012ef08;
    }
    uVar4 = uVar4 + 1;
    if (0x3f < uVar4 && (*(uint *)(((uint)&local_40 & 0xffffe000) + 4) & 0x1fff00) == 0) {
      schedule();
      uVar4 = 0;
    }
    iVar5 = MlmeDequeue(param_1 + 0x7960f8,local_2c);
    if (iVar5 == 0) break;
    pvVar3 = *(void **)((int)local_2c[0] + 0x92c);
    if (*(char *)(param_1 + 0x286285) == '\0') {
      local_3c = pvVar3;
      GetStaCfgByWdev(param_1,pvVar3);
      pvVar3 = local_3c;
    }
    switch(*(undefined4 *)((int)local_2c[0] + 0x900)) {
    case 1:
      StateMachinePerformAction
                (param_1,(int)pvVar3 + 0xbd0,local_2c[0],*(undefined4 *)((int)pvVar3 + 0xbdc));
      break;
    case 2:
      StateMachinePerformAction
                (param_1,(int)pvVar3 + 0xe24,local_2c[0],*(undefined4 *)((int)pvVar3 + 0xe30));
      break;
    default:
      if (2 < DebugLevel) {
        printk("%s(): Illegal SM %ld\n","MlmeHandler",*(undefined4 *)((int)local_2c[0] + 0x900));
      }
      break;
    case 4:
      iVar5 = get_scan_ctrl_by_wdev(param_1,pvVar3);
      StateMachinePerformAction(param_1,iVar5 + 0x84,local_2c[0],*(undefined4 *)(iVar5 + 0x90));
      break;
    case 5:
      StateMachinePerformAction
                (param_1,(int)pvVar3 + 0xc9c,local_2c[0],*(undefined4 *)((int)pvVar3 + 0xca8));
      break;
    case 9:
      StateMachinePerformAction
                (param_1,param_1 + 0x795ba0,local_2c[0],*(undefined4 *)(local_40 + 0x5bac));
      break;
    case 0x11:
      local_3c = (void *)(local_40 + 0x4000);
      if (*(int *)(local_40 + 0x4b20) != 0) {
        _raw_spin_lock_bh(param_1 + 0x794b1c);
        memmove(*(void **)((int)local_3c + 0xb20),local_2c[0],0x930);
        _raw_spin_unlock_bh(param_1 + 0x794b1c);
        RtmpOsTaskWakeUp(param_1 + 0x794ae8);
      }
      break;
    case 0x17:
      StateMachinePerformAction
                (param_1,param_1 + 0x796094,local_2c[0],*(undefined4 *)(param_1 + 0x7960a0));
      break;
    case 0x27:
      local_3c = local_2c[0];
      uVar1 = GASPeerCurrentState(param_1,local_2c[0]);
      uVar2 = 0x5bdc;
      goto LAB_0012ef98;
    case 0x28:
      local_3c = local_2c[0];
      uVar1 = BTMPeerCurrentState(param_1,local_2c[0]);
      uVar2 = 0x5d78;
      goto LAB_0012ef98;
    case 0x2b:
      StateMachinePerformAction
                (param_1,param_1 + 0xa79178,local_2c[0],*(undefined4 *)(param_1 + 0xa79184));
      break;
    case 0x2c:
      StateMachinePerformAction(param_1,local_34,local_2c[0],*(undefined4 *)(local_40 + 0x5428));
      break;
    case 0x2e:
      uVar1 = HcGetBandByWdev(pvVar3);
      iVar5 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
      StateMachinePerformAction(param_1,iVar5 + 0x4c,local_2c[0],*(undefined4 *)(iVar5 + 0x58));
      break;
    case 0x30:
      local_3c = local_2c[0];
      uVar1 = NRPeerCurrentState(param_1,local_2c[0]);
      uVar2 = 0x5d48;
      goto LAB_0012ef98;
    case 0x31:
      local_3c = local_2c[0];
      uVar1 = BCNPeerCurrentState(param_1,local_2c[0]);
      uVar2 = 0x5d0c;
LAB_0012ef98:
      StateMachinePerformAction(param_1,param_1 + (uVar2 | 0x790000),local_3c,uVar1);
      break;
    case 0x34:
      StateMachinePerformAction(param_1,local_38,local_2c[0],*(undefined4 *)(param_1 + 0x7960d4));
    }
    *(undefined1 *)((int)local_2c[0] + 0x922) = 0;
    *(undefined4 *)((int)local_2c[0] + 0x908) = 0;
  } while( true );
  if (-1 < DebugLevel) {
    printk("%s(): MlmeQ empty\n","MlmeHandler");
  }
  goto LAB_0012ed1c;
}

