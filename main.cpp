#include <simplecpp>

#include "shooter.h"
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.05;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
      int count_time=0;
      int count_health=6 ;
      int count_score=0;
      int iterate=0;        //no of times the loop runs
      int flag = 0;         //used to indicate if bubble is still crossing shooter
      int check_level_2=0;  //is 0 in level1 and once score gets 2, changes to 1, used to display level 2 printed on screen
      int check_level_3=0;  //is 0 in level2 and once score gets 11, changes to 1, used to display level 3 printed on screen

void create_bubbles(double X, double Y, double r, double speed_x, double speed_y, Color colours,vector<Bubble> &bubbles);
    //declaring the function so it can be used earlier

void move_bullets(vector<Bullet> &bullets){
    // move all bullets

    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles

    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }

}


void check_collision_bubbles_bullets(vector<Bubble> &bubbles, vector<Bullet> &bullets){
     //removes the bullet and bubble when they collide and increases the score

    for (unsigned int i=0; i < bubbles.size() ; i++)  //check collision for all bubbles
    {
        for (unsigned int j=0; j <  bullets.size(); j++)   //check collision for all bullets
        {
            if((bubbles[i].get_center_y()-bubbles[i].get_radius()) <=(bullets[j].get_center_y()-bullets[j].get_height()/2)&&(bubbles[i].get_center_y()+bubbles[i].get_radius())>=(bullets[j].get_center_y()-bullets[j].get_height()/2))
            { // if the upper end of bullet lies below upper end of bubble

                  if((bubbles[i].get_center_x()-bubbles[i].get_radius()) <=(bullets[j].get_center_x()-bullets[j].get_width()/2)&&(bubbles[i].get_center_x()+bubbles[i].get_radius())>=(bullets[j].get_center_x()-bullets[j].get_width()/2))
                  {    //if the left end of bullet lies within the bubble

                       bullets.erase(bullets.begin()+j);  // if the upper end and left end of bullet lies within bubble erase the bullet
                       if(bubbles[i].get_radius()>BUBBLE_DEFAULT_RADIUS) // if bubble is larger than default size then create 2 bubbles of half radius moving in opposite direction
                       {
                           create_bubbles(bubbles[i].get_center_x(), bubbles[i].get_center_y(),bubbles[i].get_radius()/2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,bubbles[i].get_color(),bubbles);

                           // the new bubbles are created at the same x and y where original bubble is hit moving in opposite directions and are added at last in the bubbles vector
                       }

                       bubbles.erase(bubbles.begin()+i);  // the bubble which is hit gets erased
                       count_score++;     // when a bubble is hit score increases by 1

                       break;             // come out of inner loop
                  }
                  if((bubbles[i].get_center_x()-bubbles[i].get_radius()) <=(bullets[j].get_center_x()+bullets[j].get_width()/2)&&(bubbles[i].get_center_x()+bubbles[i].get_radius())>=(bullets[j].get_center_x()+bullets[j].get_width()/2))
                  {   //if the right end of bullet lies within the bubble

                      bullets.erase(bullets.begin()+j);  // if the upper end and right end of bullet lies within bubble erase the bullet
                      if(bubbles[i].get_radius()>BUBBLE_DEFAULT_RADIUS) // if bubble is larger than default size then create 2 bubbles of half radius moving in opposite direction
                      {
                           create_bubbles(bubbles[i].get_center_x(), bubbles[i].get_center_y(),bubbles[i].get_radius()/2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,bubbles[i].get_color(),bubbles);

                           // the new bubbles are created at the same x and y where original bubble is hit moving in opposite directions and are added at last in the bubbles vector
                      }
                      bubbles.erase(bubbles.begin()+i);   // the bubble which is hit gets erased
                      count_score++;     // when a bubble is hit score increases by 1

                      break;             // come out of inner loop
                  }
             }

             if((bubbles[i].get_center_y()-bubbles[i].get_radius()) <=(bullets[j].get_center_y()+bullets[j].get_height()/2)&&(bubbles[i].get_center_y()+bubbles[i].get_radius())>=(bullets[j].get_center_y()+bullets[j].get_height()/2))
             {
                 if((bubbles[i].get_center_x()-bubbles[i].get_radius()) <=(bullets[j].get_center_x()-bullets[j].get_width()/2)&&(bubbles[i].get_center_x()+bubbles[i].get_radius())>=(bullets[j].get_center_x()-bullets[j].get_width()/2))
                 {      bullets.erase(bullets.begin()+j);
                     if(bubbles[i].get_radius()>BUBBLE_DEFAULT_RADIUS)
                     {
                         create_bubbles(bubbles[i].get_center_x(), bubbles[i].get_center_y(),bubbles[i].get_radius()/2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,bubbles[i].get_color(),bubbles);
                     }
                     bubbles.erase(bubbles.begin()+i);
                      count_score++;

                    break;
                 }
                if((bubbles[i].get_center_x()-bubbles[i].get_radius()) <=(bullets[j].get_center_x()+bullets[j].get_width()/2)&&(bubbles[i].get_center_x()+bubbles[i].get_radius())>=(bullets[j].get_center_x()+bullets[j].get_width()/2))
                {      bullets.erase(bullets.begin()+j);
                     if(bubbles[i].get_radius()>BUBBLE_DEFAULT_RADIUS)
                     {
                         create_bubbles(bubbles[i].get_center_x(), bubbles[i].get_center_y(),bubbles[i].get_radius()/2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,bubbles[i].get_color(),bubbles);
                     }
                     bubbles.erase(bubbles.begin()+i);
                      count_score++;

                     break;
                }
           }
        }
        /* bubbles[i].get_center_y()
          bubbles[i].get_radius()
          bullets[i].get_width()
          bullets[i].get_height()
          bullets[i].get_center_x()
          bullets[i].get_center_y()*/
      }

}


