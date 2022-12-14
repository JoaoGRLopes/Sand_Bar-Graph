#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Process {
public:
    fstream fstream;
    string input;
    string word;
    vector<int> data;
    /*   void bargraphnumber();*/
    void opendirectly();
    //void openningFile();
    void randomNumbers();
    void print();
    Process();
    ~Process();

private:
    vector<int> space;
    void spaces(string str, vector<int>& space);
    void vectordata(string str, vector<int>& space, vector<int>& data);
    void acolite();
    void read_file();
};

// member implementation
void Process::randomNumbers() {
    for (int i = 0; i < 16; i++) {
        data.push_back(rand() % 11 + 1);
    }
}
//COULD NOT FINISH THIS PART
//void Input::bargraphnumber() {
//    int barnumber;
//    if (barnumber == 1) {
//        fstream.open("Bargraph1.txt");
//        inputFileStream.open("bargraph1.txt");
//    }
//    if (barnumber == 2) {
//        fstream.open("Bargraph2.txt");
//        inputFileStream.open("bargraph2.txt");
//    }
//    if (barnumber == 3) {
//        fstream.open("Bargraph3.txt");
//        inputFileStream.open("bargraph3.txt");
//    }
//    if (barnumber == 4) {
//        fstream.open("Bargraph4.txt");
//        inputFileStream.open("bargraph4.txt");
//    }
//}

void Process::opendirectly() { word = input; acolite(); }


void  Process::print() {
    cout << "data size is [" << data.size() << "] = { ";
    for (int i = 0; i < data.size() - 1; i++)
    {
        cout << data[i] << ", ";
    }
    cout << data[data.size() - 1] << " }" << endl;
}

void Process::spaces(string str, vector<int>& space) { //private
    for (int i = 0; i <= str.size(); i++) {
        if (i == 0) {
            space.push_back(str.find(" "));
        }
        else {
            space.push_back(str.find(" ", space[i - 1] + 1));
        }
        if (space[i] == -1) {
            space.pop_back();
            break;
        }
    }
}

void  Process::vectordata(string str, vector<int>& space, vector<int>& data) { //private
    for (int i = 0; i <= space.size(); i++) {
        if (i == 0) {
            data.push_back(stoi(str.substr(0, space[i])));
        }
        else if (i == space.size()) {
            data.push_back(stoi(str.substr(space[i - 1] + 1, (str.size() - space[i - 1]))));
        }
        else {
            data.push_back(stoi(str.substr(space[i - 1] + 1, (space[i] - space[i - 1]))));
        }
    }
}

void Process::acolite() { //private
    spaces(word, space);
    vectordata(word, space, data);
}

void  Process::read_file() { //private
    fstream.open(input);
    getline(fstream, word);
}

Process::Process() {
    word = input = "";
}
Process::~Process() {}

class Plot {
public:
    //ostream ostr;
    string filename;
    int y_max = 0;
    int total = 0;
    vector<vector<char>> xy;
    char orientation = 'h'; // {'h', 'H', 'v', 'V'}
    void buildHorizontalGraph();
    void buildVerticalGraph();
    void plot(char ori, ostream* ostr);
    void ploth(ostream* ostr);
    void plotv(ostream* ostr);
    void save_to_file(string path);
    void calc_avail_space();
    void calc_sand();
    int calc_total(int* calc);
    void print(int* pr);
    int max_index(int* arr);

