// module: tm.ko
// function: aclRamInit @ 0x606dc
// size: 32 bytes
//

undefined4 aclRamInit(void)

{
  undefined4 uVar1;
  
  if (g_aclRamInited != '\0') {
    return 0;
  }
  uVar1 = aclRamInit_part_6();
  return uVar1;
}