bool check_collision_bubbles_shooter(vector<Bubble> &bubbles,Shooter &shooter){
 //returns 1 on collision between bubbles and shooter otherwise returns 0

      for (unsigned int i=0; i < bubbles.size() ; i++)    //check collision for all bubbles
      {

               if((shooter.get_head_center_y()-shooter.get_head_radius()) <=(bubbles[i].get_center_y()-bubbles[i].get_radius())&&(PLAY_Y_HEIGHT)>=(bubbles[i].get_center_y()-bubbles[i].get_radius()))
               { // the upper end of bubble is between shooter's upper end and the line

                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()-bubbles[i].get_radius())&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()-bubbles[i].get_radius()))
                  {  //the left end of bubble lies within the shooter

                    if(flag!=1)       //when the bubble touches the shooter 1st time flag is 0
                    {
                        flag = 1;     // after touching once flag becomes 1 so that the function doesnot return 1 again and again
                        return 1;     //return 1 on collision
                    }
                     else return 0;   //when the bubble is still crossing through shooter don't reduce health once more
                  }
                   if((shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()+bubbles[i].get_radius())&&(shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()+bubbles[i].get_radius()))
                  {  //the right end of bubble lies within the shooter

                       if(flag!=1)
                       {
                            flag = 1;
                            return 1;
                       }
                       else return 0;
                  }
                  //for large bubbles
                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()-bubbles[i].get_radius()/2.0)&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()-bubbles[i].get_radius()/2.0))
                  {  //the x coordinate at half radius on life side of bubble lies within the shooter

                    if(flag!=1)
                    {
                        flag = 1;
                        return 1;
                    }
                    else return 0;
                  }
                  if((shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()+bubbles[i].get_radius()/2.0)&&(shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()+bubbles[i].get_radius()/2.0))
                  {  //the x coordinate at half radius on right side of bubble lies within the shooter

                       if(flag!=1)
                       {
                            flag = 1;
                            return 1;
                       }
                        else return 0;
                  }
                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x())&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()))
                  {   //the x coordinate of center of bubble lies within the shooter

                    if(flag!=1)
                    {
                        flag = 1;
                        return 1;
                    }
                    else return 0;
                  }
               }

               else if((shooter.get_head_center_y()-shooter.get_head_radius()) <=(bubbles[i].get_center_y()+bubbles[i].get_radius())&&(PLAY_Y_HEIGHT)>=(bubbles[i].get_center_y()+bubbles[i].get_radius()))
              {   // the lower end of bubble is between shooter's upper end and the line

                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()-bubbles[i].get_radius())&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()-bubbles[i].get_radius()))
                  {  //the left end of bubble lies within the shooter

                       if(flag!=1)
                       {
                           flag = 1;
                           return 1;
                       }
                       else return 0;
                  }
                   if((shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()+bubbles[i].get_radius())&&(shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()+bubbles[i].get_radius()))
                  {  //the right end of bubble lies within the shooter

                       if(flag!=1)
                       {
                            flag = 1;
                            return 1;
                       }
                       else return 0;
                  }
                 //for large bubbles
                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()-bubbles[i].get_radius()/2.0)&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()-bubbles[i].get_radius()/2.0))
                  {  //the x coordinate at half radius on life side of bubble lies within the shooter

                    if(flag!=1)
                    {
                        flag = 1;
                        return 1;
                    }
                    else return 0;
                  }
                  if((shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()+bubbles[i].get_radius()/2.0)&&(shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x()+bubbles[i].get_radius()/2.0))
                  {  //the x coordinate at half radius on right side of bubble lies within the shooter

                       if(flag!=1)
                       {
                            flag = 1;
                            return 1;
                       }
                        else return 0;
                  }
                  if((shooter.get_body_center_x()-shooter.get_body_width()/2) <=(bubbles[i].get_center_x())&&(shooter.get_body_center_x()+shooter.get_body_width()/2) >=(bubbles[i].get_center_x()))
                  {  //the x coordinate of center of bubble lies within the shooter

                    if(flag!=1)
                    {
                        flag = 1;
                        return 1;
                    }
                     else return 0;
                  }
             }

        }

        flag=0; // flag gets 0 when bubble gets out of shooter
        return 0;

}

