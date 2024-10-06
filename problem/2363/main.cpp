    #include <iostream>
    #include <vector>
    using namespace std;

    int count_memory_leaks(int n, int m, vector<pair<int, int>>& intervals) {
        // 初始化座位状态，-1表示座位空闲
        vector<int> seats(m, -1);
        vector<int> seats_1(m, -1);
        int leaks = 0;
        vector<int>time_added(m,-1);//记录是否加过时间，-1表示未加时，0为加过时

        // 遍历每个同学
        for (const auto& interval : intervals) {
            long long a = interval.first;
            long long b = interval.second;
            int chosen_seat = -1;

            // 尝试寻找编号最小且两侧座位都空闲的座位
            for (int i = 0; i < m; ++i) {
                if (seats[i] < a) {  // 座位i已经空闲
                    bool left_free = (i == 0 || seats[i - 1] < a);  // 左侧座位是否空闲
                    bool right_free = (i == m - 1 || seats[i + 1] < a);  // 右侧座位是否空闲
                    if (left_free && right_free) {
                        chosen_seat = i;
                        break;
                    }
                }
            }

            // 如果没有找到两侧空闲的座位，再寻找任意空闲座位
            if (chosen_seat == -1) {
                for (int i = 0; i < m; ++i) {
                    if (seats[i] < a) {
                        chosen_seat = i;
                        break;
                    }
                }
            }

            // 如果找到了座位
            if (chosen_seat != -1) 
            {
                seats[chosen_seat] = b;//更新座位时间
                seats_1[chosen_seat] = a;
                for (int i=0;i<m;i++)//遍历每个位置来判断加时
                {
                    
                    if(seats[i]>=a && time_added[i] == -1)//如果座位有人且还没有加过时
                    {
                        bool left_free = (i == 0 || seats[i - 1] < a);
                        bool right_free = (i == m - 1 || seats[i + 1] < a);
                        if(!left_free || !right_free)//如果左边或右边有人
                        {  
                            seats[i] = (2*seats[i] - seats_1[i]);//延长时间
                            time_added[i] = 0;//将加时记录下来
                        }
                    }
                    if (seats[i] < a)//如果座位已经空出，则重置加时记录
                        {
                        time_added[i] = -1;
                        }    
                }
            } else {
                // 否则发生内存泄漏
                leaks++;
            }
        }
        return leaks;
    }

    int main() {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> intervals(n);
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i].first >> intervals[i].second ;
        }
        cout << count_memory_leaks(n, m, intervals) << endl;
        return 0;
    }