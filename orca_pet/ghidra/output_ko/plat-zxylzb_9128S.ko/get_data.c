// module: plat-zxylzb_9128S.ko
// function: get_data @ 0x11aa8
// size: 212 bytes
//

int get_data(undefined4 param_1,undefined4 param_2,uint param_3,char *param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_4 == (char *)0x0) {
    param_4 = "unkown";
  }
  if (param_3 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = myfile_lseek_constprop_14();
    if (iVar1 < 0) {
      printk("Unable to seek to 0x%lx for %s\n",param_2,param_4);
      iVar1 = 0;
    }
    else if ((param_3 < 0x200000) && (iVar1 = __kmalloc(param_3,0xd0), iVar1 != 0)) {
      uVar2 = myfile_read(param_1,iVar1,param_3);
      if (uVar2 != param_3) {
        printk("Unable to read in 0x%lx bytes of %s\n",param_3,param_4);
        kfree(iVar1);
        iVar1 = 0;
      }
    }
    else {
      printk("Out of memory allocating 0x%lx bytes for %s\n",param_3,param_4);
      iVar1 = 0;
    }
  }
  return iVar1;
}

