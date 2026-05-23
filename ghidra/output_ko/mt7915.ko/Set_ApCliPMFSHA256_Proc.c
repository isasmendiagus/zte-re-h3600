// module: mt7915.ko
// function: Set_ApCliPMFSHA256_Proc @ 0x21bcf8
// size: 252 bytes
//

undefined4 Set_ApCliPMFSHA256_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (*param_2 != '\0') {
    iVar2 = *(int *)(*param_1 + 0x3c);
    if (param_1 + iVar2 * 0x84dec != (int *)0xffc9209c) {
      iVar1 = os_str_tol(param_2,0,10);
      if (iVar1 == 0) {
        *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36df69) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36df69) = 1;
      }
      if (-1 < DebugLevel) {
        printk("[PMF]%s:: Desired PMFSHA256=%d\n","Set_ApCliPMFSHA256_Proc",
               *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x36df69),
               param_1 + iVar2 * 0x84dec + 0xdb7d8,param_4);
        return 1;
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("[PMF]%s:: pPmfCfg=%p\n","Set_ApCliPMFSHA256_Proc",0,DebugLevel,param_4);
      return 0;
    }
  }
  return 0;
}

