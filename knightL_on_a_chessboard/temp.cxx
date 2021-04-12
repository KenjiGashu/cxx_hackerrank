#include <array>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>

using namespace std;

class Position;
class Board;

class Knight {

  public:
    Knight() {
      this->a     = -1;
      this->b     = -1;
      this->x     = -1;
      this->y     = -1;
      this->moves = -1;
    };
    explicit Knight(int a, int b) : a(a), b(b) {}
    explicit Knight(int a, int b, int x, int y, int moves)
      : a(a), b(b), x(x), y(y), moves(moves) {}

    friend ostream &operator<<(ostream &os, Knight k) {
      os << "Knight[ab(" << k.a << "," << k.b << ") at [" << k.x << "," << k.y
         << "] moves: " << k.moves << "]";
      return os;
    }

    bool isEmpty() {
      //cout << "is empty:[" << !(this->a > 0) << "]" << endl;
      return !(this->a > 0);
    }

    int a;
    int b;
    int x;
    int y;
    int moves;
};

class Board {
  public:
    Board(int n) : n(n), MAX_SIZE(25) {
      //cout << "initializing board: n[" << n << "]" << endl;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          visited[i][j] = -1;
        }
      }
    };
    ~Board(){

    };
    int n;
    int MAX_SIZE;
    array<array<int, 25>, 25> visited;
    deque<Knight> dk;
    Knight answer;

    void clean_all() {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          visited[i][j] = -1;
        }
      }
      while (dk.size() > 0) {
        dk.pop_front();
      }
      answer = Knight{};
    }

    shared_ptr<Knight> get_knight() {
      if (dk.size() > 0) {
        shared_ptr<Knight> out = make_shared<Knight>(dk.front());
        dk.pop_front();
        return out;
      } else {
        return nullptr;
      }
    };

    bool viable_move(Knight k) {
      // cout << "[viable_move] start x[" << x << "],y[" << y << "]" << endl;
      if (k.x < 0 | k.y < 0)
        return false;
      if (k.x < n && k.y < n) {
        if (visited[k.x][k.y] > 0) {
          // cout << "its already visited! visited[" << visited[k.x][k.y] << "]"
          // << endl;
          return false;
        } else {
          //cout << "viable_move: its ok! " << k << endl;
          return true;
        }
      }
      return false;
    };

    int knight_arrived() {
      if (visited[n - 1][n - 1] > 0) {
        if (answer.isEmpty()) {
          cout << "weird error has happened when found solution!" << endl;
          return -1;
          // throw Exception; //weird error
        } else {
          // cout << "[knight-arrived] solution found visited[" << n - 1 << "]["
          //      << n - 1 << "]=" << visited[n - 1][n - 1] << " " << answer << endl;
          return answer.moves;
        }
      }
      // cout << "knight-arrived: not yet! visited[" << n - 1 << "][" << n - 1
      //      << "]=" << visited[n - 1][n - 1] << endl;
      return -1;
    }

    bool visit(Knight k) {
      if (viable_move(k)) {
        if (visited[k.x][k.y] > 0) {
          //cout << "already visited! K[" << k << "]" << endl;
          return false;
        }
        dk.push_back(k);
        visited[k.x][k.y] = 1;
        // found solution?
        if (k.x == n - 1 && k.y == n - 1) {
          //cout << "chosen move is detination! " << k << endl;
          answer = k;
        }
        return true;
      } else {
        //cout << "not viable[" << k.x << "," << k.y << "]" << endl;
        return false;
      }
    };
};

bool make_moves(Board &board) {
  // cout << "[make_moves] start" << endl;
  shared_ptr<Knight> k = board.get_knight();
  //cout << "[make_moves] " << *k << endl;
  if (k) {
    //cout << "add knights! ====================" << endl;
    board.visit(Knight{k->a, k->b, k->x + k->a, k->y + k->b, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x - k->a, k->y + k->b, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x + k->a, k->y - k->b, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x - k->a, k->y - k->b, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x + k->b, k->y + k->a, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x - k->b, k->y - k->a, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x + k->b, k->y - k->a, k->moves + 1});
    board.visit(Knight{k->a, k->b, k->x - k->b, k->y + k->a, k->moves + 1});
    //cout << "FINISH add knights! ====================" << endl;
    return true;
  }
  return false;
}

