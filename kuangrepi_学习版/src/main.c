#include <common.h>
struct KID Kid;
struct ITEM item[amount] = {0};
struct BULLET bullet[bamount] = {0};
struct FOOTBALL football = {0};
int main(int argc, char *argv[]) {
    Init();//初始化
    Load();//导入所有素材
    start();//健康游戏提示
    reset();
    while(!Keyboard[SDL_SCANCODE_ESCAPE]){
        switch (choice) {
            case 1:
                menu();
                break;
            case 2:
                game();
                break;
            case 3:
                guide();
                break;
            default:
                break;
        }
    }
    Deinit();//销毁最后没销毁的东西
    Deload();//销毁所有素材
    return 0;
}
//一些处理内容////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Init(){//初始化
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){//反正就初始化一下这两个东西
        SDL_Log("Init failed: %s", SDL_GetError());//初始化失败就报错
        exit(EXIT_FAILURE);
    }
    if(SDL_Init(IMG_INIT_PNG | MIX_INIT_MP3) < 0){//图片和音频初始化
        SDL_Log("Init failed: %s", SDL_GetError());//初始化失败就报错
        exit(EXIT_FAILURE);
    }
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    Window = SDL_CreateWindow("Kuangrepi_run",SDL_WINDOWPOS_CENTERED, //窗口初始化
                              SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
    if(NULL == Window){
        SDL_Log("Window init failed: %s", SDL_GetError());//初始化失败就报错
        exit(EXIT_FAILURE);
    }
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);//渲染初始化
    if(NULL == Renderer){
        SDL_Log("Renderer init failed: %s", SDL_GetError());//初始化失败就报错
        exit(EXIT_FAILURE);
    }
    TTF_Init();//字体初始化
    choice = 1;//选择初始化为菜单
    Keyboard = calloc(SDL_NUM_SCANCODES, sizeof(bool));
    mouse = false;//鼠标状态初始化
}

