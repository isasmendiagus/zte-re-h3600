// module: switch.ko
// function: TO_LAN @ 0x12bc8
// size: 32 bytes
//

bool TO_LAN(char *param_1)

{
  int iVar1;
  
  iVar1 = strncmp(param_1,"sw",2);
  return iVar1 == 0;
}

