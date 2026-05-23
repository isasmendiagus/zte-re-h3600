// module: mt7915.ko
// function: rt_ioctl_giwname @ 0x6c1b8
// size: 32 bytes
//

undefined4 rt_ioctl_giwname(undefined4 param_1,undefined4 param_2,char *param_3)

{
  strncpy(param_3,"Ralink STA",0x10);
  return 0;
}

