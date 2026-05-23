// module: mt7915.ko
// function: GetChRegion @ 0x141070
// size: 116 bytes
//

char * GetChRegion(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined1 *__s1;
  
  cVar1 = ChRegion[0];
LAB_00141084:
  do {
    if (cVar1 == '\0') {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    __s1 = ChRegion;
    do {
      iVar2 = strncmp(__s1,param_1,2);
      if (iVar2 == 0) {
        param_1 = "WO";
        if (__s1 != (char *)0x0) {
          return __s1;
        }
        goto LAB_00141084;
      }
      __s1 = __s1 + 0xc;
    } while (*__s1 != '\0');
    param_1 = "WO";
  } while( true );
}