void Load() {//导入所有素材
    Start_texture = IMG_LoadTexture(Renderer, "./res/img/start.png");
    Menu_background_texture = IMG_LoadTexture(Renderer, "./res/img/menu_background.png");
    Guide_background_texture = IMG_LoadTexture(Renderer, "./res/img/guide_background.png");
    Game_background_texture = IMG_LoadTexture(Renderer, "./res/img/game _background.png");
    Stop_texture = IMG_LoadTexture(Renderer, "./res/img/stop.png");
    Defeat_texture = IMG_LoadTexture(Renderer, "./res/img/defeat.png");
    Font = TTF_OpenFont("./res/font/GenshinDefault.ttf", 48);
    bgm[0] = Mix_LoadMUS("./res/sound/bgm0.mp3");
    bgm[1] = Mix_LoadMUS("./res/sound/bgm1.mp3");
    bgm[2] = Mix_LoadMUS("./res/sound/bgm2.mp3");
    bgm[3] = Mix_LoadMUS("./res/sound/losemusic.mp3");
    chunk[0] = Mix_LoadWAV("./res/sound/coin.mp3");//吃东西的声音
    chunk[1] = Mix_LoadWAV("./res/sound/bonk.mp3");//撞到东西的声音
    chunk[2] = Mix_LoadWAV("./res/sound/blover.mp3");//蹲下的声音
    chunk[3] = Mix_LoadWAV("./res/sound/boing.mp3");//跳跃的声音
    chunk[4] = Mix_LoadWAV("./res/sound/pause.mp3");//暂停的声音
    chunk[5] = Mix_LoadWAV("./res/sound/moneyfalls.mp3");//吃金币的声音
    chunk[6] = Mix_LoadWAV("./res/sound/throw.mp3");//射击的声音
    chunk[7] = Mix_LoadWAV("./res/sound/limbs_pop.mp3");//子弹打中的声音
    chunk[8] = Mix_LoadWAV("./res/sound/gargantuar_thump.mp3");//射门的声音
    chunk[9] = Mix_LoadWAV("./res/sound/cheer.mp3");//射门的声音
    Kid_texture[0] = IMG_LoadTexture(Renderer,"./res/img/kid_1.png");
    Kid_texture[1] = IMG_LoadTexture(Renderer,"./res/img/kid_2.png");
    Kid_texture[2] = IMG_LoadTexture(Renderer,"./res/img/kid_3.png");
    Kid_texture[3] = IMG_LoadTexture(Renderer,"./res/img/kid_4.png");
    Kid_texture[4] = IMG_LoadTexture(Renderer,"./res/img/kid_5.png");
    Kid_texture[5] = IMG_LoadTexture(Renderer,"./res/img/kid_6.png");
    Item_texture[0] = IMG_LoadTexture(Renderer,"./res/img/ProjectilePea.png");
    Item_texture[1] = IMG_LoadTexture(Renderer,"./res/img/coin_gold_dollar.png");
    Item_texture[2] = IMG_LoadTexture(Renderer,"./res/img/Tallnut_body.png");
    Item_texture[3] = IMG_LoadTexture(Renderer,"./res/img/CobCannon_cob.png");
    Item_texture[4] = IMG_LoadTexture(Renderer,"./res/img/Caltrop_body.png");
    Item_texture[5] = IMG_LoadTexture(Renderer,"./res/img/Diamond.png");
    Item_texture[6] = IMG_LoadTexture(Renderer,"./res/img/Projectile_star.png");
    Item_texture[7] = IMG_LoadTexture(Renderer,"./res/img/medicine.png");
    Item_texture[8] = IMG_LoadTexture(Renderer,"./res/img/Wallnut_body.png");
    Item_texture[9] = IMG_LoadTexture(Renderer,"./res/img/Wallnut_cracked1.png");
    Item_texture[10] = IMG_LoadTexture(Renderer,"./res/img/Wallnut_cracked2.png");
    Item_texture[11] = IMG_LoadTexture(Renderer,"./res/img/football.png");
    Item_texture[12] = IMG_LoadTexture(Renderer,"./res/img/door.png");
    HP_texture[1] = IMG_LoadTexture(Renderer,"./res/img/hp1.png");
    HP_texture[2] = IMG_LoadTexture(Renderer,"./res/img/hp2.png");
    HP_texture[3] = IMG_LoadTexture(Renderer,"./res/img/hp3.png");
}

void Deinit(){//销毁最后没销毁的东西
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    free(Keyboard);
    Mix_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();
}

void Deload(){//销毁所有素材
    SDL_DestroyTexture(Start_texture);
    SDL_DestroyTexture(Menu_background_texture);
    SDL_DestroyTexture(Guide_background_texture);
    SDL_DestroyTexture(Game_background_texture);
    SDL_DestroyTexture(Stop_texture);
    SDL_DestroyTexture(Defeat_texture);
    SDL_DestroyTexture(Kid.texture);
    for(int i = 0; i < 6; i++) SDL_DestroyTexture(Kid_texture[i]);
    for(int i = 0; i < 20; i++) SDL_DestroyTexture(Item_texture[i]);
    for(int i = 0; i < 4; i++) SDL_DestroyTexture(HP_texture[i]);
    for(int i = 0; i < amount; i++) SDL_DestroyTexture(item[i].texture);
    for(int i = 0; i < bamount; i++) SDL_DestroyTexture(bullet[i].texture);
    TTF_CloseFont(Font);
    SDL_FreeSurface(Surface_score);
    SDL_FreeSurface(Surface_record);
    SDL_DestroyTexture(Font_texture);
    for(int i = 0; i < 4; i++) Mix_FreeMusic(bgm[i]);
    for(int i = 0; i < 10; i++) Mix_FreeChunk(chunk[i]);
}

