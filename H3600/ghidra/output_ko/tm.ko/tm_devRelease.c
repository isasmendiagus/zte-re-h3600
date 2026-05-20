// module: tm.ko
// function: tm_devRelease @ 0x10148
// size: 44 bytes
//

undefined4 tm_devRelease(void)

{
  tm_devOpened = tm_devOpened + -1;
  module_put(&__this_module);
  return 0;
}

