// module: tm.ko
// function: tmUsrInterfaceRelease @ 0x78188
// size: 16 bytes
//

undefined4 tmUsrInterfaceRelease(void)

{
  tm_sysfs_delete();
  return 0;
}