void start(){//开始捏
    SDL_RenderCopy(Renderer, Start_texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    int i = 0;
    while(i < 1000 && !Keyboard[SDL_SCANCODE_ESCAPE]){
        while(SDL_PollEvent(&Event)) Do_event(Event);
        SDL_Delay(1);
        i++;
    }
}

void reset(){
    mouse = false;
    Keyboard[SDL_SCANCODE_ESCAPE] = false;
    resetkey();
}

void resetkey(){//重置所有键盘状态
    Keyboard[SDLK_a] = false;
    Keyboard[SDLK_s] = false;
    Keyboard[SDLK_d] = false;
    Keyboard[SDLK_SPACE] = false;
    Keyboard[SDLK_TAB] = false;
    Keyboard[SDLK_w] = false;
    Keyboard[SDLK_e] = false;
}
void Do_event(SDL_Event event) {//记录所有键盘鼠标事件
    switch (event.type) {
        case SDL_QUIT://按退出
            Keyboard[SDL_SCANCODE_ESCAPE] = true;
            break;
        case SDL_KEYUP://这里防止一些奇怪按键导致访问不存在内存
            if(event.key.keysym.sym < SDL_NUM_SCANCODES) Keyboard[event.key.keysym.sym] = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym < SDL_NUM_SCANCODES) Keyboard[event.key.keysym.sym] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse = false;
            break;
        case SDL_MOUSEBUTTONDOWN://鼠标按下（重点获得事件的 x坐标和 y坐标）
            mouse = true;
            break;
        default:
            break;
    }
}
//菜单////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu(){//菜单界面捏
    reset();
    Mix_PlayMusic(bgm[0], -1);
    Draw_menu();
    while(SDL_WaitEvent(&Event) && !Keyboard[SDL_SCANCODE_ESCAPE]){
        Do_event(Event);
        if(mouse == true){
            if(Event.button.y < 520 && Event.button.y > 450 &&
               Event.button.x < 800 && Event.button.x > 400){//按了进入游戏
                choice = 2;
                break;
            }
            else if(Event.button.y < 670 && Event.button.y > 600 &&
                    Event.button.x < 800 && Event.button.x > 400){//按了进入图鉴
                choice = 3;
                break;
            }
        }
    }
}

void Draw_menu(){
    //渲染背景
    SDL_RenderCopy(Renderer, Menu_background_texture, NULL, NULL);
    //渲染字
    char word[40];
    FILE *fp = fopen("./res/record.txt", "r");
    fscanf(fp, "%d", &record);
    sprintf_s(word, 30, "record: %d", record);
    Surface_record = TTF_RenderText_Blended(Font,word,Color);
    Font_texture = SDL_CreateTextureFromSurface(Renderer, Surface_record);
    SDL_Rect rect_record = {.x = 40, .y = 720};
    SDL_QueryTexture(Font_texture, NULL, NULL, &rect_record.w, &rect_record.h);
    SDL_RenderCopy(Renderer, Font_texture, NULL, &rect_record);
    //呈现
    SDL_RenderPresent(Renderer);
    SDL_FreeSurface(Surface_record);
    SDL_DestroyTexture(Font_texture);
    fclose(fp);
}
//游戏////////////////////////////////////////////////////////////////////////////////////////////////////////////

void game(){//游戏捏
    reset();
    kid_init();
    item_init();
    bool flag = true;
    Mix_PlayMusic(bgm[2], -1);
    Uint64 start, end;
    while(!Keyboard[SDL_SCANCODE_ESCAPE] && flag){
        start = SDL_GetTicks64();
        game_input();
        flag = pause();
        kid_control();
        judge();
        for(int i = 0; i < 6; i++) {
            Draw_game();
        }
        create();
        if(Kid.hp < 1) flag = defeat();
        resetkey();
        end = SDL_GetTicks64();
        fps_control(start, end);
    }
}

