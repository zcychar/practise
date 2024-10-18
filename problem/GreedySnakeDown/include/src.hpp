#ifndef SRC_HPP
#define SRC_HPP
#include <iostream>
#include <utility>
#include<vector>
struct Map;

enum class instruction { UP, DOWN, LEFT, RIGHT, NONE };

//the instruction of the snake

bool is_food(Map *map, int x, int y);

//return true if the cell at (x,y) is food

bool is_wall(Map *map, int x, int y);

//return true if the cell at (x,y) is wall

void eat_food(Map *map, int x, int y);

//remove the food at (x,y)

int get_height(Map *map);

//return the height of the map

int get_width(Map *map);

//return the width of the map

struct Snake {
  // store the necessary information of the snake
  // use any data structure you like

  // you can also add any necessary function
  //------------------------------------------
  int length, count;
  int head_point;

  struct Node {
    int x, y, next_position;
    instruction ins;
  } body[500015];

  bool dead_body[55][55];

  void initialize(int x, int y, instruction ins) {
    // (x,y) isthe position of the head of the snake, ins is the initial orientation of the snake
    //------------------------------------------
    length = 1, count = 1;
    head_point = 1;
    body[count].x = x, body[count].y = y;
    body[count].ins = ins;
  }

  int get_length() {
    //return the length of the snake
    //------------------------------------------
    return length;
  }

  bool move(Map *map, instruction ins) {
    int height = get_height(map), width = get_width(map);
    int front_x = body[head_point].x, front_y = body[head_point].y;
    int current_x = -1, current_y = -1;
    instruction current_ins = ins;
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        dead_body[i][j] = false;
      }
    }
    int current_position = head_point;
    for (int i = 1; i < length-1; ++i) {
      current_position = body[current_position].next_position;
      dead_body[body[current_position].x][body[current_position].y] = true;
    }

    if (current_ins == instruction::NONE) {
      current_ins = body[head_point].ins;
    }
    switch (current_ins) {
      case instruction::UP: {
        if(body[head_point].ins==instruction::DOWN) {
          return false;
        }
        current_x = front_x - 1;
        current_y = front_y;
        break;
      }
      case instruction::DOWN: {
        if(body[head_point].ins==instruction::UP) {
          return false;
        }
        current_x = front_x + 1;
        current_y = front_y;
        break;
      }
      case instruction::LEFT: {
        if(body[head_point].ins==instruction::RIGHT) {
          return false;
        }
        current_x = front_x;
        current_y = front_y - 1;
        break;
      }
      case instruction::RIGHT: {
        if(body[head_point].ins==instruction::LEFT) {
          return false;
        }
        current_x = front_x;
        current_y = front_y + 1;
        break;
      }
      default: {
        break;
      }
    }

    if (current_x < 0 || current_x >= height || current_y < 0 || current_y >= width) {
      return false;
    }
    if (is_wall(map, current_x, current_y)) {
      return false;
    }
    if (dead_body[current_x][current_y]) {
      return false;
    }
    if (is_food(map, current_x, current_y)) {
      eat_food(map, current_x, current_y);
      length++;
    }
    body[++count].x = current_x;
    body[count].y = current_y;
    body[count].ins = current_ins;
    body[count].next_position = head_point;
    head_point = count;
    return true;
  }

  std::pair<int, std::pair<int, int> *> get_snake() {
    //return the length of the snake and a pointer to the array of the position of the snake
    //you can store the head as the first element
    //------------------------------------------

    auto body_path=new std::pair<int,int> [505];

    int current_position = head_point;
    std::pair<int, int> current_location = std::make_pair(body[current_position].x, body[current_position].y);
    body_path[0]=current_location;
    for (int i = 1; i < length; ++i) {
      current_position = body[current_position].next_position;
      current_location = std::make_pair(body[current_position].x, body[current_position].y);
      body_path[i] = current_location;
    }
    std::pair<int, std::pair<int, int> *> value = std::make_pair(length,body_path);
    return value;
  }
};

