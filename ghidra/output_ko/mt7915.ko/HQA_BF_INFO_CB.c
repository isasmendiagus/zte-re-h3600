// module: mt7915.ko
// function: HQA_BF_INFO_CB @ 0x27b588
// size: 304 bytes
//

void HQA_BF_INFO_CB(int param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined1 *__src;
  size_t __n;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 0x400) != 0) {
    *(undefined4 *)(param_1 + 0xa3ae10) = 0;
    os_alloc_mem(param_1,param_1 + 0xa3ae0c);
    if (*(int *)(param_1 + 0xa3ae0c) != 0) {
      os_zero_mem(*(int *)(param_1 + 0xa3ae0c),param_3);
      *(undefined4 *)(param_1 + 0xa3ae10) = param_3;
      __src = param_2 + 8;
      switch(*param_2) {
      case 0x10:
        if (param_2[4] == '\0') {
          __n = 0x10;
        }
        else {
          __n = 0x1c;
        }
        memmove(*(void **)(param_1 + 0xa3ae0c),__src,__n);
        *(size_t *)(param_1 + 0xa3ae10) = __n;
        break;
      case 0x11:
        memmove(*(void **)(param_1 + 0xa3ae0c),__src,0x14);
        *(undefined4 *)(param_1 + 0xa3ae10) = 0x14;
        break;
      default:
        break;
      case 0x15:
        *(undefined1 *)(param_1 + 0xa3ae14) = param_2[4];
        break;
      case 0x16:
        memmove(*(void **)(param_1 + 0xa3ae0c),__src,0x38);
        *(undefined4 *)(param_1 + 0xa3ae10) = 0x38;
      }
    }
    if (2 < DebugLevel) {
      printk("%s(%x)\n","HQA_BF_INFO_CB");
    }
    complete(param_1 + 0xa3ba38);
    return;
  }
  return;
}

