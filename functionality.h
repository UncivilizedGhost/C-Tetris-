/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
//Muhammad Saad Zia 22i-0994 Project CS-D
#include <fstream>

//---Piece Starts to Fall When Game Starts---//
void row_check(int &score,int &level,int & starting,bool &over,int &total_rows,int &highest_score);
void gameover_check(int &score,int &starting,bool &over,int & highest_score);             //Function prototypes
void placement();
void spawn(int &n,int &starting);
void grid_cropper(float &gridtime,int &starting);






void falling(float& timer, float& delay, int& color,int & shape,int &score,int &level,int &boom,int &starting,bool &over,int &total_rows,int &highest_score){



    static int n2=rand()%7;   //Choose next color and block
    int n;

    static bool init=true;
    if (init||boom==-1){                               // To set the first block
        color=1+rand()%7;
        n=n2;
        shape=n;
        n2=rand()%7;
        spawn(n,starting);
        init=false;        // Ensure this never runs again
        boom=0;
    }



    if (timer>delay){                           //Moves blocks downwards every frame
        for (int i=0;i<4;i++){
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] ++;
        }



        if (anamoly()==0){
            std::cout<<"\n\n";    //For debugging
            for(int i=0;i<4;i++){
                gameGrid[point_2[i][1]][point_2[i][0]] = color;}      //Sets colors


            color=1+rand()%7;   // Used To set colors and shapes for next piece
            n=n2;
            shape=n;
            n2=rand()%7;
            delay=0.4;

            spawn(n,starting);
            row_check(score,level,starting,over,total_rows,highest_score);   //  Function Set For Checking state of grid at the end of every cycle


            std::cout<<"score is "<<score<<"\n";


            bool chance=(rand()%50)>42 ;                                 //Low chance of color bomb

            if ((boom<=3)&&chance){
                boom++;
            }

        }

        timer=0;  // Resets timer
    }
    
}








void movement(int& x){

    for(int i = 0; i < 4; i++){
        point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
        point_1[i][0] = point_1[i][0] + x;         // Moves each block either left or right
     }
        
        placement();                            //Checks if movement is possible
}








void DeleteLine (int y){
    for (int j = y; j > 0; j--){
        for (int i = 0; i < 10; i++){
            gameGrid[j][i] = gameGrid[j-1][i];  // Moves all the upper lines one row down
        }
    }
}








void row_check(int &score,int &level,int & starting,bool &over,int &total_rows,int &highest_score){
    int lines=0;
    for (int j = 0; j < 20; j++){
            int block=0;
            for(int i = 0; i < 10; i++){
                if (gameGrid[j][i]>0){             //Checks blocks in every row
                    block++;
            }
        }


        if (block==10){                         //Deletes every full row
            DeleteLine(j);
            lines++;                         //Adds number of deleted rows
        }
    std::cout<<"            "<<block<<"\n";
    }


    if (lines==1)
        score+=10*level;
    else if (lines==2)
        score+=30*level;
    else if (lines==3)
        score+=60*level;
    else if (lines==4)                                 //Calculates score
        score+=100*level;
    if (lines>0){
        total_rows++;}

    gameover_check(score,starting,over,highest_score);     //Checks of game is over

}








void rotation(int& rotate,int& shape){
    if (rotate){
        int center[2];          //Sets center depending on the block
        if (shape==0){
            return;
        }
        else if (shape==1){
            center[0]=point_1[0][0];
            center[1]=point_1[3][1];
        }
        else if (shape==2){
            center[0]=point_1[1][0];
            center[1]=point_1[3][1];
        }
        else if (shape==3){
            center[0]=point_1[1][0];
            center[1]=point_1[3][1];
        }
        else if (shape==4){
            center[0]=point_1[1][0];
            center[1]=point_1[1][1];
        }
        else if (shape==5){
            center[0]=point_1[1][0];
            center[1]=point_1[1][1];
        }
        else if (shape==6){
            center[0]=point_1[1][0];
            center[1]=point_1[2][1];
        }



        for (int i=0;i<4;i++){
            int x = point_1[i][1]-center[1];
            int y = point_1[i][0]-center[0];           //Find distance of blocks from center


            if (rotate==1){                           //  Rotates counter clockwise
                point_1[i][0]=center[0]-x;            // Swaps x and y distance of blocks
                point_1[i][1]=center[1]+y;
            }
            if (rotate==-1){
                point_1[i][0]=center[0]+x;           //  Rotates counter clockwise
                point_1[i][1]=center[1]-y;              // Swaps x and y distance of blocks

            }
        }
    }
    placement();
}








