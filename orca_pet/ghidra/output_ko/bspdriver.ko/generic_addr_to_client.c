// module: bspdriver.ko
// function: generic_addr_to_client @ 0x10008
// size: 244 bytes
//

int generic_addr_to_client(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &i2c_list;
  iVar1 = 0;
  do {
    if ((*piVar3 != 0) && (piVar3[1] == param_1)) {
      return (&DAT_00011018)[iVar1 * 3];
    }
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 3;
  } while (iVar1 != 4);
  iVar1 = bus_find_device(&i2c_bus_type,0,param_1,generic_i2c_match,param_4);
  if ((iVar1 != 0) && (iVar1 = i2c_verify_client(), iVar1 != 0)) {
    iVar2 = 0;
    if (i2c_list != 0) {
      if (DAT_0001101c == 0) {
        iVar2 = 1;
      }
      else if (DAT_00011028 == 0) {
        iVar2 = 2;
      }
      else if (DAT_00011034 == 0) {
        iVar2 = 3;
      }
      else {
        iVar2 = 0;
      }
    }
    (&i2c_list)[iVar2 * 3] = 1;
    (&DAT_00011018)[iVar2 * 3] = iVar1;
    (&DAT_00011014)[iVar2 * 3] = param_1;
    return iVar1;
  }
  return 0;
}

