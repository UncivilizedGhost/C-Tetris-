/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
//Muhammad Saad Zia 22i-0994 Project CS-D
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <string>

using namespace sf;

int main(){


    
    RenderWindow window(VideoMode(320, 480), title);
    
    Texture obj1, obj2, obj3,obj4;

    
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/Start.jpg");
    Sprite sprite(obj1), background(obj2), frame(obj3), startingback(obj4),shadsprite(obj1);




    srand(time(0));


    int x_position=0;
    int color_number=0;

    float delay;
    int rotate=0;    //For pieces
    int shape=0;



    int total_rows=0;
    int score=0;        //For the levels and speed
    int highest_score=get_highscore();
    int level=1;
    float timer=0;


    std::string gameoverscreen;
    std::string scoredisplay;      //Variables to display on screen
    std::string leveldisplay;


    int boom=0;         //For the color bomb

    bool save=false;
    bool over=false;
    bool start=false;    //To switch variables for menus
    bool help=false;
    bool pause=false;
    bool show_high=false;

    float start_delay;    //speed of blocks

    int starting=0;
    float gridtime=0;            //For reducing grid


    Clock clock;
    

    Music music;
    music.openFromFile("Tetris.ogg");
                                            //Enable music and fonts
    Font font;
    font.loadFromFile("Roboto.ttf");




    while (window.isOpen()){






        while (!start){
            window.clear(Color::Black);                      //Display Start menu
            window.draw(startingback);

            Text tText("Tetris",font,25);
            tText.setPosition(105,20);
            window.draw(tText);

            Text oneText("Press A to start normal mode",font,16);
            oneText.setPosition(5,90);
            window.draw(oneText);

            Text twoText("Press S to start easy mode",font,16);
            twoText.setPosition(5,140);
            window.draw(twoText);

            Text helptext("Press D to see how to play",font,16);
            helptext.setPosition(5,190);
            window.draw(helptext);

            Text hightext("Press F to see high score",font,16);
            hightext.setPosition(5,240);
            window.draw(hightext);

            window.display();

            Event e;
            while (window.pollEvent(e)){
                if (e.type == Event::Closed){
                    music.stop();
                    window.close();
                    start=true;
                }

                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::A){
                        start=true;
                        start_delay=0.5;
                        music.play();
                    }
                    if (e.key.code == Keyboard::S){                     //Enable Options
                        start=true;
                        start_delay=0.7;
                        music.play();
                    }
                    if (e.key.code == Keyboard::F){
                            show_high=true;
                            while (show_high){                               //Display help menu
                            window.clear(Color::Black);
                            window.draw(startingback);

                            Text tText("High score",font,25);
                            tText.setPosition(75,40);
                            window.draw(tText);


                            Text helpText1(highscore()+"\n\nPress R to return",font,16);
                            helpText1.setPosition(5,80);
                            window.draw(helpText1);
                            window.display();



                            Event e;
                            while (window.pollEvent(e)){
                                    if (e.type == Event::Closed){
                                        music.stop();
                                        window.close();
                                        start=true;
                                        show_high=false;
                                    }

                                    if (e.type == Event::KeyPressed) {
                                        if (e.key.code == Keyboard::R){
                                            show_high=false;
                                        }
                                    }
                                }
                            }
                    }



                    if (e.key.code == Keyboard::D){

                        bool help=true;
                        while (help){                               //Display help menu
                            window.clear(Color::Black);
                            window.draw(startingback);

                            Text tText("Instructions",font,25);
                            tText.setPosition(75,40);
                            window.draw(tText);



                            Text helpText1("Press left and right to move\n\nPress the z and x to rotate\n\nPress down to move down\n\nPress H to pause\n\nPress R to go back",font,16);
                            helpText1.setPosition(5,80);
                            window.draw(helpText1);
                            window.display();



                            Event e;

                            while (window.pollEvent(e)){
                                    if (e.type == Event::Closed){
                                        music.stop();                                    //Options to quit or go back
                                        window.close();
                                        start=true;
                                       show_high=false;
                                    }

                                    if (e.type == Event::KeyPressed) {
                                        if (e.key.code == Keyboard::R){
                                        show_high=false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
        }



        while (pause){                    //Display pause menu
            music.pause();
            window.clear(Color::Black);
            window.draw(startingback);
            Text tText("Pause",font,25);
            tText.setPosition(105,20);
            window.draw(tText);

            Text oneText("Press H to resume",font,16);
            oneText.setPosition(5,80);
            window.draw(oneText);

            Text twoText("Press J to restart",font,16);
            twoText.setPosition(5,130);
            window.draw(twoText);

            Text helptext("Press D to see how to play",font,16);
            helptext.setPosition(5,180);
            window.draw(helptext);

            Text hightext("Press F to see high score",font,16);
            hightext.setPosition(5,230);
            window.draw(hightext);

            window.display();


            Event e;
            while (window.pollEvent(e)){
                if (e.type == Event::Closed){
                    music.stop();
                    window.close();
                    pause=false;
                }

                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::H){
                        pause=false;
                        music.play();
                    }
                    if (e.key.code == Keyboard::J){
                        reset();
                        pause=false;      //Reset Everything
                        starting=0;
                        score=0;
                        level=1;
                        timer=0;
                        boom=0;
                        music.play();
                    }
                    if (e.key.code == Keyboard::F){
                            show_high=true;
                            while (show_high){                               //Display help menu
                            window.clear(Color::Black);
                            window.draw(startingback);

                            Text tText("High score",font,25);
                            tText.setPosition(75,40);
                            window.draw(tText);


                            Text helpText1(highscore()+"\n\nPress R to return",font,16);
                            helpText1.setPosition(5,80);
                            window.draw(helpText1);
                            window.display();



                            Event e;
                            while (window.pollEvent(e)){
                                    if (e.type == Event::Closed){
                                        music.stop();
                                        window.close();
                                        pause=false;
                                        show_high=false;
                                    }

                                    if (e.type == Event::KeyPressed) {
                                        if (e.key.code == Keyboard::R){
                                            show_high=false;
                                        }
                                    }
                                }
                            }
                    }
            }
        }

        }

        while (over){                             //Game over menu
            music.pause();
            window.clear(Color::Black);
             window.draw(startingback);


            Text tText("Game Over",font,25);
            tText.setPosition(60,50);
            window.draw(tText);
            std::string highaccn="";
            bool newscore=false;

            if (highest_score==score)
            {highaccn="\nThis is the highest score";
            Text saveText("Press R-ALT to save it",font,20);
            saveText.setPosition(5,160);                              //Only shows if a new high score is made
            window.draw(saveText);
            newscore=true;
            }
            gameoverscreen="You have a score of "+std::to_string(score)+highaccn;
            Text oneText(gameoverscreen,font,20);
            oneText.setPosition(5,100);
            window.draw(oneText);


            Text hightext("Press F to see high scores",font,20);
            hightext.setPosition(5,210);
            window.draw(hightext);


            Text twoText("Press J to restart",font,20);
            twoText.setPosition(5,250);
            window.draw(twoText);



            window.display();


            Event e;
            while (window.pollEvent(e)){
                if (e.type == Event::Closed){
                    music.stop();
                    window.close();
                    over=false;
                }

                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::J){
                        reset();
                        over=false;
                        starting=0;
                        score=0;                   //Reset Everything
                        boom=0;
                        level=1;
                        timer=0;
                        music.play();
                    }
                    if (e.key.code == Keyboard::RAlt&&newscore){
                        std::string playerInput="";
                        int c=0;
                        while    (!save){
                            window.clear(Color::Black);
                            window.draw(startingback);

                            Text playerText("Enter your Initials: \n\n:"+playerInput,font,20);
                            playerText.setPosition(75,40);                                   //Player can enter initals
                            window.draw(playerText);
                            window.display();
                            Event event;
                            while(window.pollEvent(event)&&!save){

                            if (event.type == sf::Event::TextEntered&&!save){
                                if (event.text.unicode < 128)
                                {playerInput +=event.text.unicode;
                                Text playerText("Enter your Initials: \n\n:"+playerInput,font,20);
                                    playerText.setPosition(75,40);
                                    window.draw(playerText);
                                    window.display();
                                    c++;
                                    if (c==4){
                                        save=true;                 //     Ensures length is constant
                                        newscore=false;
                                        savenewscore(playerInput,highest_score);
                                    }
                                }
                            }

                        if (event.type == Event::Closed)
                            {
                                window.close();
                                save=true;
                                over=false;
                            }


                }
 window.display();


}





                    }
                                        if (e.key.code == Keyboard::F){
                            show_high=true;
                            while (show_high){                               //Display help menu
                            window.clear(Color::Black);
                            window.draw(startingback);

                            Text tText("High score",font,25);
                            tText.setPosition(75,40);
                            window.draw(tText);


                            Text helpText1(highscore()+"\n\nPress R to return",font,16);
                            helpText1.setPosition(5,80);
                            window.draw(helpText1);
                            window.display();



                            Event e;
                            while (window.pollEvent(e)){
                                    if (e.type == Event::Closed){
                                        music.stop();
                                        window.close();
                                        over=false;
                                        show_high=false;
                                    }

                                    if (e.type == Event::KeyPressed) {
                                        if (e.key.code == Keyboard::R){
                                            show_high=false;
                                        }
                                    }
                                }
                            }
                    }
                }
            }
        }




        if (total_rows>=4){        //Levels up when rows are completed 4 times
            level++;
            total_rows=0;

        }

        delay=start_delay-((level-1)*0.05); // Rests Delay to ensure Sure Block Does Not Fall Constantly Once Down Key is Pressed
        x_position = 0;
        rotate=0;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        gridtime+=time;

        grid_cropper( gridtime, starting);

         //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed) {                  //If cross/close is clicked/pressed
                music.stop();
                window.close(); }                           //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = -1;                         //Rotation clockwise
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    x_position = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    x_position = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::H)    //Pauses
                    pause=true;
                else if (e.key.code == Keyboard::Z)    //Rotation clockwise
                    rotate = -1;
                else if (e.key.code == Keyboard::X)   //Rotation clockwise
                    rotate = 1;
            }
        }



        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (boom!=3){
                delay=0.05;
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (boom!=3){
                delay=0.005;
            }
        }






        if (boom==3)
            {color_bomb(timer,delay,color_number,boom,starting);}
        else{
            movement(x_position);                  //  Function Set For Moving The Piece Left And Right
            rotation(rotate,shape);             //  Function Set For Moving The Piece rotate

            falling(timer, delay, color_number,shape,score,level,boom,starting,over,total_rows,highest_score);   //Function Set For Making The Piece Fall and work
        }




        window.clear(Color::Black);
        window.draw(background);




        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;                                                //Draw board
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }



        }


        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(color_number*18,0,18,18));               //Draw pieces
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }








            scoredisplay="Score\n "+std::to_string(score);
            Text scoreText(scoredisplay,font,20);
            scoreText.setPosition(240,190);           //Draw score
            window.draw(scoreText);


            leveldisplay="Level\n "+std::to_string(level);
            Text levelText(leveldisplay,font,20);         //Draw levels
            levelText.setPosition(240,245);
            window.draw(levelText);




        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}







