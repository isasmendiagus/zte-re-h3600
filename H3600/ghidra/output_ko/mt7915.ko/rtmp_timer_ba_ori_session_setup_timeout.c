// module: mt7915.ko
// function: rtmp_timer_ba_ori_session_setup_timeout @ 0xa63d0
// size: 540 bytes
//

void rtmp_timer_ba_ori_session_setup_timeout(int param_1)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  ushort local_3a;
  undefined4 local_38;
  undefined2 local_34;
  ushort local_32;
  ushort local_30;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2a;
  
  puVar2 = *(ushort **)(param_1 + 0x24);
  if ((puVar2 != (ushort *)0x0) && (*(int *)(puVar2 + 6) != 3)) {
    uVar5 = (uint)*puVar2;
    iVar4 = *(int *)(puVar2 + 0x22);
    iVar3 = iVar4 + uVar5 * 0x14c0 + 0xa1d20;
    if (iVar3 != 0) {
      if (*(int *)(iVar4 + uVar5 * 0x14c0 + 0xa1d28) != 0) {
        if ((*(int *)(puVar2 + 6) == 2) && ((byte)puVar2[3] < 8)) {
          if (*(char *)(iVar4 + 0x286285) == '\0') {
            iVar1 = GetStaCfgByWdev(iVar4);
            if (iVar1 == 0) {
              printk(&_LC43,0x102);
              dump_stack();
            }
            else if ((((*(uint *)(iVar1 + 0x212464) & 1) != 0) &&
                     ((*(uint *)(iVar4 + 0xa39f84) & 0x4000) != 0)) &&
                    ((*(uint *)(iVar1 + 0x212464) & 0x80) != 0)) {
              RTMPSetTimer(puVar2 + 8,2000);
              goto LAB_000a6444;
            }
          }
          __memzero(&local_3a,0x12);
          local_38 = *(undefined4 *)(iVar3 + 0xec);
          local_34 = *(undefined2 *)(iVar3 + 0xf0);
          local_2e = (undefined1)puVar2[1];
          local_3a = *puVar2;
          local_32 = puVar2[2];
          local_30 = puVar2[5];
          local_2d = (undefined1)puVar2[3];
          local_2a = *(undefined1 *)((int)puVar2 + 7);
          MlmeEnqueueWithWdev(iVar4,9,0x17,0x12,&local_3a,0,
                              *(undefined4 *)(uVar5 * 0x14c0 + iVar4 + 0xa1d28));
          RtmpOsMlmeUp(iVar4 + 0x286298);
          if (2 < DebugLevel) {
            printk("BA Ori Session Timeout(%d) : Send ADD BA again\n",(char)puVar2[3]);
          }
          *(char *)(puVar2 + 3) = (char)puVar2[3] + '\x01';
          RTMPSetTimer(puVar2 + 8,2000);
        }
        else {
          ba_resrc_ori_del(iVar4,uVar5,(char)puVar2[1]);
        }
        goto LAB_000a6444;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s(): Entry is NULL\n","ba_ori_session_setup_timeout");
    }
  }
LAB_000a6444:
  if (*(char *)(param_1 + 0x1f) != '\0') {
    RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  }
  return;
}

