// module: mt7915.ko
// function: Show_WifiSysInfo_Proc @ 0xdb114
// size: 16 bytes
//

undefined4 Show_WifiSysInfo_Proc(void)

{
  wifi_sys_dump();
  return 1;
}