void Draw_game(){//渲染游戏
    SDL_RenderClear(Renderer);//清除渲染器
    SDL_RenderCopy(Renderer, Game_background_texture, NULL, &Background_rect);//先把背景画上去
    if(Background_rect.x >= -Width + 2) Background_rect.x --;
    else Background_rect.x = 0;
    //画kid
    Uint32 tmp = SDL_GetTicks() % (30 * ANIMATION_INTERVAL);
    if (tmp < 5 * ANIMATION_INTERVAL) Kid.texture = Kid_texture[0];
    else if (tmp < 10 * ANIMATION_INTERVAL) Kid.texture = Kid_texture[1];
    else if (tmp < 15 * ANIMATION_INTERVAL) Kid.texture = Kid_texture[2];
    else if (tmp < 20 * ANIMATION_INTERVAL) Kid.texture = Kid_texture[3];
    else if (tmp < 25 * ANIMATION_INTERVAL) Kid.texture = Kid_texture[4];
    else Kid.texture = Kid_texture[5];
    //画持球
    if(Kid.football){
            football.rect.x = Kid.rect.x + 3 * Kid.rect.w / 4;
            football.rect.y = Kid.rect.y + Kid.rect.h - football.rect.h;
        football.rect.w = football.rect.h = 40;
        SDL_RenderCopyEx(Renderer, Item_texture[11], NULL, &football.rect, 3 * tmp / 5, NULL, SDL_FLIP_NONE);
    }
    //画item
    for(int i = 0; i < amount; i++){
        if(item[i].exit){
            item[i].rect.x --;
            SDL_RenderCopy(Renderer, item[i].texture, NULL, &item[i].rect);
            if(item[i].rect.x < -100){
                item[i].exit = false;
            }
        }
    }
    //画子弹
    for(int i = 0; i < bamount; i++){
        if(bullet[i].exit){
            bullet[i].rect.x += 4;
            SDL_RenderCopy(Renderer, bullet[i].texture, NULL, &bullet[i].rect);
            if(bullet[i].rect.x > Width + 100){
                bullet[i].exit = false;
            }
        }
    }
    //画射出的足球
    if(football.exit){
        football.rect.x += 2;
        SDL_RenderCopyEx(Renderer, Item_texture[11], NULL, &football.rect, 3 * tmp / 5, NULL, SDL_FLIP_NONE);
        if(football.rect.x > Width + 100) football.exit = false;
    }
    //渲染字
    char word[40];
    sprintf_s(word, 30, "score: %d", Kid.score);
    Surface_score = TTF_RenderText_Blended(Font,word,Color);
    Font_texture = SDL_CreateTextureFromSurface(Renderer, Surface_score);
    static SDL_Rect rect_score = {.x = 50, .y = 50};
    SDL_QueryTexture(Font_texture, NULL, NULL, &rect_score.w, &rect_score.h);
    //画血量
    static SDL_Rect rect_hp = {.x = 1000, .y = 60, .w = 180, . h = 40};
    SDL_RenderCopy(Renderer, HP_texture[Kid.hp], NULL, &rect_hp);
    SDL_RenderCopy(Renderer, Font_texture, NULL, &rect_score);
    SDL_RenderCopy(Renderer, Kid.texture, NULL, &Kid.rect);
    //呈现
    SDL_RenderPresent(Renderer);
    SDL_FreeSurface(Surface_score);
    SDL_DestroyTexture(Font_texture);
}

void game_input(){//游戏输入
    while (SDL_PollEvent(&Event)){
        Do_event(Event);
    }
}

void fps_control(Uint64 a, Uint64 b){//控制帧率
    int len = fps_len - Kid.score / 30;
    if(len < 8) len = 8;
    if(b - a > len) SDL_Delay(1);//防止出现负数，导致游戏崩溃
    else SDL_Delay(len - (b - a));
}

void kid_init(){//对kid进行初始化
    Kid.hp = 3;
    Kid.line = 2;
    Kid.state = 1;
    Kid.rect.x = POSITIONX;
    Kid.rect.y = LINE2;
    Kid.rect.w = kidw;
    Kid.rect.h = kidh;
    Kid.clock = 0;
    Kid.score = 0;
    Kid.unbeatable = false;
    Kid.shoot = false;
    Kid.football = false;
}