    int structure[16] = { 2,6,6,6,6,8,8,8,8,8,8,11,11,11,11,7 };
    int data[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int avail_space[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int sand[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

    Plot(vector<int>& from_Class_Input);
    ~Plot();
};

int Plot::max_index(int* arr) {
    int max_i = 0;
    for (int i = 0; i < 15; i++) {
        max_i = (arr[i] > arr[i + 1] ? i : i + 1);
    }
    return max_i;
}

void Plot::buildHorizontalGraph() {
    for (int j = 0; j < 16; j++) {
        int i = 0;
        int MIN = min(sand[j], structure[j]);
        xy.push_back(vector<char>());
        for (i; i < MIN; i++) {
            xy[j].push_back('_');
            xy[j].push_back(' ');
        }
        if (sand[j] < structure[j]) {
            for (i; i < structure[j] - 1; i++) {
                xy[j].push_back('.');
                xy[j].push_back(' ');
            }
            xy[j].push_back('|');
        }
    }
}

void Plot::buildVerticalGraph() {

    y_max = max_index(structure);
    for (int j = 0; j < 16; j++) {
        int i = 0;
        int MIN = min(sand[j], structure[j]);
        xy.push_back(vector<char>());
        for (i; i < MIN; i++) {
            xy[j].push_back('|');
        }

        if (sand[j] < structure[j]) {
            for (i; i < structure[j] - 1; i++) {
                xy[j].push_back('.');
            }
            xy[j].push_back('-');
            i++;
        }

        for (i; i < structure[y_max] + 1; i++) {
            xy[j].push_back(' ');
        }
    }
}


void Plot::ploth(ostream* ostr) {
    buildHorizontalGraph();

    *ostr << endl;
    for (int j = 0; j < 16; j++) {
        if (sand[j] < 10) {
            *ostr << sand[j] << " |";
        }
        else {
            *ostr << 1 << sand[j] << "|";
        }
        for (int i = 0; i < xy[j].size(); i++) { *ostr << xy[j][i]; }
        if (sand[j] < structure[j]) { *ostr << avail_space[j]; }
        *ostr << endl;
    } *ostr << endl;
}

void Plot::plotv(ostream* ostr) {
    buildVerticalGraph();

    for (int i = structure[y_max]; i >= 0; i--) {
        for (int j = 0; j < 16; j++) {
            if (i == structure[j] && avail_space[j]) {
                if (avail_space[j] < 10) {
                    *ostr << avail_space[j] << "  ";
                }
                else {
                    *ostr << 1 << (avail_space[j] - 10) << " ";
                }
            }
            else {
                *ostr << xy[j][i] << "  ";
            }
        } *ostr << endl;
    } *ostr << "----------------------------------------------" << endl;

    for (int j = 0; j < 16; j++) {
        if (sand[j] < 10) {
            *ostr << sand[j] << "  ";
        }
        else {
            *ostr << 1 << (sand[j] - 10) << " ";
        }
    } *ostr << endl << endl;
}

void Plot::plot(char ori, ostream* ostr) {
    *ostr << "\r\nASCII art bar graph plot showing sand on top of the graph:\r\n\r\n";
    if (ori == 'v' || ori == 'V') {
        plotv(ostr);
    }
    else {
        ploth(ostr);
    }
    *ostr << "Total " << total << " units of sand." << endl;
}

void Plot::calc_sand() {
    for (int i = 0; i < 16; i++) {
        sand[i] = structure[i] - avail_space[i];
    }
}

void Plot::calc_avail_space() {
    for (int i = 0; i < 16; i++) {
        avail_space[i] = (data[i] > structure[i] ? 0 : structure[i] - data[i]);
    }
}

int Plot::calc_total(int* calc) {
    int total = 0;
    for (int i = 0; i < 16; i++) { total += calc[i]; }
    return total;
}

void Plot::save_to_file(string path) {
    if (path != "n") {
        ofstream f2;
        f2.open(path);
        if (f2.is_open()) {
            plot(orientation, &f2);
            f2.close();
            cout << "The bar graph with sand has been saved as " << filename << endl;
        }
    }
}

void Plot::print(int* pr) {
    cout << "{ ";
    for (int i = 0; i < 15; i++) { cout << pr[i] << ", "; }
    cout << pr[15] << " }" << endl;
}

Plot::Plot(vector<int>& from_Class_Input) {
    for (int i = 0; i < 16; i++) {
        data[i] = from_Class_Input[i];
    }
    calc_avail_space();
    calc_sand();
    total = calc_total(avail_space);
}

Plot::~Plot() {}

int main() {
repeat:

    cout << "Welcome to \"The Bar Graph Sand Program\"" << endl;
    cout << "Name: Joao Guilherme Rodrigues Figueira Lopes" << endl;
    cout << "SID: 9074477" << endl;
    cout << setfill('*') << setw(50) << '*' << endl;



    string repeat;
    Process input;

    cout << "Please enter the bar graph data with spaces directly, or enter a \"filename\" to read from a text file input, or type \"Random\" to randomly generate a bar graph:" << endl
        << "2 6 3 5 2 8 1 4 2 2 5 11 1 4 11 7  or BarGraph or Random " << endl << endl;
    cout << "The option in program - BarGraph does not work " << endl;
    getline(cin, input.input); //wait for input from user

     //COULD NOT FINISH THIS PART
 /*   if (input.input == "BarGraph") {
        cout << "Please choose a number between 1 to 4 to choose which Bargraph you want to output: " << endl;
          int barnumber;
        cin >> barnumber;
        input.bargraphnumber();
        cout << "Read file .." << endl;
        input.processfile();
    }
    else*/
    if (input.input == "Random") {
        cout << "Generate random number .." << endl;
        input.randomNumbers();
    }
    else {
        cout << "Read direct input .." << endl;
        input.opendirectly();
    } // endif

    Plot plot(input.data);
    cout << "Answer: This bar graph can hold a total of " << plot.total
        << " units of sand." << endl << endl;

    cout << "Please enter the bar graph orientation 'v' (vertical) or 'h'"
        << "(horizontal) " << endl;
    cin >> plot.orientation;

    plot.plot(plot.orientation, &cout);
    getline(cin, input.input); //wait for input from user

    cout << "Please enter a filename to save bar graph to text file or enter 'n'"
        << "to not save:  BarGraphSand.txt ...or... n" << endl;

    getline(cin, plot.filename); //wait for input from user
    plot.save_to_file(plot.filename);

    cout << "Please type 'Yes' or 'yes' to run again:" << endl;
    cin >> repeat;

    if (repeat == "yes" || repeat == "Yes") {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << endl << endl;
        goto repeat;
    }
    else {
        cout << "Thank you for using the bar graph sand program." << endl
            << "Goodbye!" << endl;
    }

    return 0;
}
