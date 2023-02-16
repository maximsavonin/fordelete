typedef struct {
   int x;
   int y;
   int width;
   int height;
   const char* text;
   int stage;
} BUTTON;

int control_in_menu(int x, int y);
void menu();
void draw_aboutgame();
void game();
void draw_aboutme();
void draw_sqr(int x, int y, int color);
void draw_all(int x, int y, int kol, int &blink);
void swap(int &selected, int &x, int &y);
bool fall();
bool check_sqrt(int x, int y);
int chop();
void create_map();
bool blink_sqrt(int x, int y);
BUTTON create_button(int x, int y, int width, int height, const char* text, int button_stage);