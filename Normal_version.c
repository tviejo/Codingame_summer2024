#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//version basique top 500 silver le 17/06

struct Joueur {
  char gpu[65];
  int reg_0;
  int reg_1;
  int reg_2;
  int reg_3;
  int reg_4;
  int reg_5;
  int reg_6;
  int move;
  int gold;
  int silver;
  int bronze;
} T_Joueur;

struct Result {
  int RIGHT;
  int LEFT;
  int UP;
  int DOWN;
  int priority;
  int nb_tour;
} T_Result;

#define MAX_MOVES 5

void transform100(int *a, int *b, int *c, int *d) {
    int min_val = *a, max_val = *a;
    int range;

    if (*b < min_val) min_val = *b;
    if (*c < min_val) min_val = *c;
    if (*d < min_val) min_val = *d;

    if (*b > max_val) max_val = *b;
    if (*c > max_val) max_val = *c;
    if (*d > max_val) max_val = *d;

    if (abs(max_val) >= abs(min_val))
    {
        range = abs(max_val);
    }
    else
    {
        range = abs(min_val);
    }

    if (max_val == 0) {
        *a = 0;
        *b = 0;
        *c = 0;
        *d = 0;
        return;
    }


    *a = *a * 100 / range;
    *b = *b * 100 / range;
    *c = *c * 100 / range;
    *d = *d * 100 / range;
    
}

struct Result Hurdle_Race(int player_id, int nb_game, struct Joueur *game) {
  struct Result result;
  result.RIGHT = 0;
  result.LEFT = 0;
  result.DOWN = 0;
  result.UP = 0;
  int stone;
  int reg0;
  int reg1;
  int reg2;


//PARSING


  if (player_id == 0) {
    reg0 = game->reg_0;
    reg1 = game->reg_1;
    reg2 = game->reg_2;
    stone = game->reg_3;
  }
  if (player_id == 1) {
    reg0 = game->reg_1;
    reg1 = game->reg_2;
    reg2 = game->reg_0;
    stone = game->reg_4;
  }
  if (player_id == 2) {
    reg0 = game->reg_2;
    reg1 = game->reg_0;
    reg2 = game->reg_1;
    stone = game->reg_5;
  }


// CHOICE



    if (game->gpu[reg0 + 1] == '.' && game->gpu[reg0 + 2] == '.' &&
        game->gpu[reg0 + 3] == '.')
      result.RIGHT = 3;
    else
      result.RIGHT = -4;

    if (game->gpu[reg0 + 1] == '.' && game->gpu[reg0 + 2] == '.')
      result.DOWN = 2;
    else
      result.DOWN = -4;

    if (game->gpu[reg0 + 1] == '.')
      result.LEFT = 1;
    else
      result.LEFT = -4;

    if ((game->gpu[reg0 + 1] == '#' || game->gpu[reg0 + 1] == '.') && game->gpu[reg0 + 2] == '.')
      result.UP = 2;
    else
      result.UP = -4;


  // PRIORITY


  if (reg0 + 2 < reg1 && reg0 + 2 < reg2)
    result.priority = 1;
  else if (reg0 > reg1 && reg0 > reg2)
    result.priority = 5;
  else if (reg0 < reg1 || reg0 < reg2)
    result.priority = 20;
  else
    result.priority = 15;



  if (stone > 0 || (strcmp(game->gpu, "GAME_OVER") == 0))
  {
    result.priority = 0;
  }
  if (strcmp(game->gpu, "GAME_OVER") == 0)
  {
    if (reg0 >= reg2 && reg0 >= reg1)
      game->gold ++;
    else if (reg0 >= reg2 || reg0 >= reg1)
      game->silver++;
    else
      game->bronze++;
  }
  transform100(&result.UP, &result.DOWN, &result.LEFT, &result.RIGHT);
  return (result);
}

struct Result Diving(int player_id, int nb_game, struct Joueur *game, int nbtour ){
  struct Result result;
  result.RIGHT = 0;
  result.LEFT = 0;
  result.DOWN = 0;
  result.UP = 0;
  result.priority = 2;
  int reg0;
  int reg1;
  int reg2;
  int combo;


// PARSING


