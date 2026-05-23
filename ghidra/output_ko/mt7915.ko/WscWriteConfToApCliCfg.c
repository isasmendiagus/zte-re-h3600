// module: mt7915.ko
// function: WscWriteConfToApCliCfg @ 0x1e95dc
// size: 1108 bytes
//

void WscWriteConfToApCliCfg(int *param_1,int param_2,size_t *param_3)

{
  int iVar1;
  ushort uVar2;
  size_t sVar3;
  undefined4 uVar4;
  char *pcVar5;
  byte bVar6;
  void *pvVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  
  iVar12 = *param_1;
  uVar8 = *(undefined4 *)(iVar12 + 0x38);
  uVar11 = *(byte *)(param_2 + 0x1c54) & 0xf;
  uVar9 = *(undefined4 *)(iVar12 + 0x40);
  if ((*(byte *)(param_2 + 0x1c54) & 0xf) == 0 || uVar11 == 1) {
    *(undefined4 *)(iVar12 + 0x38) = 0x400;
    if (2 < DebugLevel) {
      printk("-----> WscWriteConfToApCliCfg (apcli%d)\n",uVar11);
    }
    iVar1 = uVar11 * 0x2137b0;
    pvVar7 = (void *)((int)param_1 + iVar1 + 0x57ff5e);
    __memzero(pvVar7,0x20);
    memmove(pvVar7,param_3 + 1,*param_3);
    pvVar7 = (void *)((int)param_1 + iVar1 + 0x580e3a);
    *(char *)((int)param_1 + iVar1 + 0x57ff7e) = (char)*param_3;
    __memzero(pvVar7,0x20);
    memmove(pvVar7,param_3 + 1,*param_3);
    *(char *)((int)param_1 + iVar1 + 0x580e5a) = (char)*param_3;
    __memzero(&DAT_00580e5b + (int)(param_1 + uVar11 * 0x84dec),6);
    if (0 < DebugLevel) {
      printk("AuthType: %d, EncrType: %d\n",(short)param_3[9],*(undefined2 *)((int)param_3 + 0x26));
    }
    if (((short)param_3[9] == 2 || (short)param_3[9] == 0x20) &&
       ((*(ushort *)((int)param_3 + 0x26) & 0xc) == 0)) {
      if (2 < DebugLevel) {
        printk(
              "AuthType is WPAPSK or WPA2PAK.\nGet illegal EncrType(%d) from External Registrar, set EncrType to TKIP\n"
              );
      }
      *(undefined2 *)((int)param_3 + 0x26) = 4;
    }
    *(int **)(iVar12 + 0x40) = param_1 + uVar11 * 0x84dec + 0xdb6e1;
    uVar4 = WscGetAuthTypeStr((short)param_3[9]);
    Set_SecAuthMode_Proc(param_1,uVar4);
    uVar10 = *(ushort *)((int)param_3 + 0x26) - 1 & 0xffff;
    if (uVar10 < 8) {
      pcVar5 = *(char **)(&DAT_002a10d8 + uVar10 * 4);
    }
    else {
      pcVar5 = "TKIPAES";
    }
    Set_SecEncrypType_Proc(param_1,pcVar5);
    uVar2 = *(ushort *)((int)param_3 + 0x26);
    if (uVar2 != 1) {
      if ((uVar2 & 0xc) == 0) {
        if (uVar2 == 2) {
          sVar3 = param_3[0x1a];
          bVar6 = (char)param_3[0x1c] - 1;
          if (bVar6 < 4) {
            *(byte *)(param_1 + uVar11 * 0x84dec + 0xdb734) = bVar6;
            if (((sVar3 & 0xfff7) == 5) || ((sVar3 & 0xffef) == 10)) {
              FUN_001e0784(param_1 + uVar11 * 0x84dec + 0xdb6e1,param_3);
            }
            else if (2 < DebugLevel) {
              printk("WEP: Invalid Key Length (%d)\n",(short)param_3[0x1a]);
            }
          }
          else {
            if (2 < DebugLevel) {
              printk("Unsupport default key index (%d), use key Index 1.\n",(int)(char)bVar6);
            }
            *(undefined1 *)(param_1 + uVar11 * 0x84dec + 0xdb734) = 0;
          }
        }
      }
      else {
        *(undefined1 *)(param_1 + uVar11 * 0x84dec + 0xdb734) = 0;
        iVar1 = DebugLevel;
        if ((ushort)param_3[0x1a] - 8 < 0x39) {
          *(uint *)(param_2 + 0x29e0) = (uint)(ushort)param_3[0x1a];
          __memzero((void *)(param_2 + 0x299d),0x40);
          pvVar7 = (void *)((int)param_1 + uVar11 * 0x2137b0 + 0x36dcd1);
          memmove((void *)(param_2 + 0x299d),param_3 + 10,*(size_t *)(param_2 + 0x29e0));
          os_zero_mem(pvVar7,0x41);
          os_move_mem(pvVar7,param_3 + 10,(uint)(ushort)param_3[0x1a]);
          if (2 < DebugLevel) {
            printk("WpaPskLen = %d\n",*(undefined4 *)(param_2 + 0x29e0));
          }
        }
        else {
          *(undefined4 *)(param_2 + 0x29e0) = 0;
          if (2 < iVar1) {
            printk("WPAPSK: Invalid Key Length (%d)\n",(short)param_3[0x1a]);
          }
        }
      }
    }
    if (1 < *(uint *)(param_2 + 0x1c90)) {
      *(undefined1 *)(param_2 + 0x2874) = 1;
      RTMPSetTimer(param_2 + 0x2878,10000);
    }
    iVar1 = DebugLevel;
    *(undefined4 *)(iVar12 + 0x38) = uVar8;
    *(undefined4 *)(iVar12 + 0x40) = uVar9;
    if (2 < iVar1) {
      printk("<----- WscWriteConfToApCliCfg\n");
      return;
    }
  }
  return;
}