void item_init(){//对item进行初始化
    control = fre;
    for (int i = 0; i < amount; i++) {
        item[i].exit = false;
        item[i].type = 0;
        item[i].texture = NULL;
        item[i].touch = false;
    }
    Background_rect.x = Background_rect.y = 0;
    Background_rect.w = 2 * Width;
    Background_rect.h = Height;
    for (int i = 0; i < bamount; i++) {
        bullet[i].exit = false;
        bullet[i].texture = Item_texture[0];
    }
}

void create(){//创造除了kid的其他东西
    static int i = 0;//储存区下标
    static int obstacle = 0;//防止出现过不了的情况
    static bool lin[3] = {0};
    srand((unsigned int)(SDL_GetTicks() * time(NULL) + Kid.score));
    int type = rand() % 100;
    int line = rand() % 3 + 1;
    if (control <= 3){//控制可生成东西的时间间隔
        if(!lin[line - 1]) lin[line - 1] = true;//防止生成到同一行
        else{
            if(!lin[0]) {
                line = 1;
                lin[0] = true;
            }
            else if(!lin[1]) {
                line = 2;
                lin[1] = true;
            }
            else {
                line = 3;
                lin[2] = true;
            }
        }
        if(type < 35){//生成金币
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[1];
            item[i].type = 1;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 40;
            item[i].rect.x = Width + 30;
            item[i].rect.w = 40;
            item[i].rect.h = 40;
        }
        else if(type < 55 && obstacle < 2){//高坚果
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[2];
            item[i].type = 2;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) - 50;
            item[i].rect.x = Width;
            item[i].rect.w = 100;
            item[i].rect.h = 150;
            obstacle++;
        }
        else if(type < 65 && obstacle < 2){//玉米加农炮
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[3];
            item[i].type = 3;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) - 50;
            item[i].rect.x = Width;
            item[i].rect.w = 120;
            item[i].rect.h = 60;
            obstacle++;
        }
        else if(type < 75 && obstacle < 2){//地刺
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[4];
            item[i].type = 4;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 60;
            item[i].rect.x = Width;
            item[i].rect.w = 100;
            item[i].rect.h = 30;
            obstacle++;
        }
        else if(type < 77){//钻石
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[5];
            item[i].type = 5;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 30;
            item[i].rect.x = Width + 20;
            item[i].rect.w = 60;
            item[i].rect.h = 50;
        }
        else if(type < 78){//无敌星
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[6];
            item[i].type = 6;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 30;
            item[i].rect.x = Width + 20;
            item[i].rect.w = 60;
            item[i].rect.h = 60;
        }
        else if(type < 79){//生成血瓶
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[7];
            item[i].type = 7;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 20;
            item[i].rect.x = Width + 30;
            item[i].rect.w = 80;
            item[i].rect.h = 80;
        }
        else if(type < 85 && obstacle < 2){//生成坚果
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[8];
            item[i].type = 8;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) - 30;
            item[i].rect.x = Width;
            item[i].rect.w = 120;
            item[i].rect.h = 120;
            obstacle++;
        }
        else if(type < 86 && !Kid.football){//生成足球
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[11];
            item[i].type = 11;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) + 30;
            item[i].rect.x = Width + 30;
            item[i].rect.w = 50;
            item[i].rect.h = 50;
        }
        else if(type < 90 && obstacle < 2 && Kid.football){//生成足球门
            item[i].exit = true;
            item[i].touch = false;
            item[i].texture = Item_texture[12];
            item[i].type = 12;
            item[i].line = line;
            item[i].rect.y = LINE0 + line * (LINE3 - LINE2) - 60;
            item[i].rect.x = Width;
            item[i].rect.w = 120;
            item[i].rect.h = 160;
            obstacle++;
        }
        else//什么都没有
            item[i].type = 0;
        if(i == amount - 1) i = 0;
        else i++;
    }
    control++;
    if(control == fre * 4.5) {//控制生成间距
        control = 1;
        lin[0] = lin[1] = lin[2] = false;
        obstacle = 0;
    }
    //生成子弹
    static int tmp = 0;
    tmp++;
    static int j = 0;
    if(Kid.shoot && tmp > 1.5 * fre){
        Mix_PlayChannel(-1, chunk[6], 0);
        bullet[j].exit = true;
        bullet[j].rect.x = POSITIONX + Kid.rect.w;
        bullet[j].rect.y = Kid.rect.y + Kid.rect.h / 4;
        bullet[j].rect.w = bullet[j].rect.h = 40;
        Kid.score--;
        tmp = 0;
        Kid.shoot = false;
        if(j == bamount - 1) j = 0;
        else j++;
    }
}

