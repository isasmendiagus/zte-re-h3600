// module: mt7915.ko
// function: PMF_ExtractIGTKKDE @ 0x219f88
// size: 204 bytes
//

undefined4
PMF_ExtractIGTKKDE(undefined1 *param_1,int param_2,void *param_3,undefined1 *param_4,void *param_5,
                  undefined1 *param_6)

{
  size_t __n;
  
  __n = param_2 - 8;
  *param_6 = *param_1;
  memmove(param_5,param_1 + 2,6);
  if ((__n != 0x10) && (__n != 0x20)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s : the IGTK length(%d) is invalid\n","PMF_ExtractIGTKKDE",__n);
    return 0;
  }
  memmove(param_3,param_1 + 8,__n);
  *param_4 = (char)__n;
  if (DebugLevel < 3) {
    return 1;
  }
  printk("[PMF]%s : IGTK_Key_ID=%d, IGTK length=%d\n","PMF_ExtractIGTKKDE",*param_6,*param_4);
  return 1;
}