void create_bubbles(double X, double Y, double r, double speed_x, double speed_y, Color colours,vector<Bubble> &bubbles)
{
    // create initial bubbles in the game

    bubbles.push_back(Bubble(X, Y, r, -speed_x, speed_y,BUBBLE_DEFAULT_AY, colours));
    bubbles.push_back(Bubble(X, Y, r, speed_x, speed_y,BUBBLE_DEFAULT_AY, colours));

    //return bubbles;
}

int main()
{
     initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

     Text LEVEL1(WINDOW_X/2.0, WINDOW_Y/2.0, "Level 1" );  //when game starts display "LEVEL 1"

     wait(3);

     LEVEL1.setColor(COLOR(255,255,255));    // to make it disappear colour it same as background
     LEVEL1.setFill(true);


    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);  //at left end on bottom

    string time("Time: __/50");
    Text text1(LEFT_MARGIN, TOP_MARGIN, time);              //at left end on top

    string health("Health: _/6");
    Text text2(WINDOW_X- LEFT_MARGIN, TOP_MARGIN, health);  //at right end on top

    string score("Score: __");
    Text text3(WINDOW_X- LEFT_MARGIN, BOTTOM_MARGIN, score ); //at right end on bottom

    string level_display("Level: 1/3");
    Text text4(WINDOW_X/2, BOTTOM_MARGIN, level_display );    //in middle on bottom


    // Intialize the shooter(level1)
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles(level1)
    vector<Bubble> bubbles;
    create_bubbles(BUBBLE_START_X, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,COLOR(255,105,180), bubbles);

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;

    // Main game loop
    while (true)
    {
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;

        }

        time[time.length()-5]= count_time/10 + 48;    //second last digit of count time
        time[time.length()-4]= count_time%10  + 48;    // last digit of count time


        text1.setMessage(time);
        iterate++;
        if(iterate%20==0) count_time++;   // step_time is 0.05 so for 1 second, time must increase after 20 iterations




        if(check_collision_bubbles_shooter(bubbles,shooter)) count_health--;  //reduce health if 1 is returned
        health[health.length()-3] = count_health+48;    //3rd last letter is the health
        text2.setMessage(health);

        if(count_health ==0 ||count_time== 50) {  // Game over
           Text GAMEOVER(WINDOW_X/2.0, WINDOW_Y/2.0, "Game Over" );
           wait(2);
           break ;       //come out of game loop
       }



        score[score.length()-2]= count_score/10 + 48;       //second last digit changes second last letter of string
        score[score.length()-1]= count_score%10  + 48;      //last digit changes last letter of string
        text3.setMessage(score);



        if(check_level_2==0)     //initially its 0
        if(count_score==2)       // as score gets 2 print level 2
        {
            Text LEVEL2(WINDOW_X/2.0, WINDOW_Y/2.0, "Level 2" ); //print level 2

            wait(2);

            LEVEL2.setColor(COLOR(255,255,255));   //the message disappears
            LEVEL2.setFill(true);

            create_bubbles(BUBBLE_START_X, BUBBLE_START_Y, 2*BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,COLOR(0,0,180), bubbles);   // create 2 bubbles of double size
            bubbles.push_back(Bubble(BUBBLE_START_X, BUBBLE_START_Y, 2*BUBBLE_DEFAULT_RADIUS, 20, 20,BUBBLE_DEFAULT_AY,COLOR(0,0,180)));             //create one more
            check_level_2=1;   // after printing once dont print again
            count_time=0;      //time starts from 0 again
            iterate=0;

            level_display[level_display.length()-3]= 50;
        }


        if(check_level_3==0)    //initially its 0
        if(count_score==11)     // as score gets 11 print level 3
        {
            Text LEVEL3(WINDOW_X/2.0, WINDOW_Y/2.0, "Level 3" );     //print level 3

            wait(2);

            LEVEL3.setColor(COLOR(255,255,255));    //the message disappears
            LEVEL3.setFill(true);

            create_bubbles(BUBBLE_START_X, BUBBLE_START_Y, 3*BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY,COLOR(180,0,0), bubbles);
            bubbles.push_back(Bubble(BUBBLE_START_X, BUBBLE_START_Y, 3*BUBBLE_DEFAULT_RADIUS, 20, 20,BUBBLE_DEFAULT_AY,COLOR(180,0,0)));
            check_level_3=1;   //after printing once, it becomes 1 so that it is not printed again
            count_time=0;
            iterate=0;

            level_display[level_display.length()-3]= 51;
        }


        text4.setMessage(level_display);


         if(count_score==32 ) {  //Maximum score possible
           Text WIN(WINDOW_X/2.0, WINDOW_Y/2.0, "Congratulations!" );
           wait(2);
           break ;      //come out of game loop
       }
        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        wait(STEP_TIME);
        check_collision_bubbles_bullets(bubbles,bullets);


    }
    }
