// module: mt7915.ko
// function: fw_log_to_file @ 0x1d4f7c
// size: 220 bytes
//

undefined4 fw_log_to_file(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int local_20;
  undefined4 uStack_1c;
  
  os_file_open(&local_30,param_1 + 0xa7cc33,0x441,0);
  if (local_20 == 0) {
    os_file_write(local_30,uStack_2c,uStack_28,uStack_24,0,uStack_1c,*(undefined4 *)(param_2 + 4),
                  *(undefined4 *)(param_2 + 8));
    cVar1 = os_file_close(local_30,uStack_2c,uStack_28,uStack_24,local_20,uStack_1c);
    uVar2 = 0;
    if ((cVar1 != '\0') && (-1 < DebugLevel)) {
      printk("File Close Error ! Ret = %d\n",(int)cVar1);
    }
  }
  else if (DebugLevel < 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 1;
    printk("Open file \"%s\" failed!\n",param_1 + 0xa7cc33);
  }
  return uVar2;
}

