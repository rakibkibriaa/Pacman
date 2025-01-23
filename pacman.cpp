#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <iostream>
#include<mmsystem.h>
#define NULL 0
int dx = 2;
int dx2 = 2;
int screenWidth = 1000;
int screenHeight = 700;
int y = 652 - 24*18 - 16 - 4;//656-16;
int x = 124 + 4;//136;   //139 - 16/2
int sign = 1;
int pac_initial_x = x;
int pac_initial_y = y;
int mode = 0;
int enterName = 0;
int p_y,p_x,r_x,r_y;
int score = 0;
int gameState = -1;
int loadMenu = 1;
int res = 0;
int g_count = 4;
int g_cur=4;
int gameOnSound = 0;
int opt_highcore,opt_instruction;
int loadGame;
int menuSound = 1;
int playGameSound = 0;


int helper;

int pause = 0;

int fire = 0;
int fire_dir = 0;
int fire_r = 0;
int fire_l = 0;
int fire_u = 0;
int fire_d = 0;
int fire_row,fire_col;

int f_r_x,f_r_y;
int fire_x,fire_y;

int enterNamelen = 0;


int prev_x =-1,prev_y=-1;

double xh=500,yh=360+200,hx,hy,ph,H,M,S;
int i;

char string[100];
char player_name[10][100];
int player_score[100];
int pl_time[100];
int player_time[100];


int velocity = 2;

char str_player_score[10][100];
char str_player_time[10][100];



int row,col,g_row,g_col;

int point[21][19]={0};

int g_r_x[5],g_r_y[5];



int g_initial_x[5]={112 + 12*16 - 8 ,112 + 13*16,112 + 14*16 + 8,112 + 13*16,112 + 13*16 },g_initial_y[5]={644 -24*2 -16 + 4 - 6 * 24,644 -24*1 -16 + 4 - 6 * 24,644 -24*2 -16 + 4 - 6 * 24,644 -24*2 -16 + 4 - 6 * 24, 644 -24*2 -16 + 4 - 6 * 24};
int g_real_x[5],g_real_y[5];
char image[5][40]={"pics//blinky_l.bmp","pics//inky_l.bmp","pics//pinky_l.bmp","pics//clyde_l.bmp","pics//clyde_l.bmp"};
char image2[5][40]={"pics//blinky_r.bmp","pics//inky_r.bmp","pics//pinky_r.bmp","pics//clyde_r.bmp","pics//clyde_r.bmp"};


int t1,t2,tim,tim2,tim3,tim4,tim5,t4,time_rep,time_normal;


typedef struct{
    int vel;
    int right;
    int left;
    int up;
    int down;
    int transition_up;
    int transition_down;
    int transition_left;
    int transition_right;

}movement;

typedef struct{
    int highscore;
    int position;
    int time;
    char name[200];
    int used;
}player;

int visited[21][19];

int gh_r[5],gh_c[5];

int gameOver;

int life;



movement pac;

movement g_move[5];


char enterName_str[100];

void reset(int i)
{

      g_move[i].down = 0;
      g_move[i].up = 0;
      g_move[i].right = 0;
      g_move[i].left = 0;
      g_move[i].transition_down = 0;
      g_move[i].transition_up = 0;
      g_move[i].transition_right = 0;
      g_move[i].transition_left = 0;
      g_real_x[i] = g_initial_x[i];
      g_real_y[i] = g_initial_y[i];
    if(i==0)
        g_move[0].up = 1;
    if(i==1)
        g_move[1].right = 1;
    if(i==2)
        g_move[2].left = 1;
    if(i==3)
        g_move[3].up = 1;

}
void pacReset()
{
    x = pac_initial_x;
    y = pac_initial_y;

    pac.transition_down = 0;
    pac.transition_up = 0;
    pac.transition_right = 0;
    pac.transition_left = 0;
    pac.down = 0;
    pac.up = 0;
    pac.right = 0;
    pac.left = 0;


}

