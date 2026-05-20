// module: mt7915.ko
// function: RtmpOSNetDevCreate @ 0x244458
// size: 656 bytes
//

char * RtmpOSNetDevCreate(void)

{
  char *__dest;
  int iVar1;
  size_t __n;
  size_t sVar2;
  int iVar3;
  int in_r3;
  undefined4 in_stack_00000000;
  char *in_stack_00000004;
  char in_stack_00000008;
  char *local_48;
  undefined4 local_44;
  char acStack_40 [16];
  char acStack_30 [20];
  
  local_48 = (char *)0x0;
  local_44 = 0;
  iVar1 = RtmpOSNetDevAlloc(&local_48,in_stack_00000000);
  if (iVar1 == 0) {
    iVar1 = RtmpOSNetDevOpsAlloc(&local_44);
    if (iVar1 == 0) {
      if (2 < DebugLevel) {
        printk("Allocate net device ops success!\n");
      }
      __dest = local_48;
      *(undefined4 *)(local_48 + 300) = local_44;
      __n = strlen(in_stack_00000004);
      if (0xf < (int)__n) {
        printk(&_LC26,0x637);
        dump_stack();
      }
      for (; in_r3 < 0x20; in_r3 = in_r3 + 1) {
        __memzero(acStack_40,0x10);
        __memzero(acStack_30,0x10);
        strncpy(acStack_30,in_stack_00000004,__n);
        sprintf(acStack_40,"%d",in_r3);
        sVar2 = strlen(acStack_40);
        if (0xf < (int)(__n + sVar2)) {
          printk(&_LC28,0x64c);
          dump_stack();
        }
        if (in_stack_00000008 == '\0') {
          iVar1 = dev_get_by_name(&init_net);
          in_r3 = 0x20;
          if (iVar1 == 0) {
LAB_002445e4:
            strncpy(__dest,acStack_30,0x10);
            if (2 < DebugLevel) {
              printk("The name of the new %s interface is %s\n",in_stack_00000004,local_48);
            }
            return local_48;
          }
          if (-1 < DebugLevel) {
            in_r3 = 0x20;
            printk("Cannot request DevName with string(%s) from OS!\n",in_stack_00000004);
          }
        }
        else {
          strcat(acStack_30,acStack_40);
          iVar1 = dev_get_by_name(&init_net,acStack_30);
          if (iVar1 == 0) goto LAB_002445e4;
        }
        disableIRQinterrupts();
        iVar3 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
        *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) + -1;
      }
      if ((-1 < DebugLevel) &&
         (printk("Cannot request DevName with preifx(%s) and in range(0~32) as suffix from OS!\n",
                 in_stack_00000004), -1 < DebugLevel)) {
        printk("Assign inf name (%s with suffix 0~32) failed\n",in_stack_00000004);
      }
    }
    else if (2 < DebugLevel) {
      printk("Allocate net device ops fail!\n");
    }
    RtmpOSNetDevFree(local_48);
  }
  else if (-1 < DebugLevel) {
    printk("Allocate network device fail (%s)...\n",in_stack_00000004);
  }
  return (char *)0x0;
}

