// module: mt7915.ko
// function: RTMPPreReadProfile @ 0x14f9c8
// size: 368 bytes
//

int RTMPPreReadProfile(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int local_28;
  undefined4 uStack_24;
  
  local_3c = 0;
  pcVar1 = (char *)get_dev_l2profile();
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    os_file_open(&local_38,pcVar1,0,0);
    if (local_28 == 0) {
      os_alloc_mem(param_1,&local_3c,0x8000);
      if (local_3c == 0) {
        iVar2 = 1;
      }
      else {
        os_zero_mem(local_3c,0x8000);
        iVar2 = os_file_read(local_38,uStack_34,uStack_30,uStack_2c,local_28,uStack_24,local_3c,
                             0x7fff);
        if (iVar2 < 1) {
          if (-1 < DebugLevel) {
            printk("Read file \"%s\" failed(errCode=%d)!\n",pcVar1,iVar2);
          }
        }
        else {
          RTMPSetPreProfileParameters(param_1,local_3c);
          iVar2 = 0;
        }
        os_free_mem(local_3c);
      }
      iVar3 = os_file_close(local_38,uStack_34,uStack_30,uStack_2c,local_28,uStack_24);
      if (iVar3 == 0) {
        return iVar2;
      }
      if (-1 < DebugLevel) {
        printk("Close file \"%s\" failed(errCode=%d)!\n",pcVar1,1);
      }
    }
    else if (-1 < DebugLevel) {
      printk("Open file \"%s\" failed!\n",pcVar1);
      return 1;
    }
  }
  return 1;
}

