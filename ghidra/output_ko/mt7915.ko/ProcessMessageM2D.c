// module: mt7915.ko
// function: ProcessMessageM2D @ 0x1f84f4
// size: 1008 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 ProcessMessageM2D(undefined4 param_1,void *param_2,size_t param_3,char *param_4)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint __n;
  uint *__src;
  ushort uStack_23;
  
  *(size_t *)(param_4 + 0x1270) = param_3;
  puVar2 = memmove(param_4 + 0x1274,param_2,param_3);
  if (4 < (int)param_3) {
LAB_001f8540:
    do {
      uVar4 = *puVar2;
      uStack_23 = (ushort)(uVar4 >> 0x10);
      __n = (uStack_23 & 0xff) << 8 | (uint)(uStack_23 >> 8);
      if ((int)param_3 < (int)(__n + 4)) {
        if (DebugLevel < 3) {
          return 0;
        }
        printk("unexpected WSC IE Length(%u)\n",__n);
        break;
      }
      __src = puVar2 + 1;
      switch((uVar4 & 0xff) << 8 | uVar4 >> 8 & 0xff) {
      case 0x1002:
        puVar1 = puVar2 + 1;
        param_3 = (param_3 - 4) - __n;
        puVar2 = (uint *)((int)__src + __n);
        *(short *)(param_4 + 0x278) = (short)*puVar1;
        if ((int)param_3 < 5) goto LAB_001f870c;
        goto LAB_001f8540;
      default:
        if (2 < DebugLevel) {
          printk("ProcessMessageM2D --> Unknown IE 0x%04x\n");
        }
        goto switchD_001f8580_caseD_1005;
      case 0x1004:
        *(short *)(param_4 + 0x1c6) = (short)puVar2[1];
        break;
      case 0x1005:
      case 0x1012:
        goto switchD_001f8580_caseD_1005;
      case 0x1008:
        *(ushort *)(param_4 + 0x1cc) = (ushort)puVar2[1] << 8 | (ushort)puVar2[1] >> 8;
        break;
      case 0x1009:
        *(short *)(param_4 + 0x27c) = (short)puVar2[1];
        break;
      case 0x100d:
        param_4[0x1ca] = (char)puVar2[1];
        break;
      case 0x1010:
        *(short *)(param_4 + 0x1c8) = (short)puVar2[1];
        break;
      case 0x1011:
        memmove(param_4 + 0x18c,__src,__n);
        break;
      case 0x101a:
        iVar3 = RTMPCompareMemory(param_4 + 0x1ad0,__src,__n);
        if ((iVar3 != 0) && (2 < DebugLevel)) {
          printk("Rx M2 Compare enrollee nonce mismatched\n");
        }
        goto switchD_001f8580_caseD_1005;
      case 0x1021:
        memmove(param_4 + 0x1cf,__src,__n);
        break;
      case 0x1022:
        if (((char)puVar2[1] != '\x06') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
        goto switchD_001f8580_caseD_1005;
      case 0x1023:
        memmove(param_4 + 0x20f,__src,__n);
        break;
      case 0x1024:
        memmove(param_4 + 0x22f,__src,__n);
        break;
      case 0x102d:
        *(uint *)(param_4 + 0x270) = puVar2[1];
        break;
      case 0x1032:
        if (2 < DebugLevel) {
          printk("ProcessMessageM2D --> Receive WSC_ID_PUBLIC_KEY!! werid!\n");
        }
        goto switchD_001f8580_caseD_1005;
      case 0x1039:
        memmove(param_4 + 0x1ae0,__src,__n);
        break;
      case 0x103c:
        param_4[0x26f] = (char)puVar2[1];
        break;
      case 0x1042:
        memmove(param_4 + 0x24f,__src,__n);
        break;
      case 0x1048:
        memmove(param_4 + 0x176,__src,__n);
        break;
      case 0x104a:
        if ((*param_4 != (char)puVar2[1]) && (-1 < DebugLevel)) {
          printk("Rx WPS Message Version mismatched %02x\n");
        }
switchD_001f8580_caseD_1005:
        break;
      case 0x1054:
        memmove(param_4 + 0x1ac,__src,__n);
      }
      param_3 = (param_3 - 4) - __n;
      puVar2 = (uint *)((int)__src + __n);
    } while (4 < (int)param_3);
  }
LAB_001f870c:
  if (2 < DebugLevel) {
    printk("ProcessMessageM2D :\n");
  }
  return 0;
}

