//
//  GamepanelHeader.h
//  MonsterGame
//
//  Created by 南京艾游网络文化有限公司 on 15/5/29.
//
//

#ifndef MonsterGame_GamepanelHeader_h
#define MonsterGame_GamepanelHeader_h


#define BAGBTN 1
#define BAGCLOSEBTN 2
#define BAGJIA 0
#define BAGALL 101
#define BAGSELL 102
#define BAGJIAN 100
#define CHONGWU 3
#define MISSION 4
#define JUESE 10
#define SHOWALL 20
#define SHOWCAILIAO 21
#define SHOWZHUANGBEI 22
#define SHOWDAOJU 23
#define BAGBUY 24
#define BAGNOBUY 25

typedef enum {
    PetBagType_ESC = 0,//«π
    PetBagType_SHUXING = 1,//µ∂
    PetBagType_JINENG = 2,//≥ËŒÔ,
    PetBagType_JINJIE = 3,//≥ËŒÔ
    PetBagType_JIAQIYUE = 4,
    PetBagType_JIANQIYUE =5,
    PetBagType_BUY =6,
    PetBagType_NOBUY= 7,
}PetBagType;

typedef enum {
    ButtonType_NECKLACE = 1,//«π
    ButtonType_RINGA,
    ButtonType_RINGB,
 ButtonType_EQUIPA ,
 ButtonType_EQUIPB,
 ButtonType_PETA,
 ButtonType_PETB,
 ButtonType_PETC,
 ButtonType_ZHUDONGA,
 ButtonType_BEIDONGA,
 ButtonType_ZHUDONGB,
 ButtonType_BEIDONGB,
 ButtonType_ESCFACE,
 ButtonType_ESCPANEL,
 ButtonType_EQUIP,
 ButtonType_QIANGHUA,
 ButtonType_SHUXING,
 ButtonType_JINENG,
 ButtonType_TIANFU,
 ButtonType_CHONGZHI,
}ButtonType;



#endif
