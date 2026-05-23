// module: mt7915.ko
// function: StaSiteSurvey @ 0x144688
// size: 280 bytes
//

void StaSiteSurvey(int param_1,size_t *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  size_t __n;
  undefined1 auStack_41 [6];
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 auStack_38 [36];
  
  iVar1 = GetStaCfgByWdev(param_1,param_4);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) == 0) {
    if ((iVar1 == 0) || ((*(uint *)(iVar1 + 0x212464) & 1) == 0)) {
      if (param_3 == 3) {
        param_3 = 0;
      }
    }
    else {
      param_3 = 7;
    }
    RTMPZeroMemory(auStack_38,0x20);
    local_39 = 0;
    if ((param_2 != (size_t *)0x0) && (__n = *param_2, __n - 1 < 0x20)) {
      local_39 = (undefined1)__n;
      memcpy(auStack_38,param_2 + 1,__n);
    }
    local_3a = (undefined1)param_3;
    local_3b = 2;
    if (0 < DebugLevel) {
      printk(&_LC1,"StaSiteSurvey");
    }
    cntl_scan_request(param_4,auStack_41);
    return;
  }
  if (2 < DebugLevel) {
    printk("StaSiteSurvey:: Scanning now\n");
  }
  return;
}