int maze[21][19] =
{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int mazeEmptychecker();

void iDraw()
{

    iClear();


    if(loadMenu)
    {


        iPauseTimer(2);

        iShowBMP(0,0,"pics//menu.bmp");


        if(menuSound)
        {
              PlaySound("intro.wav",NULL,SND_ASYNC);
              menuSound = 0;
        }

    }
    else if(opt_instruction)
    {
        iShowBMP(0,0,"pics//instructions.bmp");
    }
    else if(enterName == 1)
    {
        iSetColor(255,255,255);
        enterName_str[enterNamelen] = '\0';

        iShowBMP(0,0,"pics//enterName.bmp");
        iFilledRectangle(350, 400, 260, 40);
        iSetColor(0,0,0);
        iText(360,412,enterName_str,GLUT_BITMAP_TIMES_ROMAN_24);


    }

    else if(opt_highcore)
    {


            FILE* fp = fopen("highscore.txt","r");

            int i = 0;

            while(1)
            {
                char str1[100];

                fgets(str1,100,fp);


                if(feof(fp))
                    break;
                sscanf(str1,"%d %d %[^\n]s",&player_score[i],&pl_time[i],player_name[i]);


                snprintf(str_player_score[i],sizeof(str_player_score[i]),"%d",player_score[i]);


                iSetColor(0,0,255);

                int sec = pl_time[i] % 60;
                int min = (pl_time[i] / 60)%60;
                int h = (pl_time[i]/3600);

                char second[200],minute[200],hour[200];
                snprintf(second,sizeof(second),"%02d",sec);
                snprintf(minute,sizeof(minute),"%02d:",min);
                snprintf(hour,sizeof(hour),"%02d:",h);

                strcat(str_player_time[i],hour);
                strcat(str_player_time[i],minute);
                strcat(str_player_time[i],second);


                i++;


            }
            fclose(fp);


            iShowBMP(0,0,"pics//highscoreimg.bmp");

            for(int i=0;i<10;i++)
            {
                iSetColor(255,255,255);

                iText(190,455-i*45,player_name[i],GLUT_BITMAP_TIMES_ROMAN_24);

                iText(485,455-i*45,str_player_score[i],GLUT_BITMAP_TIMES_ROMAN_24);

                iText(820,455-i*45,str_player_time[i],GLUT_BITMAP_TIMES_ROMAN_24);

                strcpy(str_player_time[i],"\0");

            }

    }
    else if(life == 0 && gameState == 0 || life==0 && gameState == 4)
    {
        FILE *fp;

        fp = fopen("players.txt","a");




        fprintf(fp,"%d %d",score,tim);
        fputs(enterName_str,fp);

        strcpy(enterName_str,"\0");

        fprintf(fp,"\n");

        fclose(fp);

        fp = fopen("players.txt","r");

        char str1[100];

        player p[100];
        int i = 0;
        while(1)
        {
            char name[100],str1[200];
            char ck;
            int score,g;


           fgets(str1,200,fp);


            sscanf(str1,"%d%d%[^\n]s",&p[i].highscore,&p[i].time,p[i].name);



            if(feof(fp))
                break;
            i++;

        }
        fclose(fp);

        int temp[100];
        int time[100];

        for(int j=0;j<i;j++)
        {

            temp[j] = p[j].highscore;


        }
        for(int j=0;j<i;j++)
        {

            time[j] = p[j].time;

        }
        for(int k=0;k<i;k++)
        {
            for(int l=k;l<i;l++)
            {
                if(temp[k] == temp[l])
                {
                    if(time[l] < time[k])
                    {

                         int t = time[k];
                         time[k] = time[l];
                         time[l] = t;

                         char st[100];
                         strcpy(st,p[k].name);
                         strcpy(p[k].name,p[l].name);
                         strcpy(p[l].name,st);

                    }
                }
                else if(temp[k] < temp[l])
                {
                    int t = temp[k];
                    temp[k] = temp[l];
                    temp[l] = t;

                        char st[100];
                         strcpy(st,p[k].name);
                         strcpy(p[k].name,p[l].name);
                         strcpy(p[l].name,st);
                }
            }
        }

        fclose(fp);


        for(int j=0;j<i;j++)
        {
            printf("%d %d %s\n",temp[j],time[j],p[j].name);
        }

        fp = fopen("highscore.txt","w");

        int mini;



        (i < 10) ? mini = i : mini = 10;

        for(int j=0;j<mini;j++)
        {

            fprintf(fp,"%d %d %s\n",temp[j],time[j],p[j].name);

        }
        fclose(fp);
        opt_highcore = 1;

    }

    else if(gameState == 0 || gameState == 1 || gameState == 2 || gameState == 3 || gameState == 4)
    {

        	iText(650,250,string);


            iSetColor(20,200,255);


            iSetColor(0,255,0);


            char sc[100];
            snprintf(sc,sizeof(sc),"Score: %d",score);

            iText(680,600,sc,GLUT_BITMAP_TIMES_ROMAN_24);


        if(mazeEmptychecker()){
            life = 0;
        }

        if(!pause)
            {
                iResumeTimer(0);
                iResumeTimer(1);
                iResumeTimer(2);
            }
        else
        {
                iPauseTimer(0);
                iPauseTimer(1);
                iPauseTimer(2);
        }


        //............................time.......................///

        int sec = tim % 60;
        int min = (tim / 60)%60;
        int h = (tim/3600);

        char second[200],minute[200],hour[200];
        snprintf(second,sizeof(second),"%02d",sec);
        snprintf(minute,sizeof(minute),"%02d:",min);
        snprintf(hour,sizeof(hour),"%02d:",h);


        iText(750,650,second,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(720,650,minute,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(690,650,hour,GLUT_BITMAP_TIMES_ROMAN_24);


        for(int i=0;i<21;i++)
        {
            for(int j=0;j<19;j++)
            {
                if(maze[i][j]){
                    iShowBMP(100+j*24,screenHeight-(24*i)-48,"pics//brick.bmp");
                    point[i][j] = 1;

                    }
             else
                 {
                    if(!point[i][j])
                    {

                        if(i==17 && j==8)
                             iFilledCircle(112+j*24,screenHeight-(24*i)-36,6,100);
                        else if(i==13 && j==17)
                            iFilledCircle(112+j*24,screenHeight-(24*i)-36,6,100);
                        else if(i==5 && j==1)
                            iFilledCircle(112+j*24,screenHeight-(24*i)-36,6,100);
                        else if(i==7 && j==12)
                            iFilledCircle(112+j*24,screenHeight-(24*i)-36,6,100);
                        else if(i==5 && j==1)
                            iFilledCircle(112+j*24,screenHeight-(24*i)-36,6,100);
                        else if(i==19 && j==17)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//fruit.bmp");
                        else if(i==19 && j==17)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//fruit.bmp");
                        else if(i==2 && j==17)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//fruit.bmp");
                        else if(i==7 && j==6)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//fruit.bmp");
                        else if(i==5 && j==10)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//banana.bmp");
                        else if(i==7 && j==1)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//banana.bmp");
                        else if(i==17 && j==1)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//2x.bmp");
                        else if(i==11 && j==9)
                            iShowBMP(112+j*24-8,screenHeight-(24*i)-36 - 8,"pics//2x.bmp");
                        else
                            iFilledCircle(112+j*24,screenHeight-(24*i)-36,2,100);   //point;

                    }


                }
            }
        }


        for(int i=1; i<= life;i++)
        {
            iSetColor(255,0,0);
            iFilledCircle(665 + i* 30,550,10,100);
        }

        iShowBMP(600,350,"pics//backmenu.bmp");

        iShowBMP(600,250,"pics//savegame.bmp");

        if(!pause)
            iShowBMP(600,150,"pics//pausegame.bmp");
        else
            iShowBMP(600,140,"pics//resumegame.bmp");



        iShowBMP(x,y,"pics//pac_u_1.bmp");
        if(fire_x && fire_y)
            iShowBMP(fire_x,fire_y,"pics//fire.bmp");

        for(int i=0;i<g_count;i++)
        {
        if(gameState == 0 || gameState == 4){
            if(g_move[i].transition_left || g_move[i].transition_up && x <= g_real_x[i] || g_move[i].transition_down && x <= g_real_x[i])
                iShowBMP(g_real_x[i],g_real_y[i],image[i]);
            if(g_move[i].transition_right || g_move[i].transition_up && x > g_real_x[i] || g_move[i].transition_down && x > g_real_x[i])
            {
                iShowBMP(g_real_x[i],g_real_y[i],image2[i]);
            }

        }
        else if(gameState == 1 || gameState == 2)
            iShowBMP(g_real_x[i],g_real_y[i],"pics//freeze.bmp");

        }

        p_y = y + 8;
        p_x = x + 8;
        p_x -= 112;
        p_y = screenHeight- (p_y + 36);     // pacman's


          if(fire && !pause)
          {

              if(fire_dir == 0)
              {
                 fire_dir = 1;
                 fire_r = 0;
                 fire_l = 0;
                 fire_u = 0;
                 fire_d = 0;

                    if(g_move[1].transition_right)
                        fire_r = 1;
                    else if(g_move[1].transition_left)
                        fire_l = 1;
                    else if(g_move[1].transition_down)
                        fire_d = 1;
                    else if(g_move[1].transition_up)
                        fire_u = 1;

              }

                f_r_x = fire_x + 8;
                f_r_y = fire_y + 8;
                f_r_x -= 112;
                f_r_y = screenHeight- (f_r_y + 36);

                if(f_r_x % 24==0 && f_r_y % 24 == 0 && fire_dir)
                {

                    fire_col = f_r_x/24;
                    fire_row = f_r_y/24;

                    if(fire_r && maze[fire_row][fire_col+1])
                    {
                        fire_x = 0;
                        fire_y = 0;
                        fire = 0;
                        fire_dir = 0;

                    }
                    else if(fire_l && maze[fire_row][fire_col-1])
                    {
                        fire_x = 0;
                        fire_y = 0;
                        fire = 0;
                        fire_dir = 0;

                    }
                    else if(fire_u && maze[fire_row - 1][fire_col])
                    {
                        fire_x = 0;
                        fire_y = 0;
                        fire = 0;
                        fire_dir = 0;

                    }
                    else if(fire_d && maze[fire_row + 1][fire_col])
                    {
                        fire_x = 0;
                        fire_y = 0;
                        fire = 0;
                        fire_dir = 0;

                    }
                }


                if(fire_r)
                    fire_x += 4;
                else if(fire_l)
                    fire_x -= 4;
                else if(fire_d)
                    fire_y -= 4;
                else if(fire_u)
                    fire_y += 4;

                if(abs(fire_x - x) <= 8 && abs(fire_y - y) <=8 )
                {
                    life--;
                    fire = 0;
                    fire_dir = 0;
                    fire_x = 0;
                    fire_y = 0;
                    for(int i=0;i<4;i++)
                        reset(i);
                    pacReset();

                    PlaySound("death.wav",NULL,SND_ASYNC);

                }


        }

                if(tim - tim4 > 3 && gameState == 3)
                {

                    g_count = g_cur;
                    gameState = 0;
                    iResumeTimer(1);

                }
                if(tim - tim3 > 5 && gameState == 2)
                {
                    if(g_count==0)
                        g_count  = g_cur;
                    gameState = 0;
                    iResumeTimer(1);


                }
                if(tim - tim2 > 5 && gameState == 1)
                {
                    if(g_count==0)
                        g_count  = g_cur;
                    gameState = 0;
                       iResumeTimer(1);

                }
                if(tim - tim5 > 5 && gameState == 4)
                {
                    if(g_count==0)
                        g_count  = g_cur;
                    gameState = 0;
                    dx = 2;
                       iResumeTimer(1);

                }


        for(int i=0;i<g_count;i++)
        {

            g_r_x[i] = g_real_x[i] + 8;
            g_r_y[i] = g_real_y[i] + 8;
            g_r_x[i] -= 112;
            g_r_y[i] = screenHeight- (g_r_y[i] + 36);

            if(g_r_x[i] % 24 == 0 && g_r_y[i] % 24 == 0)
            {

                 if(score > 200 && g_count == 4 && tim - time_normal > 2)
                    {

                        if(g_r_x[3] % 24 == 0 && g_r_y[3] % 24 == 0)
                        {
                            time_rep = tim;
                            g_count = 5;
                            g_cur = g_count;

                            g_r_x[4] = g_r_x[3];
                            g_r_y[4] = g_r_y[3];
                            g_real_x[4] = g_real_x[3];
                            g_real_y[4] = g_real_y[3];


                            gh_r[4] = g_r_y[3]/24;
                            gh_c[4] = g_r_x[3]/24;



                            g_move[4].vel = 1;

                            if(g_move[3].transition_right)
                            {
                                 if(maze[gh_r[4]][gh_c[4] + 1] == 0)
                                    g_move[4].transition_right  = 1;


                            }
                            else if(g_move[3].transition_left)
                            {
                                 if(maze[gh_r[4]][gh_c[4] - 1] == 0)
                                    g_move[4].transition_left  = 1;


                            }
                           else if(g_move[3].transition_up)
                            {
                                if(maze[gh_r[4] - 1][gh_c[4]] == 0)
                                    g_move[4].transition_up  = 1;

                            }
                           else if(g_move[3].transition_down)
                            {
                                if(maze[gh_r[4] + 1][gh_c[4]] == 0)
                                    g_move[4].transition_down= 1;

                            }

                        }

                    }
                    else if (score > 10 && g_count == 5 && tim - time_rep > 5)
                    {
                        g_count = 4;
                        g_cur = g_count;
                        time_normal = tim;
                    }

                 gh_r[i] = g_r_y[i]/24;
                 gh_c[i] = g_r_x[i]/24;

                if(gameState == 1)      // freeze
                {
                        fire = 0;
                        fire_dir = 0;
                        fire_x = 0;
                        fire_y = 0;
                    if(g_count==0)
                        g_count  = 4;

                        dx = 2;


                      g_move[i].vel  = 1;
                        iResumeTimer(1);
                }
                if(gameState == 2)     // pause
                {
                        fire = 0;
                        fire_dir = 0;
                        fire_x = 0;
                        fire_y = 0;
                    if(g_count==0)
                        g_count  = 4;

                    dx = 2;


                    iPauseTimer(1);
                }
                if(gameState == 3) // vanish
                {
                        fire = 0;
                        fire_dir = 0;
                        fire_x = 0;
                        fire_y = 0;

                    iPauseTimer(1);

                    g_count = 0;
                    dx = 2;


                }

                else if(gameState == 0 && score >= 200 || gameState == 4 && score >= 200)
                {
                    if(i!=4)
                        g_move[i].vel = 2;
                    if(i==4)
                        g_move[i].vel = 1;

                }
                else if(gameState == 0 && score < 200)
                {
                    g_move[i].vel = 1;
                }
                if(score > 300 && i==1)
                {

                    if(tim % 2 ==0)
                    {

                    if(!fire){
                        fire_x = g_real_x[1];
                        fire_y = g_real_y[1];
                        fire = 1;
                    }

                    }
                }

            if(i==0)
            {


                if(g_move[i].transition_up)
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                          if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                                g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;


                                    }
                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                         g_move[i].left = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down==0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                }


                            }


                }
                else if(g_move[i].transition_down)
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y > g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                           g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                    else
                                    {
                                         if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 && g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;


                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }

                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y > g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                     else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;


                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                    }
                                }


                            }
                }
                else if(g_move[i].transition_right)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y > g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                   else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                      g_move[i].left = 1;
                                   else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                       g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                     g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }


                        }
                }
                else if(g_move[i].transition_left)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                  else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;


                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;




                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;


                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                            }


                        }


                 }
            }

    //....................................................................................................................................//
            else if(i==1)
            {


                if(g_move[i].transition_up && maze[gh_r[i] - 1][gh_c[i]])
                {


                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                          if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                                g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;


                                    }
                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                         g_move[i].left = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                }


                            }


                }
                else if(g_move[i].transition_down && maze[gh_r[i] + 1][gh_c[i]])
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                           g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                    else
                                    {
                                         if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;


                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }

                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                     else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;


                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                    }
                                }


                            }
                }
                else if( g_move[i].transition_right && maze[gh_r[i]][gh_c[i] + 1])
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                   else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                      g_move[i].left = 1;
                                   else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                       g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                     g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }


                        }
                }
                else if( g_move[i].transition_left && maze[gh_r[i]][gh_c[i] - 1])
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y > g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                  else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                 else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;





                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;



                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                            }

                        }


                 }
            }
    //...................................................................................................................//
            else if(i==2)
            {


                if( g_move[i].transition_up)
                {


                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                          if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                                g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;


                                    }
                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                         g_move[i].left = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                }
    ;
                            }


                }
                else if(g_move[i].transition_down)
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                           g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                    else
                                    {
                                         if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;


                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }

                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                     else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                       else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;


                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                    }
                                }


                            }
                }
                else if(g_move[i].transition_right && maze[gh_r[i]][gh_c[i] + 1])
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                   else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                      g_move[i].left = 1;
                                   else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                       g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                     g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }


                        }
                }
                else if( g_move[i].transition_left && maze[gh_r[i]][gh_c[i] - 1])
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                  else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;



                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                            }


                        }


                 }
            }

            //......................................................................//

            else if(i==3)
            {


                if( g_move[i].transition_up && maze[gh_r[i] - 1][gh_c[i]])
                {


                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                          if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                                g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;


                                    }
                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                         g_move[i].left = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                }


                            }


                }
                else if(g_move[i].transition_down && maze[gh_r[i] + 1][gh_c[i]])
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                           g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                    else
                                    {
                                         if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;


                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }

                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                     else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;


                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                    }
                                }


                            }
                }
                else if( g_move[i].transition_right)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y > g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                   else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                      g_move[i].left = 1;
                                   else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                       g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                     g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }


                        }
                }
                else if( g_move[i].transition_left)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                  else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;




                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                            }


                        }


                 }
            }
            else if(i==4)
            {


                if(g_move[i].transition_up)
                {


                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                          if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                                g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 && g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 && g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;


                                    }
                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y >= g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                         g_move[i].left = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down==0)
                                        g_move[i].up = 1;
                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    }
                                }


                            }


                }
                else if(g_move[i].transition_down)
                {
                            if(x >= g_real_x[i])
                            {
                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;
                                int d1 = x - g_real_x[i];
                                if(y > g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                           g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;

                                    }
                                    else
                                    {
                                         if(maze[gh_r[i] - 1][gh_c[i]]==0 &&  g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 && g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                        if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;

                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;


                                      else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    }

                                }
                            }
                            else
                            {

                                   g_move[i].right = 0;
                                   g_move[i].left = 0;
                                   g_move[i].up = 0;
                                   g_move[i].down = 0;

                                int d1 = g_real_x[i] - x;
                                if(y > g_real_y[i])
                                {
                                    int d2 = y - g_real_y[i];

                                    if(d1 > d2)
                                    {
                                      if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                     else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                    }
                                    else
                                    {
                                        if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;
                                        else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                            g_move[i].left = 1;
                                        else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                        else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;


                                    }
                                }
                                else
                                {
                                    int d2 = g_real_y[i] - y;

                                    if(d1 > d2)
                                    {
                                       if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                      else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                      else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;


                                      else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                        g_move[i].up = 1;

                                    }
                                    else
                                    {

                                    if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;


                                    }
                                }


                            }
                }
                else if( g_move[i].transition_right)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y > g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;
                                   else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                      g_move[i].left = 1;
                                   else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                       g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {

                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                     g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;
                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;


                                  else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }


                        }
                }
                else if( g_move[i].transition_left)
                {
                        if(x >= g_real_x[i])
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;
                            int d1 = x - g_real_x[i];
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                    if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;

                                    else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;

                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;

                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                        g_move[i].right = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                        g_move[i].left = 1;
                                    else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                        g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                            g_move[i].right = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                            g_move[i].down = 1;
                                  else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                            g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                            g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;

                                }
                            }
                        }
                        else
                        {
                               g_move[i].right = 0;
                               g_move[i].left = 0;
                               g_move[i].up = 0;
                               g_move[i].down = 0;

                            int d1 = g_real_x[i] - x;
                            if(y >= g_real_y[i])
                            {
                                int d2 = y - g_real_y[i];

                                if(d1 > d2)
                                {
                                  if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                    g_move[i].up = 1;


                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;




                                }
                                else
                                {
                                    if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down == 0)
                                        g_move[i].up = 1;
                                    else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right==0)
                                        g_move[i].left = 1;

                                   else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                      g_move[i].right = 1;
                                   else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;

                                }
                            }
                            else
                            {
                                int d2 = g_real_y[i] - y;

                                if(d1 > d2)
                                {
                                   if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;
                                  else if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                    else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                                else
                                {

                                if(maze[gh_r[i] + 1][gh_c[i]]==0 &&  g_move[i].transition_up == 0)
                                    g_move[i].down = 1;
                                else if(maze[gh_r[i]][gh_c[i] - 1]==0 &&  g_move[i].transition_right == 0)
                                    g_move[i].left = 1;

                                else if(maze[gh_r[i]][gh_c[i] + 1]==0 &&  g_move[i].transition_left == 0)
                                    g_move[i].right = 1;

                                else if(maze[gh_r[i] - 1][gh_c[i]]==0 && g_move[i].transition_down==0)
                                    g_move[i].up = 1;

                                }
                            }

                        }
                 }
            }

        }

            if(g_move[i].right && maze[gh_r[i]][gh_c[i] + 1] == 0)
            {
                 g_move[i].transition_right = 1;
                 g_move[i].transition_left = 0;
                 g_move[i].transition_up = 0;
                 g_move[i].transition_down = 0;
            }
            else if(g_move[i].left && maze[gh_r[i]][gh_c[i] - 1] == 0)
            {


                 g_move[i].transition_right = 0;
                 g_move[i].transition_left = 1;
                 g_move[i].transition_up = 0;
                 g_move[i].transition_down = 0;
            }
            else if(g_move[i].up && maze[gh_r[i] - 1][gh_c[i]] == 0)
            {
                 g_move[i].transition_right = 0;
                 g_move[i].transition_left = 0;
                 g_move[i].transition_up = 1;
                 g_move[i].transition_down = 0;
            }
           else if(g_move[i].down && maze[gh_r[i] + 1][gh_c[i]] == 0)
            {

                 g_move[i].transition_right = 0;
                 g_move[i].transition_left = 0;
                 g_move[i].transition_up = 0;
                 g_move[i].transition_down = 1;
            }

            if(abs(x-g_real_x[i])<= 8 && abs(y-g_real_y[i])<= 8)
            {
                if(gameState == 0 ||  gameState == 4){

                    fire = 0;
                    fire_dir = 0;
                    fire_x = 0;
                    fire_y = 0;
                    g_count = 4;
                    PlaySound("death.wav",NULL,SND_ASYNC);
                    pacReset();
                    for(int i=0;i<g_count;i++)
                        reset(i);
                    life--;

                }
                else if(gameState == 1 || gameState == 2)
                {

                        prev_x = g_real_x[i],prev_y = g_real_y[i];

                        iText(prev_x,prev_y,"200",GLUT_BITMAP_9_BY_15);
                             score += 200;
                        PlaySound("eatghost.wav",NULL,SND_ASYNC);

                        reset(i);

                }
            }
        }

        //.........................................................................................................................................//



    /////////................................FOR PACMAN............................../////////////////////
        if(p_y % 24==0 && p_x %24==0){



             col = p_x/24;
             row = p_y/24;

                if(gameState == 4)
                {
                    if(p_x % 24==0 && p_y %24== 0)
                        dx = 4;


                }
            if(point[row][col] == 0)
            {
                // for points



                if(!(row==19 && col==1)){
                    score += 10;


                  }
                   point[row][col] = 1;

                  if(row==17 && col==8 || row ==13 && col == 17 || row==5 && col==1 || row==7 && col==12 || row==5 && col==1){
                        gameState = 1,tim2 = tim;
                        PlaySound("fruit.wav",NULL,SND_ASYNC);

                  }
                  if(row==19 && col==17 || row==2 && col==17 || row==7 && col==6){
                        gameState = 2,tim3 = tim;
                        PlaySound("fruit.wav",NULL,SND_ASYNC);

                  }
                  if(row==17 && col==1 || row==11 && col==9){
                        gameState = 4 , tim5 = tim;
                        PlaySound("fruit.wav",NULL,SND_ASYNC);
                    }

                    if(row==5 && col==10 || row==7 && col==1){
                        gameState = 3,tim4 = tim;
                        PlaySound("fruit.wav",NULL,SND_ASYNC);
                    }

            }
          if(pac.up && maze[row-1][col]==0)
          {
            pac.transition_down = 0;
            pac.transition_up = 0;
            pac.transition_right = 0;
            pac.transition_left = 0;

            iShowBMP(x,y,"pics//pac_u_1.bmp");

            iSetColor(255,0,0);

            pac.transition_up = 1;

          }
           else if(pac.up && maze[row-1][col])
          {

            if(pac.transition_right){
              iShowBMP(x,y,"pics//pac_r_1.bmp");


            }
            else if(pac.transition_left){
              iShowBMP(x,y,"pics//pac_l_1.bmp");

            }
            else if(pac.transition_up){
              iShowBMP(x,y,"pics//pac_u_1.bmp");

            }
            else if(pac.transition_down){

              iShowBMP(x,y,"pics//pac_d_1.bmp");

            }

          }
          else if(pac.down  && maze[row+1][col]==0)
          {
          pac.transition_down = 0;
          pac.transition_up = 0;
          pac.transition_right = 0;
          pac.transition_left = 0;

          iShowBMP(x,y,"pics//pac_d_1.bmp");

          pac.transition_down = 1;

          }
          else if(pac.down  && maze[row+1][col]){

            if(pac.transition_right){
                iShowBMP(x,y,"pics//pac_r_1.bmp");
            }
            else if(pac.transition_left){
              iShowBMP(x,y,"pics//pac_l_1.bmp");
            }
            else if(pac.transition_up){
              iShowBMP(x,y,"pics//pac_u_1.bmp");

            }
            else if(pac.transition_down){
              iShowBMP(x,y,"pics//pac_d_1.bmp");
            }

          }
          if(pac.right && maze[row][col+1]==0)
          {
               pac.transition_down = 0;
               pac.transition_up = 0;
               pac.transition_right = 0;
               pac.transition_left = 0;

              iShowBMP(x,y,"pics//pac_r_1.bmp");

              pac.transition_right = 1;

          }
          else if(pac.right && maze[row][col+1]){
            if(pac.transition_right){

              iShowBMP(x,y,"pics//pac_r_1.bmp");

            }
             else if(pac.transition_left){
              iShowBMP(x,y,"pics//pac_l_1.bmp");
            }
            else if(pac.transition_up){
              iShowBMP(x,y,"pics//pac_u_1.bmp");

            }
            else if(pac.transition_down){
              iShowBMP(x,y,"pics//pac_d_1.bmp");

            }
          }

          else if(pac.left && maze[row][col-1]==0)
          {
            pac.transition_down = 0;
            pac.transition_up = 0;
            pac.transition_right = 0;
            pac.transition_left = 0;

            iShowBMP(x,y,"pics//pac_l_1.bmp");

            pac.transition_left = 1;

          }
          else if(pac.left && maze[row][col-1])
            if(pac.transition_right){
              iShowBMP(x,y,"pics//pac_r_1.bmp");

            }
            else if(pac.transition_left){
              iShowBMP(x,y,"pics//pac_l_1.bmp");

            }
            else if(pac.transition_up){
              iShowBMP(x,y,"pics//pac_u_1.bmp");

            }
            else if(pac.transition_down){
              iShowBMP(x,y,"pics//pac_d_1.bmp");

            }

        }
        else
        {

            if(pac.transition_up)
            {
                iShowBMP(x,y,"pics//pac_u_1.bmp");

            }
           else  if(pac.transition_down)
            {

                iShowBMP(x,y,"pics//pac_d_1.bmp");


            }
             else if(pac.transition_right)
            {

                iShowBMP(x,y,"pics//pac_r_1.bmp");



            }
            else if(pac.transition_left)
            {

                iShowBMP(x,y,"pics//pac_l_1.bmp");

            }

        }

    }
}
int mazeEmptychecker()
{
    for(int i=0;i<21;i++)
    {
        for(int j=0;j<19;j++)
        {
            if(point[i][j] == 0)
                return 0;

        }
    }
    return 1;


}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {



        if(mx>=426 && mx <= 581 && my<= 515 && my>=496)
        {

            life = 3;

            dx = 2;
            loadMenu = 0;
            enterName = 1;
            enterNamelen = 0;

            gameState = 0;
            pause = 0;



            strcpy(enterName_str,"\0");
            pacReset();
            for(int i=0;i<g_count;i++)
                reset(i);
            score = 0;

            tim = 0;

            fire = 0;
            fire_dir = 0;
            fire_x = 0;
            fire_y = 0;
            fire_row = 0;
            fire_col = 0;
            fire_r = 0;
            fire_l = 0;
            fire_d = 0;
            fire_u = 0;



            for(int i=0;i<21;i++)
            {
                for(int j=0;j<19;j++)
                    point[i][j] = 0;
            }

            for(int i=0;i<g_count;i++)
            {
                g_r_x[i] = 0;
                g_r_y[i] = 0;
                gh_c[i] = 0;
                gh_r[i] = 0;
            }


        }
        if(mx>=420 && mx <= 588 && my<= 443 && my>= 426)
        {




            FILE *fp = NULL;
            fp = fopen("save.txt","r");
            if(fp!=NULL)
                loadMenu = 0;


            fscanf(fp,"%d",&score);

            fscanf(fp,"%d",&x);

            fscanf(fp,"%d",&y);
            fscanf(fp,"%d",&g_count);
            fscanf(fp,"%d",&time_normal);
            fscanf(fp,"%d",&time_rep);



            for(int i=0;i<g_count;i++)
            {
                fscanf(fp,"%d",&g_real_x[i]);
                fscanf(fp,"%d",&g_real_y[i]);
                fscanf(fp,"%d",&gh_r[i]);
                fscanf(fp,"%d",&gh_c[i]);
                fscanf(fp,"%d",&g_move[i].up);
                fscanf(fp,"%d",&g_move[i].down);
                fscanf(fp,"%d",&g_move[i].right);
                fscanf(fp,"%d",&g_move[i].left);
                fscanf(fp,"%d",&g_move[i].transition_up);
                fscanf(fp,"%d",&g_move[i].transition_down);
                fscanf(fp,"%d",&g_move[i].transition_right);
                fscanf(fp,"%d",&g_move[i].transition_left);
                fscanf(fp,"%d",&g_move[i].vel);
                fscanf(fp,"%d",&row);
                fscanf(fp,"%d",&col);
                fscanf(fp,"%d",&dx);
                fscanf(fp,"%d",&pac.up);
                fscanf(fp,"%d",&pac.down);
                fscanf(fp,"%d",&pac.left);
                fscanf(fp,"%d",&pac.right);
                fscanf(fp,"%d",&pac.transition_up);
                fscanf(fp,"%d",&pac.transition_down);
                fscanf(fp,"%d",&pac.transition_left);
                fscanf(fp,"%d",&pac.transition_right);
                fscanf(fp,"%d",&tim);
            }

            for(int i=0;i<21;i++)
            {
                for(int j=0;j<19;j++)
                {
                    fscanf(fp,"%d",&point[i][j]);
                }
            }

            fscanf(fp,"%d",&gameState);
            fscanf(fp,"%d",&pause);
            fscanf(fp,"%d",&fire);
            fscanf(fp,"%d",&fire_dir);
            fscanf(fp,"%d",&f_r_x);
            fscanf(fp,"%d",&f_r_y);
            fscanf(fp,"%d",&fire_x);
            fscanf(fp,"%d",&fire_y);
            fscanf(fp,"%d",&fire_l);
            fscanf(fp,"%d",&fire_r);
            fscanf(fp,"%d",&fire_u);
            fscanf(fp,"%d",&fire_d);
            fscanf(fp,"%d",&fire_row);
            fscanf(fp,"%d",&fire_col);
            fscanf(fp,"%d",&life);



            char ch;
            fscanf(fp,"%c",&ch);
            fscanf(fp,"%[^\n]s",enterName_str);

            fclose(fp);

        }
        if(mx >= 617 && mx<= 833 && my>=392 && my<=437) //back
        {
            loadMenu = 1;

            opt_highcore = 0;
            opt_instruction = 0;

            menuSound = 1;

        }
        if(mx >= 665 && mx<= 743 && my>=293 && my<=310)
        {

            FILE *fp;
            fp = fopen("save.txt","w");

            fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n",score,x,y,g_count,time_normal,time_rep);

            for(int i=0;i<g_count;i++)
            {

                    fprintf(fp,"%d\n",g_real_x[i]);
                    fprintf(fp,"%d\n",g_real_y[i]);
                    fprintf(fp,"%d\n",gh_r[i]);
                    fprintf(fp,"%d\n",gh_c[i]);
                    fprintf(fp,"%d\n",g_move[i].up);
                    fprintf(fp,"%d\n",g_move[i].down);
                    fprintf(fp,"%d\n",g_move[i].right);
                    fprintf(fp,"%d\n",g_move[i].left);
                    fprintf(fp,"%d\n",g_move[i].transition_up);
                    fprintf(fp,"%d\n",g_move[i].transition_down);
                    fprintf(fp,"%d\n",g_move[i].transition_right);
                    fprintf(fp,"%d\n",g_move[i].transition_left);
                    fprintf(fp,"%d\n",g_move[i].vel);
                    fprintf(fp,"%d\n",row);
                    fprintf(fp,"%d\n",col);
                    fprintf(fp,"%d\n",dx);
                    fprintf(fp,"%d\n",pac.up);
                    fprintf(fp,"%d\n",pac.down);
                    fprintf(fp,"%d\n",pac.left);
                    fprintf(fp,"%d\n",pac.right);

                    fprintf(fp,"%d\n",pac.transition_up);
                    fprintf(fp,"%d\n",pac.transition_down);
                    fprintf(fp,"%d\n",pac.transition_left);
                    fprintf(fp,"%d\n",pac.transition_right);
                    fprintf(fp,"%d\n",tim);
            }
            for(int i=0;i<21;i++)
            {
                for(int j=0;j<19;j++)
                {
                    fprintf(fp,"%d\n",point[i][j]);
                }
            }

            fprintf(fp,"%d\n",gameState);
            fprintf(fp,"%d\n",pause);
            fprintf(fp,"%d\n",fire);
            fprintf(fp,"%d\n",fire_dir);
            fprintf(fp,"%d\n",f_r_x);
            fprintf(fp,"%d\n",f_r_y);
            fprintf(fp,"%d\n",fire_x);
            fprintf(fp,"%d\n",fire_y);
            fprintf(fp,"%d\n",fire_l);
            fprintf(fp,"%d\n",fire_r);
            fprintf(fp,"%d\n",fire_u);
            fprintf(fp,"%d\n",fire_d);
            fprintf(fp,"%d\n",fire_row);
            fprintf(fp,"%d\n",fire_col);
            fprintf(fp,"%d\n",life);


            fprintf(fp,"%s\n",enterName_str);

            fclose(fp);


        }
        if(pause)
        {
            if(mx >= 647 && mx<= 761 && my>=180 && my<=201)
            {
                pause = 0;

            }
        }
        else if(pause == 0)
        {

            if(mx >= 660 && mx<= 748 && my>=191 && my<=210)
            {
                pause = 1;

            }


        }
        if(mx >= 423 && mx <= 583 && my>=282 && my<=300)
        {

            loadMenu = 0;
            opt_highcore = 1;




        }
      if(mx >= 770 && mx <= 985 && my>=654 && my<=671 && opt_highcore)
        {

            loadMenu = 1;

            opt_highcore = 0;

            opt_instruction = 0;

            menuSound = 1;



        }
        if(mx >= 770 && mx <= 985 && my>=654 && my<=671 && opt_instruction)
        {

            loadMenu = 1;

            opt_highcore = 0;

            opt_instruction = 0;

            menuSound = 1;



        }
        if(mx >= 409 && mx <= 599 && my>= 352 && my<= 373)
        {

           loadMenu = 0;

           opt_instruction = 1;

        }
        if(mx >= 470 && mx <= 525 && my>= 226 && my<= 243)
        {

           exit(0);

        }


    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {


    }

}