int calls(Board &board) {
  int ret = board.knight_arrived();
  while ((ret < 0) && board.dk.size() > 0) {
    // cout << "[calls] ret[" << ret << "] queue size: " << board.dk.size()
    //      << endl;
    if (!make_moves(board))
      return -1;

    ret = board.knight_arrived();
  }
  return ret;
}

vector<vector<int>> solve(Board &board) {
  vector<vector<int>> found_answers;
  found_answers.resize(board.n-1, vector<int>(board.n-1));

  for(vector<vector<int>>::iterator subvec = found_answers.begin(); subvec != found_answers.end(); subvec++){
    for(vector<int>::iterator answ = subvec->begin(); answ != subvec->end(); answ++){
      *answ = -1;
    }
  }
  for (int i = 1; i < board.n; i++) {
    for (int j = 1; j < board.n; j++) {
      //printf("answers[%d][%d] = %d\n", i, j, found_answers.at(i).at(j));
      if (found_answers.at(i-1).at(j-1)<0) {
        Knight initial_knight = Knight{i, j, 0, 0, 0};
        board.visited[0][0] = 1;
        board.dk.push_back(initial_knight);
        //printf("make call a[%d]b[%d]\n",i,j);
        //cout << "make call a[" << i << "]b[" << j << "]" << endl;
        int ret = calls(board);
        if (ret){
          //printf("found solution! move[%d] a[%d]b[%d] \n",ret ,i ,j);
          //printf("%d ",ret);
          // cout << "found solution! move[" << ret << "] a[" << i << "]b[" << j
          //      << "]" << endl;
        }
        else{
          //printf("%d ", -1);
          //printf("no solution found! a[%d]b[%]\n",i,j);
          //cout << "no solution found! a[" << i << "]b[" << j << "]" << endl;
        }

        found_answers[i-1][j-1] = ret;
        found_answers[j-1][i-1] = ret;
        // clean old things
        board.clean_all();
      } else{
        //printf("%d ",found_answers.at(i).at(j));
        //printf("found solution! move[%d] a[%d]b[%d] - already computed\n", found_answers.at(i).at(j), i, i);
        //cout << "found solution! move[" << found_answers.at(i).at(j) << "] a[" << i << "]b[" << j << "] - already computed" << endl;
      }
    }
    //printf("\n");
  }
  return found_answers;
}

class Position {
  public:
    int x;
    int y;
};

int main() {
  // Knight oi{1, 2, 0, 0, 0};
  // ostringstream ss;
  // ss << oi << "- %d %s %d";
  // printf(ss.str().c_str(), 1, "ei", 10);

  // cout << oi;
  // deque<Knight> my_deque;
  // my_deque.push_back(Knight{1, 2, 0, 0, 9});
  // my_deque.push_back(Knight{2, 2, 3, 4, 9});
  // my_deque.push_back(Knight{1, 2, 5, 5, 9});
  // for (auto k : my_deque) {
  //   cout << k;
  // }

  // vector<vector<int>> teste;
  // teste.resize(25,vector<int>(25));
  // teste[0][0] = 1;
  // cout << "teste: " << teste[0][0] << endl;

  // cout << arey.at(0)<< endl;
  // cout << arey[0].size() << endl;
  Board b{5};
  // cout << b.visited[0][0] << endl;
  // cout << b.visited[0][1] << endl;
  // cout <<"viable: " << b.viable_move(1,1) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(-1, 2) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(0, 0) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(0, -1) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(0, -3) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(10, 10) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(25,2) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(25, 25) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(40, 30) << " ]" << endl;
  // cout <<"viable: " << b.viable_move(40, 8) << " ]" << endl;

  // my_deque.pop_front();
  // cout << "size: " << my_deque.size() << endl;
  // my_deque.pop_front();
  // cout << "size: " << my_deque.size() << endl;
  // my_deque.pop_front();
  // cout << "size: " << my_deque.size() << endl;

  Board b2{5};
  solve(b2);

  // my_deque.pop_front();
  //     cout << "size: " << my_deque.size() << endl;

  // for(int i=0; i < 25; i++){
  //     for (int j=0; j < 25; j++){
  //         arey[i][j] = 0;
  //     }
  // }
}
