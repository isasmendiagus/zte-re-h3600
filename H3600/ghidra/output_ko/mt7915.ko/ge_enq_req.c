// module: mt7915.ko
// function: ge_enq_req @ 0xd22dc
// size: 772 bytes
//

undefined4 ge_enq_req(int param_1,undefined4 *param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  
  if (param_3 < 4) {
    sVar8 = *(short *)(param_4 + 8);
  }
  else {
    printk(&_LC32,0x2f2);
    dump_stack();
    sVar8 = *(short *)(param_4 + 8);
  }
  if (sVar8 == 0) {
    printk(&_LC33,0x2f3);
    dump_stack();
  }
  iVar6 = param_1 + param_3 * 4 + 0x28633c;
  _raw_spin_lock_bh(iVar6);
  if ((*(uint *)(param_4 + 0x74) < 0x4001) || (*(uint *)(param_4 + param_3 * 0x10 + 0x2c) < 0x1001))
  {
    iVar7 = *(int *)(param_1 + param_3 * 0x4018 + 0x28a34c);
    iVar5 = param_1 + (iVar7 + param_3 * 0x200c) * 2;
    sVar8 = *(short *)(iVar5 + 0x28634c);
    if ((sVar8 == 0) && (*(char *)(param_4 + 0xb8) != '\0')) {
      iVar3 = param_4 + param_3 * 4 + 0x94;
      _raw_spin_lock_bh(iVar3);
      iVar1 = param_4 + param_3 * 0x10;
      *(int *)(param_4 + 0x74) = *(int *)(param_4 + 0x74) + 1;
      *param_2 = 0;
      if (*(undefined4 **)(iVar1 + 0x28) == (undefined4 *)0x0) {
        *(undefined4 **)(iVar1 + 0x24) = param_2;
      }
      else {
        **(undefined4 **)(iVar1 + 0x28) = param_2;
      }
      iVar2 = param_4 + param_3 * 0x10;
      *(undefined4 **)(iVar1 + 0x28) = param_2;
      *(int *)(iVar2 + 0x2c) = *(int *)(iVar2 + 0x2c) + 1;
      _raw_spin_unlock_bh(iVar3);
      *(undefined2 *)(iVar5 + 0x28634c) = *(undefined2 *)(param_4 + 8);
      iVar5 = param_1 + param_3 * 0x4018;
      uVar4 = *(int *)(iVar5 + 0x28a34c) + 1;
      if (0x1fff < uVar4) {
        uVar4 = 0;
      }
      *(uint *)(iVar5 + 0x28a34c) = uVar4;
      if (((*(short *)(param_1 + (uVar4 + param_3 * 0x200c) * 2 + 0x28634c) != 0) &&
          ((*(uint *)(param_1 + 0xa39f84) & 0x200000) != 0)) &&
         (iVar5 = tx_flow_check_state(param_1,1,param_3), iVar5 == 0)) {
        tx_flow_set_state_block(param_1,0,1,1,param_3);
      }
      _raw_spin_unlock_bh(iVar6);
      if (DebugLevel < 4) {
        return 1;
      }
      printk("%s():EnqPkt(%p) for WCID(%d) to tx_swq[%d].swq[%d] %s\n","ge_enq_req",param_2,
             *(undefined2 *)(param_4 + 8),param_3,iVar7,"success");
      return 1;
    }
    *(int *)(param_1 + 0x9db68) = *(int *)(param_1 + 0x9db68) + 1;
  }
  else {
    iVar7 = 0;
    sVar8 = *(short *)(param_1 + param_3 * 0x4018 + 0x28634c);
    *(int *)(param_1 + 0x9db68) = *(int *)(param_1 + 0x9db68) + 1;
  }
  _raw_spin_unlock_bh(iVar6);
  if (3 < DebugLevel) {
    printk("%s():EnqPkt(%p) for WCID(%d) to tx_swq[%d].swq[%d] %s\n","ge_enq_req",param_2,
           *(undefined2 *)(param_4 + 8),param_3,iVar7,&_LC36);
  }
  if (2 < DebugLevel) {
    printk("\t FailedCause =>OccupiedWCID:%d,EnqCap:%d\n",sVar8,*(undefined1 *)(param_4 + 0xb8));
  }
  return 0;
}

