//
// Created by 谷羽 on 2024/1/8.
//

#ifndef KUANGREPI_RUN_COMMON_H
#define KUANGREPI_RUN_COMMON_H
//标准库
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//SDL库
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
//宏
#define Width 1280
#define Height 800
#define fps 60
#define fps_len (1000 / fps)
#define LINE0 60
#define LINE1 230
#define LINE2 400
#define LINE3 570
#define POSITIONX 70
#define ANIMATION_INTERVAL 20
#define kidw 100
#define kidh 100
#define fre 10//可操作频率
#define speed ((LINE2 - LINE1) / fre)
#define amount 21//item数量上限
#define bamount 5//bullet数量上限
//函数原型
static void Init();//初始化
void Load();//导入所有素材
void Deload();//销毁所有素材
void Deinit();//销毁最后没销毁的东西
void reset();//重置所有键鼠状态
void resetkey();//重置所有键盘状态
void start();//开始捏
void menu();//菜单界面捏
void Do_event(SDL_Event);//记录所有键盘鼠标事件
void Draw_menu();//渲染菜单
void Draw_guide();//渲染图鉴
void Draw_game();//渲染游戏
void game();//游戏捏
void guide();//图鉴捏
void game_input();//游戏输入
void fps_control(Uint64 a, Uint64 b);//控制帧率
void kid_init();//对kid进行初始化
void item_init();//对item进行初始化
void create();//创造除了kid的其他东西
void judge();//进行各种判定
void kid_control();//对kid进行操作；
void kid_move();//运算kid的运动
bool pause();//暂停界面
bool defeat();//失败界面
//全局变量
static SDL_Window *Window = NULL;
static SDL_Renderer *Renderer = NULL;
static SDL_Event Event;
static bool *Keyboard;//记录键盘状态
static bool mouse;//记录鼠标状态，true为按下了
static bool input = false;//判断是否已经输入
static int control;//控制item生成频率
static int choice;//记录下面要进行什么页面： 1：菜单； 2：游戏； 3： 图鉴；
static int record;//得分记录
static SDL_Rect Background_rect;
//以下一堆东西与字体有关；
static TTF_Font *Font;
static SDL_Color Color = {0xff, 0xff, 0xff, 0xff};
static SDL_Surface *Surface_score;
static SDL_Surface *Surface_record;
static SDL_Texture *Font_texture;
//以下是一些结构体
struct KID{
    SDL_Texture *texture;//kid的图片
    int hp;//kid的血量
    int line;//kid在第几行
    int state;//kid的状态（1：正常； 2： 跳跃； 3： 蹲下；4: 向上； 5：向下）
    bool shoot;//射击了么
    bool football;//是否持球
    bool unbeatable;//kid的特殊状态·(0: 无特殊状态； 1： 无敌；)
    SDL_Rect rect;//x,y坐标以及高度与宽度
    int clock;//控制游戏操作频率
    int score;//游戏得分
};
struct ITEM{
    bool exit;//是否存在
    bool touch;//是否触碰过
    int type;//我是谁(0:啥也不是；1: 金币; 2: 高坚果； 3:玉米加农炮；4：地刺； 5； 钻石）
    SDL_Texture *texture;//图片
    int line;
    SDL_Rect rect;//x,y坐标以及高度与宽度
};
struct BULLET{
    bool exit;//是否存在
    SDL_Texture *texture;//图片
    SDL_Rect rect;//x,y坐标以及高度与宽度
};
struct FOOTBALL{
    bool exit;//是否存在
    SDL_Rect rect;//x,y坐标以及高度与宽度
};
//以下一堆东西与图片有关
static SDL_Texture *Start_texture;
static SDL_Texture *Menu_background_texture;
static SDL_Texture *Guide_background_texture;
static SDL_Texture *Game_background_texture;
static SDL_Texture *Stop_texture;
static SDL_Texture *Defeat_texture;
static SDL_Texture *Kid_texture[6];
static SDL_Texture *Item_texture[20];
static SDL_Texture *HP_texture[4];
//以下一堆东西与音频有关
static Mix_Music *bgm[4];
static Mix_Chunk *chunk[10];

#endif //KUANGREPI_RUN_COMMON_H
