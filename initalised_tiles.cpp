#include<iostream>
#include "initalised_tiles.h"
#include "game.h"
using namespace std;

void initalised_tiles(Tile tiles[]){
  for (int i=0; i<40; i++){
    
    //type_0, color_0: Chance
    if(i==7||i==36){
      tiles[i].set(-1,0,0,0,0,0,"Chance");
    }

    //type_1, color_1: Community Chest
    else if(i==2||i==17||i==33){
      tiles[i].set(-1,0,0,1,0,1,"Community Chest");
    }
      
    //type_2, color_2: Stanley Jail
    else if(i==10||i==30){
      tiles[i].set(-1,0,0,2,0,2,"Stanley Jail");
    } 
    
    //type_3, color_3: Free Parking
    else if(i==22){
      tiles[i].set(-1,0,0,3,0,3,"Free Parking");
    } 

    //type_4, color_4: property

    //Chek Lap Kok, Lantau Island
    else if(i==1||i==3){
      if(i==1){
        tiles[i].set(-1,0,0,4,600,4,"Chek Lap Kok");
      }
      else{
        tiles[i].set(-1,0,0,4,600,4,"Lantau Island");
      }
    }

    //Ngong Ping, Cheung Chau, Lamma Island
    else if(i==6||i==8||i==9){
      if(i==6){
        tiles[i].set(-1,0,0,4,1000,4,"Ngong Ping");
      }
      else if(i==8){
        tiles[i].set(-1,0,0,4,1000,4,"Cheung Chau");
      }
      else{
        tiles[i].set(-1,0,0,4,1200,4,"Lamma Island");
      }
    }

    //Lo Wu, Tin Shui Wai, Sham Tseng
    else if(i==11||i==13||i==14){
      if(i==11){
        tiles[i].set(-1,0,0,4,1400,4,"Lo Wu");
      }
      else if(i==13){
        tiles[i].set(-1,0,0,4,1400,4,"Tin Shui Wai");
      }
      else{
         tiles[i].set(-1,0,0,4,1600,4,"Sham Tseng");
      }
    }
    
    //Kwai Chung, Sha Tin, Tseung Kwan O
    else if(i==16||i==18||i==19){
      if(i==16){
          tiles[i].set(-1,0,0,4,1800,4,"Kwai Chung");
      }
      else if(i==18){
          tiles[i].set(-1,0,0,4,1800,4,"Sha Tin");
      }
      else{
          tiles[i].set(-1,0,0,4,2000,4,"Tseung Kwan O");
      }
    }

    //Lei Yue Mun, Wong Tai Sin, Kowloon Tong
    else if(i==21||i==23||i==24){
      if(i==21){
        tiles[i].set(-1,0,0,4,2200,4,"Lei Yue Mun");
      }
      else if(i==23){
        tiles[i].set(-1,0,0,4,2200,4,"Wong Tai Sin");
      }
      else{
        tiles[i].set(-1,0,0,4,2400,4,"Kowloon Tong");
      }
    }

    //Kwun Tong, Mong Kok, Tsim Sha Tsui
    else if(i==26||i==27||i==29){
      if(i==26){
        tiles[i].set(-1,0,0,4,2600,4,"Kwun Tong");
      }
      else if(i==27){
        tiles[i].set(-1,0,0,4,2600,4,"Mong Kok");
      }
      else{
        tiles[i].set(-1,0,0,4,2800,4,"Tsim Sha Tsui");
      }
    }

    //Causeway Bay, Cyberport, Central
    else if(i==31||i==32||i==34){
      if(i==31){
        tiles[i].set(-1,0,0,4,3000,4,"Causeway Bay");
      }
      else if(i==32){
        tiles[i].set(-1,0,0,4,3000,4,"Cyberport");
      }
      else{
        tiles[i].set(-1,0,0,4,3200,4,"Central");
      }
    }

    //Repulse Bay,The Peak
    else if(i==37||i==39){
      if(i==37){
        tiles[i].set(-1,0,0,4,3500,4,"Repulse Bay");
      }
      else{
        tiles[i].set(-1,0,0,4,4000,4,"The Peak");
      }
    }

    //type_5, color_5: Go
    else if(i==0){
          tiles[i].set(-1,0,0,5,0,5, "Go");
    }

    //type_6, color_6: Income Tax & Salary Tax

    //Income Tax
    else if(i==4){
      tiles[i].set(-1,0,0,6,0,6,"Income Tax");
    }

    //Salary Tax
    else if(i==38){
      tiles[i].set(-1,0,0,6,750,6,"Salary Tax");
    }

    //type_7, color_7: railroad
    //Airport Station, Hong Kong Electric, Tsing Yi Station, Kowloon Station
    else if(i==5||i==12||i==15||i==25){
      if(i==5){
        tiles[i].set(-1,0,0,7,2000,7,"Airport Station");
      }
      else if(i==12){
        tiles[i].set(-1,0,0,7,1500,7,"Hong Kong Electric");
      }
      else if(i==15){
        tiles[i].set(-1,0,0,7,2000,7,"Tsing Yi Station");
      }
      else{
        tiles[i].set(-1,0,0,7,2000,7,"Kowloon Station");
      }
    }
      
    //type_8, color_8: utility
        
    //Provincial
    else if(i==20){
      tiles[i].set(-1,0,0,15,0,15,"Provincial");
    } 
      
    //Water Works
    else if(i==28){
      tiles[i].set(-1,0,0,16,1500,16,"Water Works");
    } 
  }
}
