// module: mt7915.ko
// function: Send_BTM_Rsp @ 0x66730
// size: 516 bytes
//

undefined4 Send_BTM_Rsp(int *param_1,void *param_2,void *param_3,size_t param_4)

{
  undefined1 *puVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  undefined1 *local_2c [2];
  
  uVar4 = *(uint *)(*param_1 + 0x3c);
  uVar5 = uVar4 & 0xff;
  if (0 < DebugLevel) {
    printk(&_LC255,"Send_BTM_Rsp");
  }
  piVar3 = param_1 + uVar5 * 0x84dec + 0x16037b;
  down_interruptible(piVar3);
  piVar6 = (int *)param_1[uVar5 * 0x84dec + 0x16038a];
  while( true ) {
    if (piVar6 == param_1 + uVar5 * 0x84dec + 0x16038a) {
      up(piVar3);
      if (-1 < DebugLevel) {
        printk(" %s BTMPeerEntry not found\n","Send_BTM_Rsp");
      }
      return 0;
    }
    iVar2 = memcmp((void *)((int)piVar6 + 0xd),param_2,6);
    if (iVar2 == 0) break;
    piVar6 = (int *)*piVar6;
  }
  iVar2 = param_4 + 0xc;
  up(piVar3);
  os_alloc_mem(0,local_2c,iVar2);
  if (local_2c[0] == (undefined1 *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s Not available memory\n","Send_BTM_Rsp");
    return 0;
  }
  if (iVar2 != 0) {
    __memzero(local_2c[0],iVar2);
  }
  puVar1 = local_2c[0];
  *local_2c[0] = (char)uVar4;
  memmove(local_2c[0] + 1,param_2,6);
  puVar1[8] = 0;
  puVar1[7] = 5;
  puVar1[9] = *(undefined1 *)((int)piVar6 + 0x13);
  *(short *)(puVar1 + 10) = (short)param_4;
  memmove(puVar1 + 0xc,param_3,param_4);
  if (0 < DebugLevel) {
    printk("\n %s before adding BSS Transition Candidate List Entries::BTMRspLen=%d, Len=%d\n",
           "Send_BTM_Rsp",param_4,iVar2);
  }
  MlmeEnqueue(param_1,0x28,5,iVar2,local_2c[0],0);
  os_free_mem(local_2c[0]);
  return 1;
}