void iKeyboard(unsigned char key)
{
    if(enterName==1)
    {
        if(key=='\r')
        {

            enterName_str[enterNamelen] = '\0';
            gameState = 0;
            enterName = 0;

            menuSound = 0;
            playGameSound = 1;

            if(playGameSound)
            {
                PlaySound("beginning.wav",NULL,SND_ASYNC);
                playGameSound = 0;

                gameOnSound = 1;

            }






        }
        else
        {
            if(key == '\b'){
                    if(enterNamelen > 0)
                    {
                        enterNamelen--;
                    }
                enterName_str[enterNamelen] = '\0';
            }
            else
            {
                enterName_str[enterNamelen] = key;
                enterNamelen++;
            }
        }
    }
    else
    {


        if(key == 'q')
        {
            exit(0);
        }
        if(key == 'w')
        {
                    pac.up = 1;
                    pac.down = 0;
                    pac.right = 0;
                    pac.left = 0;



        }
        if(key == 's')
        {

                    pac.up = 0;
                    pac.down = 1;
                    pac.right = 0;
                    pac.left = 0;




        }
        if(key == 'a')
        {

                pac.up = 0;
                pac.down = 0;
                pac.right = 0;
                pac.left = 1;


        }
        if(key == 'd')
        {

                    pac.up = 0;
                    pac.down = 0;
                    pac.right = 1;
                    pac.left = 0;

        }
        if(key=='k')
        {


        }
        if(key=='p')
        {
                fire = 0;
                fire_dir = 0;
                iPauseTimer(0);
                iPauseTimer(1);
                iPauseTimer(2);
                pause = 1;


        }
        if(key=='r')
        {
                pause = 0;
                iResumeTimer(0);
                iResumeTimer(1);
                iResumeTimer(2);



        }
    }

    //place your codes for other keys here
}
void pacMove()
{
        if(pac.transition_up && maze[row-1][col]==0)
            y += dx;
        if(pac.transition_right && maze[row][col+1] == 0)
            x += dx;
        if(pac.transition_left && maze[row][col-1] == 0)
            x -= dx;
        if(pac.transition_down && maze[row+1][col] == 0)
            y -= dx;



}
void ghostMove()
{

        for(int i=0 ;i<g_count; i++)
        {


            if(g_move[i].transition_up && maze[gh_r[i] - 1][gh_c[i]] == 0)
            {
                g_real_y[i] += g_move[i].vel;
            }
            else if(g_move[i].transition_down && maze[gh_r[i] + 1][gh_c[i]] == 0)
            {
                g_real_y[i] -= g_move[i].vel;
            }
            else if( g_move[i].transition_right && maze[gh_r[i]][gh_c[i] + 1] == 0)
            {
                g_real_x[i] += g_move[i].vel;
            }
            else if( g_move[i].transition_left && maze[gh_r[i]][gh_c[i] - 1] == 0)
            {

                g_real_x[i] -= g_move[i].vel;
            }


        }


}
void time()
{
    tim += 1;
}

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

}

int main()
{

   iSetTimer(10,pacMove);

   iSetTimer(10,ghostMove);

   iSetTimer(1000,time);


   for(int i=0;i<4;i++)
   {
       g_real_x[i] = g_initial_x[i];
       g_real_y[i] = g_initial_y[i];
       g_move[i].vel = 1;
   }


    g_move[0].up = 1;
    g_move[1].right = 1;
    g_move[2].left = 1;
    g_move[3].up = 1;

    iInitialize(screenWidth, screenHeight, "Pacman!");
    return 0;
}