  if (player_id == 0) {
    reg0 = game->reg_0;
    reg1 = game->reg_1;
    reg2 = game->reg_2;
    combo = game->reg_3;
  }
  if (player_id == 1) {
    reg0 = game->reg_1;
    reg1 = game->reg_2;
    reg2 = game->reg_0;
    combo = game->reg_4;
  }
  if (player_id == 2) {
    reg0 = game->reg_2;
    reg1 = game->reg_0;
    reg2 = game->reg_1;
    combo = game->reg_5;
  }


  // CHOICE


  if (game->gpu[0] == 'R')
  {
    result.RIGHT = 100;
    result.DOWN = -50;
    result.LEFT = -50;
    result.UP = -50;
  }
  else if (game->gpu[0] == 'D')
  {
    result.RIGHT = -50;
    result.DOWN = 100;
    result.LEFT = -50;
    result.UP = -50;
  }
  else if (game->gpu[0] == 'L')
  {
    result.RIGHT = -50;
    result.DOWN = -50;
    result.LEFT = 100;
    result.UP = -50;
  }
  else if (game->gpu[0] == 'U')
  {
    result.RIGHT = -50;
    result.DOWN = -50;
    result.LEFT = -50;
    result.UP = 100;
  }
  else
  {
    result.RIGHT = -50;
    result.DOWN = -50;
    result.LEFT = -50;
    result.UP = -50;
  }


// PRIORITY

  if (reg0 > reg1 && reg0 > reg2)
    result.priority = 5;
  if (reg0 < reg1 || reg0 < reg2)
    result.priority = 20;
  if (reg0 + 3 < reg1 && reg0 + 3 < reg2)
      result.priority = 1;
  if (combo > 1 && combo < 15)
  {
    result.priority += 5;
  }
  result.priority += 15 - nbtour;
  if (reg0 > 40)
      result.priority = 0;
  if (strcmp(game->gpu, "GAME_OVER") == 0)
  {
    result.priority = 0;
    if (reg0 >= reg2 && reg0 >= reg1)
      game->gold ++;
    else if (reg0 >= reg2 || reg0 >= reg1)
      game->silver++;
    else
      game->bronze++;
  }
  transform100(&result.UP, &result.DOWN, &result.LEFT, &result.RIGHT);
  return (result);
}

double distance(int x, int y)
{
    return (sqrt(x * x + y * y));
}

struct Result Skate(int player_id, int nb_game, struct Joueur *game) {
  struct Result result;
  result.RIGHT = 0;
  result.LEFT = 0;
  result.DOWN = 0;
  result.UP = 0;
  int stone;
  int reg0;
  int reg1;
  int reg2;


//PARSING


  if (player_id == 0) {
    reg0 = game->reg_0;
    reg1 = game->reg_1;
    reg2 = game->reg_2;
    stone = game->reg_3;
  }
  if (player_id == 1) {
    reg0 = game->reg_1;
    reg1 = game->reg_2;
    reg2 = game->reg_0;
    stone = game->reg_4;
  }
  if (player_id == 2) {
    reg0 = game->reg_2;
    reg1 = game->reg_0;
    reg2 = game->reg_1;
    stone = game->reg_5;
  }


// CHOICE


