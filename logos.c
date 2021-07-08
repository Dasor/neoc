#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define C1 "\033[30m"
#define C2 "\033[1;31m"
#define C3 "\033[1;32m"
#define C4 "\033[1;33m"
#define C5 "\033[1;34m"
#define C6 "\033[1;35m"
#define C7 "\033[1;36m"
#define C9 "\033[1;37m"

typedef struct{

  int height;
  char *logo;
  char *color;

}Logo;

Logo *getLogo(char *string){

  Logo *mylogo = malloc(sizeof(Logo));  

  if(strstr(string,"Arch") != NULL || strstr(string,"arch") != NULL ){
    mylogo->logo = 
      C7"                      -`                     \0"\
      C7"                     .o+`                    \0"\
      C7"                    `ooo/                    \0"\
      C7"                   `+oooo:                   \0"\
      C7"                  `+oooooo:                  \0"\
      C7"                  -+oooooo+:                 \0"\
      C7"                `/:-:++oooo+:                \0"\
      C7"               `/++++/+++++++:               \0"\
      C7"              `/++++++++++++++:              \0"\
      C7"             `/+++ooooooooooooo/`            \0"\
      C7"            ./ooosssso++osssssso+`           \0"\
      C7"           .oossssso-````/ossssss+`          \0"\
      C7"          -osssssso.      :ssssssso.         \0"\
      C7"         :osssssss/        osssso+++.        \0"\
      C7"        /ossssssss/        +ssssooo/-        \0"\
      C7"      `/ossssso+/:-        -:/+osssso+-      \0"\
      C7"     `+sso+:-`                 `.-/+oso:     \0"\
      C7"    `++:.                           `-/+/    \0"\
      C7"    .`                                 `/    \0"\
      ;
    mylogo->color = C7;
    mylogo->height = 19;
  }else if(strstr(string,"Debian") != NULL || strstr(string,"debian") != NULL ){
    mylogo->logo =
      C9"                                 \0"\
      C9"        _,met$$$$$gg.            \0"\
      C9"     ,g$$$$$$$$$$$$$$$P.         \0"\
      C9"   ,g$$P\"     \"\"\"Y$$.\".          \0"\
      C9"  ,$$P'              `$$$.       \0"\
      C9" ',$$P       ,ggs.     `$$b:     \0"\
      C9" `d$$'     ,$P\"' "C2"  ."C9"    $$$      \0"\
      C9"  $$P      d$'    "C2" , "C9"   $$P      \0"\
      C9"  $$:      $$.  "C2" - "C9"   ,d$$'      \0"\
      C9"  $$;      Y$b._   _,d$P'        \0"\
      C9"  Y$$.    "C2"`."C9"`\"Y$$$$P\"'           \0"\
      C9"  `$$b     "C2" \"-.__ "C9"               \0"\
      C9"   `Y$$                          \0"\
      C9"    `Y$$.                        \0"\
      C9"      `$$b.  		         \0"\
      C9"         `Y$$b.                   \0"\
      C9"           `\"Y$b._               \0"\
      C9"               `\"\"\"              \0"\
      ;
    mylogo->color = C2;
    mylogo->height = 18;
  }else if(strstr(string,"Ubuntu") != NULL || strstr(string,"ubuntu") != NULL ){
    mylogo->logo =
      C2"            .-/+oossssoo+\\-.               \0"\
      C2"        ´:+ssssssssssssssssss+:`           \0"\
      C2"      -+ssssssssssssssssssyyssss+-         \0"\
      C2"    .ossssssssssssssssss"C9"dMMMNy"C2"sssso.       \0"\
      C2"   /sssssssssss"C9"hdmmNNmmyNMMMMh"C2"ssssss\\      \0"\
      C2"  +sssssssss"C9"hm"C2"yd"C9"MMMMMMMNddddy"C2"ssssssss+     \0"\
      C2" /ssssssss"C9"hNMMM"C2"yh"C9"hyyyyhmNMMMNh"C2"ssssssss\\    \0"\
      C2".ssssssss"C9"dMMMNh"C2"ssssssssss"C9"hNMMMd"C2"ssssssss.   \0"\
      C2"+ssss"C9"hhhyNMMNy"C2"ssssssssssss"C9"yNMMMy"C2"sssssss+   \0"\
      C2"oss"C9"yNMMMNyMMh"C2"ssssssssssssss"C9"hmmmh"C2"ssssssso   \0"\
      C2"oss"C9"yNMMMNyMMh"C2"sssssssssssssshmmmh"C2"ssssssso   \0"\
      C2"+ssss"C9"hhhyNMMNy"C2"ssssssssssss"C9"yNMMMy"C2"sssssss+   \0"\
      C2".ssssssss"C9"dMMMNh"C2"ssssssssss"C9"hNMMMd"C2"ssssssss.   \0"\
      C2" \\ssssssss"C9"hNMMM"C2"yh"C9"hyyyyhdNMMMNh"C2"ssssssss/    \0"\
      C2"  +sssssssss"C9"dm"C2"yd"C9"MMMMMMMMddddy"C2"ssssssss+     \0"\
      C2"   \\sssssssssss"C9"hdmNNNNmyNMMMMh"C2"ssssss/             \0"\
      C2"    .ossssssssssssssssss"C9"dMMMNy"C2"sssso.               \0"\
      C2"      -+sssssssssssssssss"C9"yyy"C2"ssss+-                 \0"\
      C2"        `:+ssssssssssssssssss+:`                           \0"\
      C2"            .-\\+oossssoo+/-.                              \0"\
      ;
    mylogo->color = C2;
    mylogo->height = 20;
  }else if(strstr(string,"Gentoo") != NULL || strstr(string,"gentoo") != NULL ){
    mylogo->logo =
      C6"         -/oyddmdhs+:.                 \0"\
      C6"     -o"C9"dNMMMMMMMMNNmhy+"C6"-`              \0"\
      C6"   -y"C9"NMMMMMMMMMMMNNNmmdhy"C6"+-            \0"\
      C6" `o"C9"mMMMMMMMMMMMMNmdmmmmddhhy"C6"/`         \0"\
      C6" om"C9"MMMMMMMMMMMN"C6"hhyyyo"C9"hmdddhhhd"C6"o`       \0"\
      C6".y"C9"dMMMMMMMMMMd"C6"hs++so/s"C9"mdddhhhhdm"C6"+`     \0"\
      C6" oy"C9"hdmNMMMMMMMN"C6"dyooy"C9"dmddddhhhhyhN"C6"d.    \0"\
      C6"  :o"C9"yhhdNNMMMMMMMNNNmmdddhhhhhyym"C6"Mh    \0"\
      C6"    .:"C9"+sydNMMMMMNNNmmmdddhhhhhhmM"C6"my    \0"\
      C6"       /m"C9"MMMMMMNNNmmmdddhhhhhmMNh"C6"s:    \0"\
      C6"    `o"C9"NMMMMMMMNNNmmmddddhhdmMNhs"C6"+`     \0"\
      C6"  `s"C9"NMMMMMMMMNNNmmmdddddmNMmhs"C6"/.       \0"\
      C6" /N"C9"MMMMMMMMNNNNmmmdddmNMNdso"C6":`         \0"\
      C6"+M"C9"MMMMMMNNNNNmmmmdmNMNdso"C6"/-            \0"\
      C6"yM"C9"MNNNNNNNmmmmmNNMmhs+/"C6"-`              \0"\
      C6"/h"C9"MMNNNNNNNNMNdhs++/"C6"-`                 \0"\
      C6"`/"C9"ohdmmddhys+++/:"C6".`                    \0"\
      C6"  `-//////:--.                          \0"\
      ;
    mylogo->color = C6;
    mylogo->height =18;
  }else if(strstr(string,"Fedora") != NULL || strstr(string,"fedora") != NULL ){
    mylogo->logo =
      C5"          /:-------------:\\           \0"\
      C5"       :-------------------::         \0"\
      C5"     :-----------"C9"/shhOHbmp"C5"---:\\       \0"\
      C5"   /-----------"C9"omMMMNNNMMD  "C5"---:      \0"\
      C5"  :-----------"C9"sMMMMNMNMP"C5".    ---:     \0"\
      C5" :-----------"C9":MMMdP"C5"-------    ---\\    \0"\
      C5",------------"C9":MMMd"C5"--------    ---:    \0"\
      C5":------------"C9":MMMd"C5"-------    .---:    \0"\
      C5":----    "C9"oNMMMMMMMMMNho"C5"     .----:    \0"\
      C5":--     ."C9"+shhhMMMmhhy++"C5"   .------/    \0"\
      C5":-    -------"C9":MMMd"C5"--------------:     \0"\
      C5":-   --------"C9"/MMMd"C5"-------------;      \0"\
      C5":-    ------"C9"/hMMMy"C5"------------:       \0"\
      C5":--"C9" :dMNdhhdNMMNo"C5"------------;        \0"\
      C5":---"C9":sdNMMMMNds:"C5"------------:         \0"\
      C5":------"C9":://:"C5"-------------::      \0"\
      C5":---------------------://               \0"\
      ;
    mylogo->color = C5;
    mylogo->height = 17;
  }
  else{
    mylogo->logo =
      C4 "          ________               \0"\
      C4 "       _jgN########Ngg_          \0"\
      C4 "     _N##N@@\"\"  \"\"9NN##Np_       \0"\
      C4 "    d###P            N####p      \0"\
      C4 "    \"^^\"              T####      \0"\
      C4 "                      d###P      \0"\
      C4 "                   _g###@F       \0"\
      C4 "                _gN##@P          \0"\
      C4 "              gN###F\"            \0"\
      C4 "             d###F               \0"\
      C4 "            0###F                \0"\
      C4 "            0###F                \0"\
      C4 "            0###F                \0"\
      C4 "            \"NN@'                \0"\
      C4 "                                 \0"\
      C4 "             ___                 \0"\
      C4 "            q###r                \0"\
      C4 "             \"\"                  \0"\
      ;
      mylogo->color = C4;
      mylogo->height = 18;
  }
  return mylogo;
}