void judge() {//进行各种判定
    static int unbeatable = 1;
    for (int i = 0; i < amount; i++) {
        if (item[i].exit) {
            switch (item[i].type) {
                case 1://金币
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 10 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        Kid.score++;
                        Mix_PlayChannel(-1, chunk[5], 0);
                    }
                    break;
                case 2://高坚果
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 2 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable) Kid.hp--;
                        Mix_PlayChannel(-1, chunk[1], 0);
                    }
                    break;
                case 3://玉米加农炮
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 40 > item[i].rect.x && Kid.line == item[i].line) {
                        if (Kid.state == 1 || Kid.state == 2 || Kid.state == 4 || Kid.state == 5) {
                            item[i].exit = false;
                            if(!Kid.unbeatable) Kid.hp--;
                            Mix_PlayChannel(-1, chunk[1], 0);
                        } else if (Kid.state == 3 && !item[i].touch) {
                            Kid.score += 2;
                            item[i].touch = true;
                        }
                    }
                    break;
                case 4://地刺
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 40 > item[i].rect.x && Kid.line == item[i].line) {
                        if (Kid.state == 1 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5) {
                            item[i].exit = false;
                            if(!Kid.unbeatable) Kid.hp--;
                            Mix_PlayChannel(-1, chunk[1], 0);
                        } else if (Kid.state == 2 && !item[i].touch) {
                            Kid.score += 2;
                            item[i].touch = true;
                        }
                    }
                    break;
                case 5://钻石
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 10> item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        Kid.score += 2;
                        Mix_PlayChannel(-1, chunk[0], 0);
                    }
                    break;
                case 6://无敌星
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 10 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable || unbeatable > 50 * fre){
                            Kid.rect.w += 60;
                            Kid.rect.h += 60;
                            Kid.rect.y -= 40;
                        }
                        unbeatable = 1;
                        Kid.unbeatable = true;
                        Mix_PlayChannel(-1, chunk[0], 0);
                    }
                    break;
                case 7://血瓶
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 2 && Kid.rect.x + Kid.rect.w - 10 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(Kid.hp < 3) Kid.hp++;
                        Mix_PlayChannel(-1, chunk[0], 0);
                    }
                    break;
                case 8://坚果
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 2 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable) Kid.hp--;
                        Mix_PlayChannel(-1, chunk[1], 0);
                    }
                    break;
                case 9://坚果
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 2 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable) Kid.hp--;
                        Mix_PlayChannel(-1, chunk[1], 0);
                    }
                    break;
                case 10://坚果
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 2 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable) Kid.hp--;
                        Mix_PlayChannel(-1, chunk[1], 0);
                    }
                    break;
                case 11://足球
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        Kid.football = true;
                    }
                    break;
                case 12://足球门
                    if (Kid.rect.x < item[i].rect.x + item[i].rect.w / 3 && Kid.rect.x + Kid.rect.w - 20 > item[i].rect.x && Kid.line == item[i].line
                        && (Kid.state == 1 || Kid.state == 2 || Kid.state == 3 || Kid.state == 4 || Kid.state == 5)) {
                        item[i].exit = false;
                        if(!Kid.unbeatable) Kid.hp--;
                        Mix_PlayChannel(-1, chunk[1], 0);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if(Kid.unbeatable){//控制无敌时间
        unbeatable ++;
        if(unbeatable == 50 * fre){
            Kid.rect.w -= 60;
            Kid.rect.h -= 60;
            Kid.rect.y += 40;
        }
        if(unbeatable == 55 * fre){
            Kid.unbeatable = false;
            unbeatable = 1;
        }
    }
    for (int i = 0; i < bamount; i++) {
        if(bullet[i].exit){
            for(int j = 0; j < amount; j++){
                if(item[j].exit){
                    if(item[j].type == 2 || item[j].type == 3 || item[j].type == 4)
                    {
                        if (item[j].rect.x < bullet[i].rect.x && item[j].rect.x + item[j].rect.w > bullet[i].rect.x
                            && item[j].rect.y < bullet[i].rect.y && item[j].rect.y + item[j].rect.h > bullet[i].rect.y){
                            bullet[i].exit = false;
                            Mix_PlayChannel(-1, chunk[7], 0);
                        }
                    }
                    else if(item[j].type == 8 || item[j].type == 9)
                    {
                        if (item[j].rect.x < bullet[i].rect.x && item[j].rect.x + item[j].rect.w > bullet[i].rect.x
                            && item[j].rect.y < bullet[i].rect.y && item[j].rect.y + item[j].rect.h > bullet[i].rect.y){
                            bullet[i].exit = false;
                            item[j].texture = Item_texture[++item[j].type];
                            Mix_PlayChannel(-1, chunk[7], 0);
                        }
                    }
                    else if(item[j].type == 10)
                    {
                        if (item[j].rect.x < bullet[i].rect.x && item[j].rect.x + item[j].rect.w > bullet[i].rect.x
                            && item[j].rect.y < bullet[i].rect.y && item[j].rect.y + item[j].rect.h > bullet[i].rect.y){
                            bullet[i].exit = false;
                            item[j].exit = false;
                            Kid.score += 6;
                            Mix_PlayChannel(-1, chunk[7], 0);
                        }
                    }
                }
            }
        }
    }
    if(football.exit){
        for(int j = 0; j < amount; j++){
            if(item[j].exit){
                if(item[j].type == 2 || item[j].type == 3 || item[j].type == 4 || item[j].type == 8 || item[j].type == 9 || item[j].type == 10)
                {
                    if (item[j].rect.x < football.rect.x && item[j].rect.x + item[j].rect.w > football.rect.x
                        && item[j].rect.y < football.rect.y && item[j].rect.y + item[j].rect.h > football.rect.y){
                        football.exit = false;
                        Mix_PlayChannel(-1, chunk[7], 0);
                    }
                }
                else if(item[j].type == 12)
                {
                    if (item[j].rect.x < football.rect.x && item[j].rect.x + item[j].rect.w > football.rect.x
                        && item[j].rect.y < football.rect.y && item[j].rect.y + item[j].rect.h > football.rect.y){
                        football.exit = false;
                        Kid.score += 20;
                        Mix_PlayChannel(-1, chunk[9], 0);
                    }
                }
            }
        }
    }
}

