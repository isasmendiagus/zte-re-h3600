// module: tm.ko
// function: tm_devOpen @ 0x10174
// size: 60 bytes
//

undefined4 tm_devOpen(void)

{
  undefined4 uVar1;
  
  if (tm_devOpened == 0) {
    tm_devOpened = 1;
    try_module_get(&__this_module);
    uVar1 = 0;
  }
  else {
    uVar1 = 0xfffffff0;
  }
  return uVar1;
}

