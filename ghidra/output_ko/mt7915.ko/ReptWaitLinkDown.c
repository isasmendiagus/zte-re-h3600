// module: mt7915.ko
// function: ReptWaitLinkDown @ 0x80cd8
// size: 92 bytes
//

void ReptWaitLinkDown(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_1 == '\0') {
    return;
  }
  uVar1 = RTMPMsecsToJiffies(5000);
  iVar2 = wait_for_completion_timeout(param_1 + 0x9c,uVar1);
  if (iVar2 != 0) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("(%s) ApCli Rept[%d] can\'t done.\n","ReptWaitLinkDown",param_1[4]);
  return;
}

