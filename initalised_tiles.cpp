#include<iostream>
#include "initalised_tiles.h"
using namespace std;

void initalised_tiles(&tiles){
  for (int i=0; i<40; i++){
     
    //type_0, color_0: Go
    if(i==0){
        tiles[i]={-1,0,0,0,-2000,0, name="Go"};
     }

    //type_1, color_1: Chek Lap Kok, Lantau Island
    else if(i==1||i==3){
      if(i==1){
        tiles[i]={-1,0,0,1,600,1,name="Chek Lap Kok"};
      }
      else{
        tiles[i]={-1,0,0,1,600,1,name="Lantau Island"};
      }
    }

    //type_2, color_2: Ngong Ping, Cheung Chau, Lamma Island
    else if(i==6||i==8||i==9){
      if(i==6){
        tiles[i]={-1,0,0,2,1000,2,name="Ngong Ping"};
      }
      else if(i==8){
        tiles[i]={-1,0,0,2,1000,2,name="Cheung Chau"};
      }
      else{
        tiles[i]={-1,0,0,2,1200,2,name="Lamma Island"};
      }
    }

    //type_3, color_3: Lo Wu, Tin Shui Wai, Sham Tseng
    else if(i==11||i==13||i==14){
      if(i==11){
        tiles[i]={-1,0,0,3,1400,3,name="Lo Wu"};
      }
      else if(i==13){
        tiles[i]={-1,0,0,3,1400,3,name="Tin Shui Wai"};
      }
      else{
         tiles[i]={-1,0,0,3,1600,3,name="Sham Tseng"};
      }
    }

    //type_4, color_4: Kwai Chung, Sha Tin, Tseung Kwan O
    else if(i==16||i==18||i==19){
      if(i==16){
          tiles[i]={-1,0,0,4,1800,4,name="Kwai Chung"};
      }
      else if(i==18){
          tiles[i]={-1,0,0,4,1800,4,name="Sha Tin"};
      }
      else{
          tiles[i]={-1,0,0,4,2000,4,name="Tseung Kwan O"};
      }
    }

  //type_5, color_5: Lei Yue Mun, Wong Tai Sin, Kowloon Tong
  else if(i==21||i==23||i==24){
    if(i==21){
      tiles[i]={-1,0,0,5,2200,5,name="Lei Yue Mun"};
    }
    else if(i==23){
      tiles[i]={-1,0,0,5,2200,5,name="Wong Tai Sin"};
    }
    else{
      tiles[i]={-1,0,0,5,2400,5,name="Kowloon Tong"};
    }
  }

  //type_6, color_6: Kwun Tong, Mong Kok, Tsim Sha Tsui
  else if(i==26||i==27||i==29){
    if(i==26){
      tiles[i]={-1,0,0,6,2600,6,name="Kwun Tong"};
    }
    else if(i==27){
      tiles[i]={-1,0,0,6,2600,6,name="Mong Kok"};
    }
    else{
      tiles[i]={-1,0,0,6,2800,6,name="Tsim Sha Tsui"};
    }
  }

  //type_7, color_7: Causeway Bay, Cyberport, Central
  else if(i==31||i==32||i==34){
    if(i==31){
      tiles[i]={-1,0,0,7,3000,7,name="Causeway Bay"};
    }
    else if(i==32){
      tiles[i]={-1,0,0,7,3000,7,name="Cyberport"};
    }
    else{
      tiles[i]={-1,0,0,7,3200,7,name="Central"};
    }
  }

  //type_8, color_8: Repulse Bay,The Peak
  else if(i==37||i==39){
    if(i==37){
      tiles[i]={-1,0,0,8,3500,8,name="Repulse Bay"};
    }
    else{
      tiles[i]={-1,0,0,8,4000,8,name="The Peak"};
    }
  }
}
