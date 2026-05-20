// module: mt7915.ko
// function: AsicSetRDG @ 0x132874
// size: 252 bytes
//

int AsicSetRDG(int param_1,undefined2 param_2,undefined1 param_3,int param_4,char param_5)

{
  int iVar1;
  code *pcVar2;
  undefined2 local_2c;
  undefined1 local_2a;
  undefined1 local_29;
  char local_28;
  undefined1 local_27;
  undefined4 local_24;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar2 = *(code **)(iVar1 + 0x1c);
  if (pcVar2 == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetRDG");
    return 0;
  }
  local_29 = (undefined1)param_4;
  local_28 = param_5;
  local_2c = param_2;
  local_2a = param_3;
  if (param_4 == 0 || param_5 == '\0') {
    local_27 = 0;
    local_24 = 0x60;
    iVar1 = (*pcVar2)(param_1,&local_2c);
    if (iVar1 == 1) {
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffefffff;
      return 1;
    }
  }
  else {
    local_24 = 0x80;
    local_27 = 1;
    iVar1 = (*pcVar2)(param_1,&local_2c);
    if (iVar1 == 1) {
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x100000;
      return 1;
    }
  }
  return iVar1;
}

