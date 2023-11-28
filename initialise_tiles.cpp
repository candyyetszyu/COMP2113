#include<iostream>
#include "initialise_tiles.h"
#include "game.h"
using namespace std;

void initialise_tiles(Tile tiles[]){
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
      tiles[i].set(-1,0,0,2,0,0,"Stanley Jail");
    } 
    
    //type_3, color_3: Free Parking
    else if(i==22){
      tiles[i].set(-1,0,0,3,0,0,"Free Parking");
    } 

    //type_4, color_4: property

    //Chek Lap Kok, Lantau Island
    else if(i==1||i==3){
      if(i==1){
        tiles[i].set(-1,0,0,4,60,1,"Chek Lap Kok");
      }
      else{
        tiles[i].set(-1,0,0,4,60,1,"Lantau Island");
      }
    }

    //Ngong Ping, Cheung Chau, Lamma Island
    else if(i==6||i==8||i==9){
      if(i==6){
        tiles[i].set(-1,0,0,4,100,2,"Ngong Ping");
      }
      else if(i==8){
        tiles[i].set(-1,0,0,4,100,2,"Cheung Chau");
      }
      else{
        tiles[i].set(-1,0,0,4,120,2,"Lamma Island");
      }
    }

    //Lo Wu, Tin Shui Wai, Sham Tseng
    else if(i==11||i==13||i==14){
      if(i==11){
        tiles[i].set(-1,0,0,4,140,3,"Lo Wu");
      }
      else if(i==13){
        tiles[i].set(-1,0,0,4,140,3,"Tin Shui Wai");
      }
      else{
         tiles[i].set(-1,0,0,4,160,3,"Sham Tseng");
      }
    }
    
    //Kwai Chung, Sha Tin, Tseung Kwan O
    else if(i==16||i==18||i==19){
      if(i==16){
          tiles[i].set(-1,0,0,4,180,4,"Kwai Chung");
      }
      else if(i==18){
          tiles[i].set(-1,0,0,4,180,4,"Sha Tin");
      }
      else{
          tiles[i].set(-1,0,0,4,200,4,"Tseung Kwan O");
      }
    }

    //Lei Yue Mun, Wong Tai Sin, Kowloon Tong
    else if(i==21||i==23||i==24){
      if(i==21){
        tiles[i].set(-1,0,0,4,220,5,"Lei Yue Mun");
      }
      else if(i==23){
        tiles[i].set(-1,0,0,4,220,5,"Wong Tai Sin");
      }
      else{
        tiles[i].set(-1,0,0,4,240,5,"Kowloon Tong");
      }
    }

    //Kwun Tong, Mong Kok, Tsim Sha Tsui
    else if(i==26||i==27||i==29){
      if(i==26){
        tiles[i].set(-1,0,0,4,260,6,"Kwun Tong");
      }
      else if(i==27){
        tiles[i].set(-1,0,0,4,260,6,"Mong Kok");
      }
      else{
        tiles[i].set(-1,0,0,4,280,6,"Tsim Sha Tsui");
      }
    }

    //Causeway Bay, Cyberport, Central
    else if(i==31||i==32||i==34){
      if(i==31){
        tiles[i].set(-1,0,0,4,300,7,"Causeway Bay");
      }
      else if(i==32){
        tiles[i].set(-1,0,0,4,300,7,"Cyberport");
      }
      else{
        tiles[i].set(-1,0,0,4,320,7,"Central");
      }
    }

    //Repulse Bay,The Peak
    else if(i==37||i==39){
      if(i==37){
        tiles[i].set(-1,0,0,4,350,8,"Repulse Bay");
      }
      else{
        tiles[i].set(-1,0,0,4,400,8,"The Peak");
      }
    }

    //type_5, color_5: Go
    else if(i==0){
          tiles[i].set(-1,0,0,5,0,0, "Go");
    }

    //type_6, color_6: Income Tax & Salary Tax

    //Income Tax
    else if(i==4){
      tiles[i].set(-1,0,0,6,0,0,"Income Tax");
    }

    //Salary Tax
    else if(i==38){
      tiles[i].set(-1,0,0,6,75,0,"Salary Tax");
    }

    //type_7, color_7: railroad
    else if(i==5||i==15||i==25||i==35){
      if(i==5){
        tiles[i].set(-1,0,0,7,200,0,"Airport Station");
      }
      else if(i==15){
        tiles[i].set(-1,0,0,7,200,0,"Tsing Yi Station");
      }
      else if (i==25){
        tiles[i].set(-1,0,0,7,200,0,"Kowloon Station");
      } else{
        tiles[i].set(-1,0,0,7,200,0,"Hong Kong Station");
      }
    }
      
    //type_8, color_8: utility
        
    //Provincial
    else if(i==20){
      tiles[i].set(-1,0,0,15,0,0,"Provincial");
    } 
      
    //Water Works
    else if(i==28){
      tiles[i].set(-1,0,0,16,150,0,"Water Works");
    } 

    //Hong Kong Electric
    else if(i==12){
        tiles[i].set(-1,0,0,7,150,0,"Hong Kong Electric");
      }
  }
}
