// module: plat-zxylzb_9128S.ko
// function: getopt @ 0x103b4
// size: 564 bytes
//

int getopt(int ___argc,char **___argv,char *__shortopts)

{
  char *pcVar1;
  byte *pbVar2;
  uint __c;
  
  if ((optreset == 0) && (__c = (uint)*place_37758, __c != 0)) {
    pbVar2 = place_37758 + 1;
LAB_00010400:
    place_37758 = pbVar2;
    optopt = __c;
    if (__c == 0x3a) goto LAB_00010408;
  }
  else {
    optreset = 0;
    pcVar1 = ___argv[optind];
    if ((___argc <= optind) || (*pcVar1 != '-')) {
      place_37758 = &_LC2;
      optreset = 0;
      return -1;
    }
    __c = (uint)(byte)pcVar1[1];
    pbVar2 = (byte *)(pcVar1 + 2);
    optopt = __c;
    if (__c == 0x2d) {
      place_37758 = pbVar2;
      if (pcVar1[2] == '\0') {
        place_37758 = &_LC2;
        optind = optind + 1;
        optreset = 0;
        return -1;
      }
    }
    else {
      if (__c != 0) goto LAB_00010400;
      pbVar2 = &_LC2;
      place_37758 = &_LC2;
      pcVar1 = strchr(__shortopts,0x2d);
      if (pcVar1 == (char *)0x0) {
        return -1;
      }
      optopt = 0x2d;
    }
    __c = 0x2d;
  }
  pcVar1 = strchr(__shortopts,__c);
  if (pcVar1 != (char *)0x0) {
    if (pcVar1[1] == ':') {
      if (*pbVar2 == 0) {
        optind = optind + 1;
        if (___argc <= optind) {
          place_37758 = &_LC2;
          if (*__shortopts != ':') {
            printk("option requires an argument -- %c\n",__c);
            return 0x3f;
          }
          return 0x3a;
        }
        pbVar2 = (byte *)___argv[optind];
      }
      optarg = pbVar2;
      optind = optind + 1;
      place_37758 = &_LC2;
    }
    else {
      optarg = (byte *)0x0;
      if (*pbVar2 == 0) {
        optind = optind + 1;
      }
    }
    return optopt;
  }
LAB_00010408:
  if (*pbVar2 == 0) {
    optind = optind + 1;
  }
  if (*__shortopts != ':') {
    printk("unknown option -- %c\n",__c);
  }
  return 0x3f;
}

