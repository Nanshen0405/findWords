#ifndef _WINDOWS_H_
#define	_WINDOWS_H_
#endif

//改变控制台窗口大小为width宽，height高
void set_size(int width, int height);

//设置控制台窗口的标题为字符串title
void set_title(char *title);

//移动光标到坐标(x, y)处，即y行x列
void gotoxy(int x, int y); 

//隐藏光标
void hide_cursor(void);

//显示光标
void show_cursor(void);

//设置颜色函数： bcolor背景色，fcolor前景色 
//具体颜色值参见命令行下的color/?命令。
void set_color(int bcolor, int fcolor);

//延时函数，单位毫秒
void delay(int dtime);

//播放wav格式的声音
void play_sound(const char *sndfile);

//清屏
void cls(void);

//获取按键
int getkey(void);
