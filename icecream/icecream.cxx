#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the icecreamParlor function below.
vector<int> icecreamParlor(int m, vector<int> arr, vector<int> arr2) {
    vector<int> answer(2) ;
    for(int i=0; i<arr.size();i++){
        int cost1 = arr[i];
        cout << "cost1:" << cost1 << " - cost2:" << m-cost1 << " - m:" << m << endl;

        int cost2 = m-cost1;
        if(cost2 >= 0 && arr2[cost2] >= 0 && i!=arr2[cost2]){
            cout << "found answer? cost1: " << cost1 << ", cost2: "
                 << cost2 << ", pos: " << arr2[cost2]+1 <<  endl;
            answer[0] = i+1;
            answer[1] = arr2[cost2]+1;
            break;
        }
    }
    return answer;

}

int main()
{
    //ofstream fout("out.txt");
    ofstream fout(getenv("OUTPUT_PATH"));

    // std::ifstream in("in.txt");
    // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    // std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int m;
        cin >> m;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n,-1);
        vector<int> arr2(10001, -1);

        for(auto & element : arr2){
            element = -1;
        }

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr2[arr_item] = i;
            cout << "load: " << arr_item << ":" << i << endl;

            arr[i] = arr_item;
        }

        vector<int> result = icecreamParlor(m, arr, arr2);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
