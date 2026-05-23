// module: mt7915.ko
// function: RTEnqueueInternalCmd @ 0xc49bc
// size: 480 bytes
//

undefined4 RTEnqueueInternalCmd(int param_1,undefined4 param_2,void *param_3,size_t param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_20;
  undefined4 *local_1c [2];
  
  local_20 = 0;
  local_1c[0] = (undefined4 *)0x0;
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0) {
    iVar2 = os_alloc_mem(param_1,local_1c,0x14);
    if ((iVar2 != 0) || (local_1c[0] == (undefined4 *)0x0)) {
      return 3;
    }
    __memzero(local_1c[0],0x14);
    if (param_4 == 0) {
      local_1c[0][1] = 0;
      local_1c[0][2] = 0;
    }
    else {
      iVar2 = os_alloc_mem(param_1,local_1c[0] + 1,param_4);
      if ((iVar2 != 0) || ((void *)local_1c[0][1] == (void *)0x0)) {
        os_free_mem();
        return 3;
      }
      memmove((void *)local_1c[0][1],param_3,param_4);
      local_1c[0][2] = param_4;
    }
    *local_1c[0] = param_2;
    *(undefined1 *)(local_1c[0] + 3) = 0;
    if (local_1c[0] != (undefined4 *)0x0) {
      iVar2 = (int)&DAT_00285c64 + param_1;
      OS_SPIN_LOCK_IRQSAVE(iVar2,&local_20);
      if ((*(uint *)(param_1 + 0x285c54) < 0x100) && ((*(uint *)(param_1 + 0x285c60) & 3) != 0)) {
        if (*(uint *)(param_1 + 0x285c54) == 0) {
          *(undefined4 **)(param_1 + 0x285c58) = local_1c[0];
        }
        else {
          *(undefined4 **)(*(int *)(param_1 + 0x285c5c) + 0x10) = local_1c[0];
        }
        *(undefined4 **)(param_1 + 0x285c5c) = local_1c[0];
        local_1c[0][4] = 0;
        *(int *)(param_1 + 0x285c54) = *(int *)(param_1 + 0x285c54) + 1;
        OS_SPIN_UNLOCK_IRQRESTORE(iVar2,&local_20);
        RtmpOsCmdUp(mt_ate_ampdu_frame + param_1);
        return 0;
      }
      OS_SPIN_UNLOCK_IRQRESTORE(iVar2,&local_20);
      if (local_1c[0][1] != 0) {
        os_free_mem(local_1c[0][1]);
      }
      os_free_mem(local_1c[0]);
    }
    uVar1 = 0;
  }
  else if (DebugLevel < 3) {
    uVar1 = 1;
  }
  else {
    printk("--->RTEnqueueInternalCmd - NIC is not exist!!\n");
    uVar1 = 1;
  }
  return uVar1;
}