void kid_control(){//对kid进行操作；
    if(input == true){//控制操作频率
        Kid.clock++;
        kid_move();
        if(Kid.clock == fre && Kid.state != 2 && Kid.state != 3) {
            Kid.clock = 0;
            input = false;
            Kid.state = 1;
        }
        if(Kid.clock == 4 * fre){
            Kid.clock = 0;
            input = false;
            Kid.state = 1;
        }
    }
    if(input == false){
        if(Keyboard[SDLK_a]){//向上
            input = true;
            if(Kid.line != 1) Kid.state = 4;
        }
        else if(Keyboard[SDLK_d]){//向下
            input = true;
            if(Kid.line != 3) Kid.state = 5;
        }
        else if(Keyboard[SDLK_SPACE]){
            input = true;
            Kid.state = 2;
            Mix_PlayChannel(-1, chunk[3], 0);
        }
        else if(Keyboard[SDLK_s]){//蹲下
            input = true;
            Kid.state = 3;
            Mix_PlayChannel(-1, chunk[2], 0);
        }
    }
    if(Keyboard[SDLK_w]) {//射击
        Kid.shoot = true;
    }
    if(Keyboard[SDLK_e] && Kid.football) {//射击
        football.exit = true;
        Kid.football = false;
        Mix_PlayChannel(-1, chunk[8], 0);
    }
}

