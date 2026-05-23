// module: mt7915.ko
// function: scan_partial_trigger_checker @ 0x144194
// size: 616 bytes
//

void scan_partial_trigger_checker(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *__src;
  int iVar7;
  size_t sVar8;
  undefined4 *puVar9;
  undefined1 auStack_51 [6];
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 auStack_48 [36];
  
  __src = (void *)(param_1 + 0x829274);
  do {
    iVar7 = *(int *)((int)__src + 0xaf5d0);
    if ((((iVar7 == 0) || (*(char *)(iVar7 + 0xbb4) == '\0')) || (*(int *)((int)__src + 0x8c) != 3))
       || ((*(uint *)(param_1 + 0xa39f84) & 0x4000) != 0)) {
      if ((*(char *)((int)__src + 0x178) == '\x01') &&
         (puVar9 = *(undefined4 **)((int)__src + 0x1b8), puVar9 != (undefined4 *)0x0)) {
        if (0 < DebugLevel) {
          uVar5 = *puVar9;
          uVar1 = *(undefined1 *)((int)__src + 0x179);
          uVar2 = *(undefined1 *)((int)puVar9 + 0xbb6);
          uVar6 = *(undefined4 *)((int)__src + 0x17c);
          uVar3 = scan_in_run_state(param_1,puVar9);
          printk("%s, %u,(%s) NumOfChannels = %u, LastScanChannel = %u, bScanning = %u, BreakTime = %u[%d]\n"
                 ,"scan_partial_trigger_checker",0x5ad,uVar5,uVar1,uVar2,1,uVar6,uVar3);
        }
        iVar7 = scan_in_run_state(param_1,puVar9);
        uVar4 = *(uint *)((int)__src + 0x17c);
        if (iVar7 == 0) {
          uVar4 = uVar4 + 1;
        }
        *(uint *)((int)__src + 0x17c) = uVar4 & 3;
        if (((uVar4 & 3) == 0) && (iVar7 = scan_in_run_state(param_1,puVar9), iVar7 == 0)) {
          __memzero(auStack_51,0x29);
          sVar8 = (size_t)*(byte *)((int)__src + -1);
          __memzero(auStack_48,0x20);
          if (0x1f < sVar8) {
            sVar8 = 0x20;
          }
          local_49 = (undefined1)sVar8;
          memmove(auStack_48,__src,sVar8);
          local_4b = 2;
          local_4a = 8;
          MlmeEnqueueWithWdev(param_1,4,2,0x29,auStack_51,0,puVar9);
          RtmpOsMlmeUp(param_1 + 0x286298);
        }
      }
    }
    else {
      __memzero(auStack_51,0x29);
      sVar8 = (size_t)*(byte *)((int)__src + -1);
      __memzero(auStack_48,0x20);
      if (0x1f < sVar8) {
        sVar8 = 0x20;
      }
      local_49 = (undefined1)sVar8;
      memmove(auStack_48,__src,sVar8);
      local_4b = 2;
      local_4a = 7;
      MlmeEnqueueWithWdev(param_1,4,2,0x29,auStack_51,0,iVar7);
      RtmpOsMlmeUp(param_1 + 0x286298);
      if (0 < DebugLevel) {
        printk("bImprovedScan ............. Resume for bImprovedScan, SCAN_PENDING ..............\n"
              );
      }
    }
    __src = (void *)((int)__src + 0xaf5d8);
  } while (__src != (void *)(param_1 + 0x987e24));
  return;
}

