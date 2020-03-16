#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct line {
    int A;
    int B;
    int C;
}Line;

typedef struct dot {
    int xu;
    int xd;
    int yu;
    int yd;
}Dot;

vector<Line> lines;
vector<Dot> dots;
//判定两点重合
int dotEql(Dot da, Dot db) {
    if ((da.xu * db.xd == db.xu * da.xd) && (da.yu * db.yd == db.yu * da.yd)) {
        return 1;
    }
    else {
        return 0;
    }
}
//添加一条直线到直线集中
void addLine(int x1, int y1, int x2, int y2) {
    Line tmpLine;
    tmpLine.A = y2 - y1;
    tmpLine.B = x1 - x2;
    tmpLine.C = x2 * y1 - x1 * y2;
    lines.push_back(tmpLine);
}
//求交点并添加到点集中
void intersection(Line la, Line lb) {
    Dot tmpDot;
    int i;
    int m = dots.size();
    if (la.A * lb.B == la.B * lb.A) {
        return;
    }
    else {
        tmpDot.xu = lb.B * la.C - la.B * lb.C;
        tmpDot.yu = la.A * lb.C - lb.A * la.C;
        tmpDot.xd = tmpDot.yd = lb.A * la.B - la.A * lb.B;
        for (i = 0; i < m; i++) {
            if (dotEql(tmpDot, dots[i])) {
                return;
            }
        }
        dots.push_back(tmpDot);
    }
    return;
}

int main(int argc, char* argv[])
{
    int n, m, i, x1, y1, x2, y2;
    char c;
    FILE* stream;
    if (argc == 3) {
        if (!strcmp(argv[1], "-i")) {
            freopen_s(&stream, argv[2], "r", stdin);
        }
        else if (!strcmp(argv[1], "-o")) {
            freopen_s(&stream, argv[2], "w", stdout);
        }
    }
    //一个参数
    else if (argc == 5) {
        if (!strcmp(argv[1], "-i")) {
            freopen_s(&stream, argv[2], "r", stdin);
            if (!strcmp(argv[3], "-o")) {
                freopen_s(&stream, argv[4], "w", stdout);
            }
        }
        else if (!strcmp(argv[1], "-o")) {
            freopen_s(&stream, argv[2], "w", stdout);
            if (!strcmp(argv[3], "-i")) {
                freopen_s(&stream, argv[4], "r", stdin);
            }
        }
    }
    //两个参数
    cin >> n;
    while (n--) {
        cin >> c >> x1 >> y1 >> x2 >> y2;
        addLine(x1, y1, x2, y2);
        m = lines.size();
        for (i = 0; i < m - 1; i++) {
            intersection(lines[m - 1], lines[i]);
        }
    }
    cout << dots.size() << endl;
    return 0;
}
