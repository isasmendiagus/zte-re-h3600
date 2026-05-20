// module: plat-zxylzb_9128S.ko
// function: idm_creat_status_proc @ 0x1612c
// size: 88 bytes
//

void idm_creat_status_proc(void)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  
  uVar1 = proc_mkdir(&_LC43,0);
  iVar2 = proc_create_data(&_LC44,0x180,uVar1,idm_mode_fops,0);
  if (iVar2 == 0) {
    pcVar3 = "idm_status_proc failed!\n";
  }
  else {
    pcVar3 = "idm_status_proc success!\n";
  }
  printk(pcVar3);
  return;
}