const int MaxWidth = 25;

struct Map {
  // store the necessary information of the map
  bool wall[MaxWidth][MaxWidth];
  bool food[MaxWidth][MaxWidth];
  int width, height;

  int get_height() {
    //return the height of the map
    return height;
  }

  int get_width() {
    //return the width of the map
    return width;
  }

  bool is_food(int x, int y) {
    //return true if the cell at (x,y) is food
    if (food[x][y]) {
      return true;
    }
    return false;
  }

  void eat_food(int x, int y) {
    //eat the food at (x,y)
    food[x][y] = false;
  }

  bool is_wall(int x, int y) {
    //return true if the cell at (x,y) is wall
    if (wall[x][y]) {
      return true;
    }
    return false;
  }

  // use any data structure you like
  // you can also add any necessary function
  //------------------------------------------
  int snake_map[MaxWidth][MaxWidth];

  void initialize(Snake *snake) {
    char str[MaxWidth];
    int head_x = -1, head_y = -1;
    instruction ins;
    //------------------------------------------
    std::cin >> height >> width;
    for (int i = 0; i < height; ++i) {
      std::cin >> str;
      for (int j = 0; j < width; ++j) {
        switch (str[j]) {
          case '#': {
            wall[i][j ] = true;
            break;
          }
          case '*': {
            food[i][j ] = true;
            break;
          }
          case '@': {
            head_x = i;
            head_y = j ;
            break;
          }
          default: {
            break;
          }
        }
      }
    }
    std::cin >> str;
    switch (str[0]) {
      case 'U':
        ins = instruction::UP;
        break;
      case 'D':
        ins = instruction::DOWN;
        break;
      case 'L':
        ins = instruction::LEFT;
        break;
      case 'R':
        ins = instruction::RIGHT;
        break;
      default:
        ins = instruction::NONE;
    }
    //------------------------------------------
    snake->initialize(head_x, head_y, ins);
  }

  void print(Snake *snake) {
    auto snake_body = snake->get_snake();
    //------------------------------------------
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        snake_map[i][j] = 0;
      }
    }
    int length = snake_body.first;
    auto position = snake_body.second;
    std::pair<int, int> current_position = *position;
    snake_map[current_position.first][current_position.second] = 2;
    for (int i = 1; i < length; ++i) {
      current_position = *(position + i);
      snake_map[current_position.first][current_position.second] = 1;
    }
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        if (wall[i][j]) {
          std::cout << '#';
        } else if (snake_map[i][j]) {
          if (snake_map[i][j] == 1) {
            std::cout << 'o';
          } else {
            std::cout << "@";
          }
        } else if (food[i][j]) {
          std::cout << '*';
        } else {
          std::cout << '.';
        }
      }
      std::cout <<std::endl;
    }
    delete[] position;
  }
};

struct Game {
  Map *map;
  Snake *snake;
  int score;
  int round;

  void initialize() {
    map = new Map();
    snake = new Snake();
    map->initialize(snake);
    score = 0;
    round = 0;
  }
  ~Game() {
    delete map;
    delete snake;
  }
  bool step() {
    char str[MaxWidth];
    std::cin >> str;
    instruction ins;
    switch (str[0]) {
      case 'U':
        ins = instruction::UP;
        break;
      case 'D':
        ins = instruction::DOWN;
        break;
      case 'L':
        ins = instruction::LEFT;
        break;
      case 'R':
        ins = instruction::RIGHT;
        break;
      default:
        ins = instruction::NONE;
    }
    if (snake->move(map, ins)) {
      score++;
    } else {
      return false;
    }
    return true;
  }

  void print() {
    std::cout << "Round: " << round << std::endl;
    map->print(snake);
  }

  void play() {
    while (step()) {
      round++;
      print();
    }
    score += snake->get_length();
    std::cout << "Game Over" << std::endl;
    std::cout << "Score: " << score << std::endl;
  }
};
#endif