  if (stone >= 0)
  {
    if (stone > 3)
    {
     if (game->gpu[0] == 'U')
        result.UP = 100;
     if (game->gpu[0] == 'D')
        result.DOWN = 100;
     if (game->gpu[0] == 'L')
        result.LEFT = 100;
     if (game->gpu[0] == 'R')
        result.RIGHT = 100;

     if (game->gpu[1] == 'U')
        result.UP = 50;
     if (game->gpu[1] == 'D')
        result.DOWN = 50;
     if (game->gpu[1] == 'L')
        result.LEFT = 50;
     if (game->gpu[1] == 'R')
        result.RIGHT = 50;

     if (game->gpu[2] == 'U')
        result.UP = -100;
     if (game->gpu[2] == 'D')
        result.DOWN = -100;
     if (game->gpu[2] == 'L')
        result.LEFT = -100;
     if (game->gpu[2] == 'R')
        result.RIGHT = -100;

     if (game->gpu[3] == 'U')
        result.UP = -100;
     if (game->gpu[3] == 'D')
        result.DOWN = -100;
     if (game->gpu[3] == 'L')
        result.LEFT = -100;
     if (game->gpu[3] == 'R')
        result.RIGHT = -100;
    }
    else if (stone < 2)
    {
     if (game->gpu[0] == 'U')
        result.UP = 0;
     if (game->gpu[0] == 'D')
        result.DOWN = 0;
     if (game->gpu[0] == 'L')
        result.LEFT = 0;
     if (game->gpu[0] == 'R')
        result.RIGHT = 0;

     if (game->gpu[1] == 'U')
        result.UP = 100;
     if (game->gpu[1] == 'D')
        result.DOWN = 100;
     if (game->gpu[1] == 'L')
        result.LEFT = 100;
     if (game->gpu[1] == 'R')
        result.RIGHT = 100;

     if (game->gpu[2] == 'U')
        result.UP = 50;
     if (game->gpu[2] == 'D')
        result.DOWN = 50;
     if (game->gpu[2] == 'L')
        result.LEFT = 50;
     if (game->gpu[2] == 'R')
        result.RIGHT = 50;

     if (game->gpu[3] == 'U')
        result.UP = 100;
     if (game->gpu[3] == 'D')
        result.DOWN = 100;
     if (game->gpu[3] == 'L')
        result.LEFT = 100;
     if (game->gpu[3] == 'R')
        result.RIGHT = 100;
    }
    else
    {
      if (game->gpu[0] == 'U')
        result.UP = 0;
     if (game->gpu[0] == 'D')
        result.DOWN = 0;
     if (game->gpu[0] == 'L')
        result.LEFT = 0;
     if (game->gpu[0] == 'R')
        result.RIGHT = 0;

     if (game->gpu[1] == 'U')
        result.UP = 100;
     if (game->gpu[1] == 'D')
        result.DOWN = 100;
     if (game->gpu[1] == 'L')
        result.LEFT = 100;
     if (game->gpu[1] == 'R')
        result.RIGHT = 100;

     if (game->gpu[2] == 'U')
        result.UP = 50;
     if (game->gpu[2] == 'D')
        result.DOWN = 50;
     if (game->gpu[2] == 'L')
        result.LEFT = 50;
     if (game->gpu[2] == 'R')
        result.RIGHT = 50;

     if (game->gpu[3] == 'U')
        result.UP = 75;
     if (game->gpu[3] == 'D')
        result.DOWN = 75;
     if (game->gpu[3] == 'L')
        result.LEFT = 75;
     if (game->gpu[3] == 'R')
        result.RIGHT = 75;
    }
  }

  // PRIORITY


    result.priority = 15;



  if (stone < 0 || (strcmp(game->gpu, "GAME_OVER") == 0))
  {
    result.priority = 0;
  }

  if (strcmp(game->gpu, "GAME_OVER") == 0)
  {
    if (reg0 >= reg2 && reg0 >= reg1)
      game->gold ++;
    else if (reg0 >= reg2 || reg0 >= reg1)
      game->silver++;
    else
      game->bronze++;
  }
  transform100(&result.UP, &result.DOWN, &result.LEFT, &result.RIGHT);
  return (result);
}

struct Result Archery(int player_id, int nb_game, struct Joueur *game) {
  struct Result result;
  static int nbtour = 0;
  result.RIGHT = 0;
  result.LEFT = 0;
  result.DOWN = 0;
  result.UP = 0;
  result.priority = 2;
  int test[16];
  int x;
  int y;
  int x2;
  int y2;
  int x3;
  int y3;


//PARSING

  if (player_id == 0)
  {
    x = game->reg_0;
    y = game->reg_1;
    x2 = game->reg_2;
    y2 = game->reg_3;
    x3 = game->reg_4;
    y3 = game->reg_5;
  }
  if (player_id == 1)
  {
    x = game->reg_2;
    y = game->reg_3;
    x2 = game->reg_0;
    y2 = game->reg_1;
    x3 = game->reg_4;
    y3 = game->reg_5;
  }
  if (player_id == 2)
  {
    x = game->reg_4;
    y = game->reg_5;
    x2 = game->reg_0;
    y2 = game->reg_1;
    x3 = game->reg_2;
    y3 = game->reg_3;
  }
  
 
 //CHOICE