void placement(){
    if(!anamoly()){             //    Sets new positions following movement and rotation only if no collisions are taking place
        for (int i = 0; i < 4; i++){
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
}







void gameover_check(int &score,int &starting,bool &over,int &highest_score){                   //Checks is game is over
    for(int i = 0; i < 10; i++){
        if (gameGrid[starting][i]>0||gameGrid[starting+1][i]>0){

            if (score>highest_score)
            {highest_score=score;
                std::cout<<"yes";            //Check if a new high score is made
            }
            over=true;
        }
    }
}



void spawn(int &n,int &starting){
    int sp=rand()%9;
    for (int i=0;i<4;i++){
        point_1[i][0] = BLOCKS[n][i] % 2+sp;   // Set's x coordinate of piece
        point_1[i][1] = BLOCKS[n][i] / 2+starting;   //  Set's y coordinate of piece
        }
}




void color_bomb(float& timer, float& delay,int &color,int & boom,int & starting){     //For the color bomb
    srand(time(0));
     int sp=rand()%9;
     bool done=false;

    static bool cinit=true;
    if (cinit){
        color=1+rand()%7;
        for (int i=0;i<4;i++){
            point_1[i][0] = sp;   //Spawns the block
            point_1[i][1] = 1+starting;}
        cinit=false;

    }
    int xpoint;
    int ypoint;



     if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //falling  downward
            if (!done)
            {xpoint=point_1[3][0];
             ypoint=point_1[3][1];}

        }
        if (!anamoly()){
            int n=0;
            for(int i=0;i<4;i++){
                gameGrid[point_2[i][1]][point_2[i][0]] = color;                 //Lands the block
            }
        color=1+rand()%7;




            if (ypoint<20&&(gameGrid[ypoint][xpoint]==gameGrid[ypoint-1][xpoint])){
                    for (int j = starting; j < 20; j++){
                        for(int i = 0; i < 10; i++){        //Destroys all blocks  if lands on right color
                            gameGrid[j][i]=0;
                        }
                    }

            }
            else if ((gameGrid[ypoint-1][xpoint]!=gameGrid[ypoint][xpoint])&&ypoint<20){       //Small explosion if lands on wrong color


                if (xpoint<1){
                    gameGrid[ypoint][xpoint]=0;
                    gameGrid[ypoint-1][xpoint+1]=0;
                    gameGrid[ypoint-1][xpoint]=0;
                    gameGrid[ypoint-1][xpoint]=0;

                    done=true;
                }
                else if (xpoint>8){
                      gameGrid[ypoint][xpoint]=0;
                    gameGrid[ypoint-1][xpoint-1]=0;
                    gameGrid[ypoint-1][xpoint]=0;
                    gameGrid[ypoint-1][xpoint]=0;
                    done=true;

                }
                else{
                    gameGrid[ypoint][xpoint]=0;
                    gameGrid[ypoint-1][xpoint+1]=0;
                    gameGrid[ypoint-1][xpoint-1]=0;
                    gameGrid[ypoint-1][xpoint]=0;
                    gameGrid[ypoint-1][xpoint]=0;
                    done=true;
                }

            }
                else if (!done){
                      gameGrid[19][xpoint]=0; //Makes block disappear if it lands on no blocks
                      done=true;
                }
        boom=-1;
        cinit=true;

        }
        timer=0;
     }
}

void grid_cropper(float &gridtime,int &starting){                 //Decreases the grid size


    if (gridtime>300){
        for (int i=0;i<10;i++){
            gameGrid[starting][i]=10;
        }
        starting++;
        gridtime=0;
    }
}


void reset(){
    for (int j = 0; j < 20; j++){
        for(int i = 0; i < 10; i++){        //Destroys all blocks
            gameGrid[j][i]=0;
            }
        }
        for(int i = 0; i < 4; i++){  //Removes previous block
        point_1[i][0] = 0;
        point_1[i][1] = 0;
     }

        for(int i = 0; i < 4; i++){  //Removes previous points
        point_2[i][0] = 0;
        point_2[i][1] = 0;
     }
        int n=rand()&7;                //Spawns brand new block
        int starting=0;
        spawn(n,starting);
}





std::string highscore(){
    std::string tscore="";
    std::string score="";
std::ifstream MyFile("Highscore.txt");

    while (getline (MyFile, score)) {
        tscore+=score+"\n";          //Finds high score to display it
    }
        MyFile.close();

    return tscore;
}


int get_highscore(){
    std::string s =highscore();                    //Get actual number
    int posit =s.find(":");
    std::string sub = s.substr(posit + 1);
    int high=std::stoi(sub);
    return high;
}



void savenewscore(std::string player,int highest_score){
  std::ofstream MyFile("Highscore.txt");
  MyFile << player+":"+std::to_string(highest_score);                    //Saves new name and score

  MyFile.close();
}




