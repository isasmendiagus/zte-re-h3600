// module: tm.ko
// function: tmUsrInterfaceCreate @ 0x78170
// size: 24 bytes
//

int tmUsrInterfaceCreate(void)

{
  int iVar1;
  
  iVar1 = tm_sysfs_init();
  return -(uint)(iVar1 == 0);
}

