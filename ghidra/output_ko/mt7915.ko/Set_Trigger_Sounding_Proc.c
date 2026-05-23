// module: mt7915.ko
// function: Set_Trigger_Sounding_Proc @ 0xe5ad8
// size: 396 bytes
//

bool Set_Trigger_Sounding_Proc(int param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  size_t sVar3;
  byte *__s;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  byte local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_1f = 0;
  local_1e = 0;
  local_1d = 0;
  local_1c = 0;
  local_1b = 0;
  local_1a = 0;
  local_19 = 0;
  sVar3 = strlen(param_2);
  if (sVar3 == 0x14) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      puVar6 = &local_1f;
      do {
        sVar3 = strlen((char *)__s);
        if (sVar3 != 2) {
          return false;
        }
        if (((&_ctype)[*__s] & 0x44) == 0) {
          return false;
        }
        if (((&_ctype)[__s[1]] & 0x44) == 0) {
          return false;
        }
        AtoH(__s,puVar6);
        __s = (byte *)rstrtok(0,&_LC232);
        puVar6 = puVar6 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar2 = local_1e;
    uVar1 = local_1f;
    uVar5 = (uint)local_1d;
    local_23 = local_1c;
    local_22 = local_1b;
    local_21 = local_1a;
    local_20 = local_19;
    if (0x1f < (byte)"SetPartProfileParameters"[param_1 + 0x18]) {
      if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
         ((*(int *)(param_1 + 0xa77bb4) == 1 &&
          ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
        MtATESetMacTxRx(param_1,1,1,*(undefined1 *)(*(int *)(param_1 + 0xa77bb8) + 0x4cc));
      }
      iVar4 = mt_Trigger_Sounding_Packet(param_1,1,uVar5 << 2,uVar1,uVar2,&local_23);
      return iVar4 == 0;
    }
  }
  return false;
}

