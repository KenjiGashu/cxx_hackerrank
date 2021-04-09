#include <bits/stdc++.h>
#include <queue>

using namespace std;
class Position;

class Knight{

    public:
       Knight() = delete;
        explicit Knight(int a, int b):
            a(a), b(b){}
        explicit Knight(int a, int b, int x, int y):
            a(a), b(b), y(y), x(x){}

        friend ostream& operator<<(ostream&os,  Knight k){
            os << "oi" << endl;
        }

        void movement(){

        }

        int a;
        int b;
        int x;
        int y;
};



class Position{
    public:
        int x;
        int y;
};

// Complete the knightlOnAChessboard function below.
vector<vector<int>> knightlOnAChessboard(int n) {


}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
