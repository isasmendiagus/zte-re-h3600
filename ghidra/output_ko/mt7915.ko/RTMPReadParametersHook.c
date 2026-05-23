// module: mt7915.ko
// function: RTMPReadParametersHook @ 0x14f818
// size: 432 bytes
//

int RTMPReadParametersHook(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int local_20;
  int local_1c;
  
  local_34 = 0;
  os_alloc_mem(param_1,&local_34,0x8000);
  if (local_34 == 0) {
    return 1;
  }
  os_zero_mem(local_34,0x8000);
  iVar1 = multi_profile_check(param_1,local_34);
  if (iVar1 == 0) {
    RTMPSetProfileParameters(param_1,local_34);
    iVar1 = 0;
    goto LAB_0014f884;
  }
  pcVar2 = (char *)get_dev_l2profile();
  if ((pcVar2 != (char *)0x0) && (*pcVar2 != '\0')) {
    os_file_open(&local_30,pcVar2,0,0);
    if (local_20 == 0) {
      if (local_1c == 0) {
        iVar1 = 0x7fff;
      }
      else {
        uVar4 = local_1c + 1;
        if (uVar4 < 0x8000) {
          uVar4 = 0x8000;
        }
        iVar1 = uVar4 - 1;
      }
      iVar1 = os_file_read(local_30,uStack_2c,uStack_28,uStack_24,0,local_1c,local_34,iVar1);
      if (iVar1 < 1) {
        if (-1 < DebugLevel) {
          printk("Read file \"%s\" failed(errCode=%d)!\n",pcVar2,iVar1);
        }
      }
      else {
        RTMPSetProfileParameters(param_1,local_34);
        iVar1 = 0;
      }
      iVar3 = os_file_close(local_30,uStack_2c,uStack_28,uStack_24,local_20,local_1c);
      if (iVar3 == 0) goto LAB_0014f884;
      if (-1 < DebugLevel) {
        printk("Close file \"%s\" failed(errCode=%d)!\n",pcVar2,1);
      }
    }
    else if (-1 < DebugLevel) {
      iVar1 = 1;
      printk("Open file \"%s\" failed!\n",pcVar2);
      goto LAB_0014f884;
    }
  }
  iVar1 = 1;
LAB_0014f884:
  if (local_34 != 0) {
    os_free_mem(local_34);
  }
  return iVar1;
}