  result.RIGHT = distance(x, y) - distance(x + (game->gpu[0] - 48) , y);
  result.LEFT = distance(x, y) - distance(x - (game->gpu[0] - 48), y);
  result.UP = distance(x, y) - distance(x , y - (game->gpu[0] - 48));
  result.DOWN = distance(x, y) - distance(x , y + (game->gpu[0] - 48));
  fprintf(stderr, "\nArcherybefore: u:%d, d:%d, r:%d, l:%d\n", result.UP, result.DOWN, result.RIGHT, result.LEFT);


  nbtour++;


  //PRIORITY

   fprintf(stderr, "\nResult: nbtour:%d\n", nbtour);
   
   result.priority = 10 + nbtour / 2;

   if (distance(x, y) < 4)
        result.priority = 0;
   else if (distance(x, y) > distance(x2, y2) || distance(x, y) > distance(x3, y3))
        result.priority *= 1.5;
   else if (distance(x, y) > distance(x2, y2) && distance(x, y) > distance(x3, y3))
        result.priority = 0;
   
  if (strcmp(game->gpu, "GAME_OVER") == 0)
  {
    result.priority = 0;
    nbtour = 0;
    if (distance(x, y) == distance(x2, y2) && distance(x, y) == distance(x3, y3))
      game->gold++;
    if (distance(x, y) <= distance(x2, y2) && distance(x, y) <= distance(x3, y3))
      game->gold++;
    else if (distance(x, y) <=  distance(x2, y2) || distance(x, y) <= distance(x3, y3))
      game->silver++;
    else
      game->bronze++;
  }

  result.nb_tour = nbtour;
  transform100(&result.UP, &result.DOWN, &result.LEFT, &result.RIGHT);
  fprintf(stderr, "Divingbefore: u:%d, d:%d, r:%d, l:%d, priority:%d\n\n", result.UP, result.DOWN, result.RIGHT, result.LEFT, result.priority);
  return (result);
}


