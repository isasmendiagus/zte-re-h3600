// module: mt7915.ko
// function: SetATETxBfPhaseE2pUpdate @ 0x267fb0
// size: 296 bytes
//

undefined4 SetATETxBfPhaseE2pUpdate(int param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  byte *__s;
  undefined1 *puVar5;
  undefined1 local_23;
  byte local_22;
  undefined1 local_21;
  
  local_23 = 0;
  local_22 = 0;
  local_21 = 0;
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 == (char *)0x0) || (sVar3 = strlen(param_2), sVar3 != 8)) {
LAB_00267ffc:
    uVar4 = 0;
  }
  else {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar5 = &local_23;
      do {
        sVar3 = strlen((char *)__s);
        if (((sVar3 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_00267ffc;
        AtoH(__s,puVar5);
        __s = (byte *)rstrtok(0,&_LC2);
        puVar5 = puVar5 + 1;
      } while (__s != (byte *)0x0);
    }
    bVar1 = local_22 >> 4;
    if ((bVar1 == 1) || ((bVar1 != 0 && (bVar1 == 2)))) {
      *(byte *)(param_1 + 0xa78730) = bVar1;
    }
    else {
      *(undefined1 *)(param_1 + 0xa78730) = 0;
    }
    (**(code **)(iVar2 + 0x144))(param_1,local_23,local_22,local_21);
    uVar4 = 1;
  }
  return uVar4;
}

