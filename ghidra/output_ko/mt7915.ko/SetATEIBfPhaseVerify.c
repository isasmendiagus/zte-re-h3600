// module: mt7915.ko
// function: SetATEIBfPhaseVerify @ 0x267df8
// size: 436 bytes
//

undefined4 SetATEIBfPhaseVerify(int param_1,char *param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  size_t sVar7;
  byte *__s;
  int iVar8;
  undefined2 *puVar9;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  iVar6 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 != (char *)0x0) && (sVar7 = strlen(param_2), sVar7 == 0x11)) {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar9 = &local_2e;
      do {
        sVar7 = strlen((char *)__s);
        if (sVar7 != 2) {
          return 0;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return 0;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return 0;
        }
        AtoH(__s,puVar9);
        __s = (byte *)rstrtok(0,&_LC2);
        puVar9 = (undefined2 *)((int)puVar9 + 1);
      } while (__s != (byte *)0x0);
    }
    if (-1 < DebugLevel) {
      printk(&_LC324,"SetATEIBfPhaseVerify");
    }
    cVar1 = (char)local_2e;
    uVar3 = (undefined1)local_2c;
    uVar2 = local_2e._1_1_;
    uVar4 = local_2c._1_1_;
    uVar5 = (undefined1)local_2a;
    iVar8 = CmdITxBfPhaseComp(param_1,0,(char)local_2e == '\x01',(undefined1)local_2c,(char)local_2e
                              ,local_2a._1_1_,0);
    if (iVar8 == 0) {
      iVar8 = CmdITxBfPhaseCal(param_1,cVar1,uVar2,uVar3,uVar4,uVar5);
      if (iVar8 == 0) {
        return 1;
      }
      if (*(code **)(iVar6 + 0x140) != (code *)0x0) {
        (**(code **)(iVar6 + 0x140))(param_1);
        return 0;
      }
    }
    else if (*(code **)(iVar6 + 0x140) != (code *)0x0) {
      (**(code **)(iVar6 + 0x140))(param_1);
      return 0;
    }
  }
  return 0;
}