int main() {
  int player_idx;
  scanf("%d", &player_idx);
  int nb_games;
  scanf("%d", &nb_games);
  fgetc(stdin);
  struct Joueur game[4];
  struct Result result0;
  struct Result result1;
  struct Result result2;
  struct Result result3;
  int result;
  int RIGHT = 0;
  int DOWN = 0;
  int LEFT = 0;
  int UP = 0;
  int priority0 = 0;
  int priority1 = 0;
  int priority2 = 0;
  int priority3 = 0;
  game[0].bronze = 0;
  game[0].silver = 0;
  game[0].gold = 0;
  game[1].bronze = 0;
  game[1].silver = 0;
  game[1].gold = 0;
  game[2].bronze = 0;
  game[2].silver = 0;
  game[2].gold = 0;
  game[3].bronze = 0;
  game[3].silver = 0;
  game[3].gold = 0;
  int tour = 0;
  // game loop
  while (1) {
    for (int i = 0; i < 3; i++) {
      char score_info[65];
      scanf("%[^\n]", score_info);
      fgetc(stdin);
    }
    for (int i = 0; i < nb_games; i++) {
      char gpu[65];
      int reg_0;
      int reg_1;
      int reg_2;
      int reg_3;
      int reg_4;
      int reg_5;
      int reg_6;
      scanf("%s%d%d%d%d%d%d%d", gpu, &reg_0, &reg_1, &reg_2, &reg_3, &reg_4,
            &reg_5, &reg_6);
      fgetc(stdin);
      strcpy(game[i].gpu, gpu);
      game[i].reg_0 = reg_0;
      game[i].reg_1 = reg_1;
      game[i].reg_2 = reg_2;
      game[i].reg_3 = reg_3;
      game[i].reg_4 = reg_4;
      game[i].reg_5 = reg_5;
      game[i].reg_6 = reg_6;
    }

    RIGHT = 0;
    DOWN = 0;
    LEFT = 0;
    UP = 0;

    result0 = Hurdle_Race(player_idx, 0, &game[0]);
    result1 = Archery(player_idx, 1, &game[1]);
    result2 = Skate(player_idx, 2, &game[2]);
    result3 = Diving(player_idx, 3, &game[3], result1.nb_tour);
    
    fprintf(stderr, "Race medaille: Gold:%d, Silver:%d, Bronze:%d,\n", game[0].gold, game[0].silver, game[0].bronze);
    fprintf(stderr, "Archery medaille: Gold:%d, Silver:%d, Bronze:%d,\n", game[1].gold, game[1].silver, game[1].bronze);
    fprintf(stderr, "Skate medaille: Gold:%d, Silver:%d, Bronze:%d,\n", game[2].gold, game[2].silver, game[2].bronze);
    fprintf(stderr, "Diving medaille: Gold:%d, Silver:%d, Bronze:%d,\n", game[3].gold, game[3].silver, game[3].bronze);


    if (game[0].silver > game[0].gold)
      result0.priority  *= (2 + game[0].silver - game[0].gold);
    if (game[0].bronze > game[0].gold)
      result0.priority  *= (1 + game[0].bronze - game[0].gold);
    if (game[1].silver > game[1].gold)
      result1.priority *= (1 + game[1].silver - game[1].gold);
    if (game[1].bronze > game[1].gold)
      result1.priority *= (1 + game[1].bronze - game[1].gold);
    if (game[2].silver > game[2].gold)
      result1.priority *= (1 + game[2].silver - game[2].gold);
    if (game[2].bronze > game[2].gold)
      result1.priority *= (1 + game[2].bronze - game[2].gold);
    if (game[3].silver > game[3].gold)
      result3.priority *= (1 + game[3].silver - game[3].gold);
    if (game[3].bronze > game[3].gold)
      result3.priority *= (1 + game[3].bronze - game[3].gold);


    if (tour < 50)
    {
      result1.priority += 10;
      result3.priority += 10;
    }
    else
    {
      result0.priority += 10;
      result2.priority += 10;
    }

    if (tour > 80 && game[0].gold == 0)
      result0.priority += 100;
    if (tour > 80 && game[1].gold == 0)
      result1.priority += 100;
    if (tour > 80 && game[2].gold == 0)
      result2.priority += 100;
    if (tour > 80 && game[3].gold == 0)
      result3.priority += 100;

    fprintf(stderr, "Race: u:%d, d:%d, r:%d, l:%d, priority:%d\n", result0.UP, result0.DOWN, result0.RIGHT, result0.LEFT, result0.priority);
    fprintf(stderr, "Archery: u:%d, d:%d, r:%d, l:%d, priority:%d\n", result1.UP, result1.DOWN, result1.RIGHT, result1.LEFT, result1.priority);
    fprintf(stderr, "Skate: u:%d, d:%d, r:%d, l:%d, priority:%d\n", result2.UP, result2.DOWN, result2.RIGHT, result2.LEFT, result2.priority);
    fprintf(stderr, "Diving: u:%d, d:%d, r:%d, l:%d, priority:%d\n", result3.UP, result3.DOWN, result3.RIGHT, result3.LEFT, result3.priority);

    UP = result0.UP * result0.priority + result1.UP * result1.priority + result1.UP * result1.priority + result3.UP * result3.priority;
    DOWN = result0.DOWN * result0.priority  + result1.DOWN * result1.priority + result2.DOWN * result2.priority + result3.DOWN * result3.priority ;
    LEFT = result0.LEFT * result0.priority + result1.LEFT * result1.priority + result2.LEFT * result2.priority  + result3.LEFT * result3.priority ;
    RIGHT = result0.RIGHT * result0.priority + result1.RIGHT * result1.priority + result2.RIGHT * result2.priority + result3.RIGHT * result3.priority ;
    fprintf(stderr, "\nResult: u:%d, d:%d, r:%d, l:%d\n", UP, DOWN, RIGHT, LEFT);

    if (UP >= RIGHT && UP >= LEFT && UP >= DOWN)
      printf("UP\n");
    else if (RIGHT >= DOWN && RIGHT >= LEFT)
      printf("RIGHT\n");
    else if (DOWN >= LEFT)
      printf("DOWN\n");
    else
      printf("LEFT\n");
    tour++;
  }
  return 0;
}