void kid_move(){//运算kid的运动
    if(Kid.state == 4){//向上移动
        Kid.rect.y -= speed;
        if(Kid.clock == fre)
            Kid.line--;
    }
    else if(Kid.state == 5){//向下移动
        Kid.rect.y += speed;
        if(Kid.clock == fre)
            Kid.line++;
    }
    else if(Kid.state == 2){//跳跃
        Kid.rect.y -= (4 * fre - 2 * Kid.clock + 1) / 3;
    }
    else if(Kid.state == 3){//蹲下
        if(Kid.clock <= 3){
            Kid.rect.h -= kidh / 5;
            Kid.rect.w -= kidw / 5;
            Kid.rect.y += kidh / 5;
            Kid.rect.x += kidw / 10;
        }
        if(Kid.clock >= 4 * fre - 2){
            Kid.rect.h += kidh / 5;
            Kid.rect.w += kidh / 5;
            Kid.rect.y -= kidh / 5;
            Kid.rect.x -= kidw / 10;
        }
    }

}

bool pause() {//暂停界面
    if (Keyboard[SDLK_TAB]) {
        Mix_PlayChannel(-1, chunk[4], 0);
        reset();
        SDL_RenderCopy(Renderer, Stop_texture, NULL, NULL);
        SDL_RenderPresent(Renderer);
        while (SDL_WaitEvent(&Event) && !Keyboard[SDL_SCANCODE_ESCAPE]) {
            Do_event(Event);
            if (mouse == true) {
                if (Event.button.y < 520 && Event.button.y > 360 &&
                    Event.button.x < 470 && Event.button.x > 310) {//按了继续游戏
                    return true;
                }
                else if (Event.button.y < 520 && Event.button.y > 360 &&
                           Event.button.x < 720 && Event.button.x > 570) {//按了重新开始
                    choice = 2;
                    return false;
                }
                else if (Event.button.y < 520 && Event.button.y > 360 &&
                         Event.button.x < 975 && Event.button.x > 820) {//按了回到主菜单
                    choice = 1;
                    return false;
                }
            }
        }
    }
    return true;
}

bool defeat(){//失败界面
    Mix_PlayMusic(bgm[3], 0);
    reset();
    SDL_RenderCopy(Renderer, Defeat_texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    //记录读入
    FILE *fp = fopen("./res/record.txt", "w");
    if(Kid.score > record) fprintf(fp, "%d", Kid.score);
    else fprintf(fp, "%d", record);
    fclose(fp);
    while (SDL_WaitEvent(&Event) && !Keyboard[SDL_SCANCODE_ESCAPE]) {
        Do_event(Event);
        if (mouse == true) {
            if (Event.button.y < 585 && Event.button.y > 480 &&
                Event.button.x < 855 && Event.button.x > 430) {//按了重新开始
                choice = 2;
                return false;
            } else if (Event.button.y < 745 && Event.button.y > 640 &&
                       Event.button.x < 855 && Event.button.x > 430) {//按了回到主菜单
                choice = 1;
                return false;
            }
        }
    }
    return true;
}
//图鉴////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guide() {
    reset();
    bool flag = true;
    Mix_PlayMusic(bgm[1], -1);
    Draw_guide();
    while (SDL_WaitEvent(&Event) && !Keyboard[SDL_SCANCODE_ESCAPE] && flag) {
        Do_event(Event);
        if (mouse == true) {
            if (Event.button.y < 775 && Event.button.y > 740 &&
                       Event.button.x < 290 && Event.button.x > 40) {//按了进入图鉴
                flag = false;
                choice = 1;
            }
        }
    }
}

void Draw_guide(){
    SDL_RenderCopy(Renderer, Guide_background_texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
}