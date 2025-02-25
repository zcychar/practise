

#include <fstream>
#include <vector>
#include <cstring>
#include<iostream>
#include <algorithm>
#include <bits/atomic_base.h>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;

template <typename T>
struct Unit {
  T value = {};         // 值
  int pos = 0;          // body_文件中头元素位置
  int next = 0;         // 头链表中下一个位置
  int size = 0;         // 作为头结点时 块大小
  char index[80] = {};  // 键

  Unit()=default;

  Unit(const char *str);

  Unit(const char *str, T val);

  bool operator<(const Unit &other) const;

  bool operator>(const Unit &other) const;

  bool operator<=(const Unit &other) const;

  bool operator>=(const Unit& other) const;

  bool operator==(const Unit &other) const {
    if(strcmp(index,other.index)&&value==other.value) {
      return true;
    }
    return false;
  }
};

  //位置索引index可以取为对象写入的起始位置
template <class T, int info_len = 2>
class MemoryRiver {
 private:
  /* your code here */
  fstream file;
  string file_name;
  int sizeofT = sizeof(T);

 public:
  MemoryRiver() = default;

  MemoryRiver(const string &file_name) : file_name(file_name) {}

  void initialise(string FN = "") {
    if (FN != "") file_name = FN;
    file.open(file_name, std::ios::out);
    int tmp = 0;
    for (int i = 0; i < info_len; ++i) file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
  }
  
  // 读出第n个int的值赋给tmp，1_base
  void get_info(int &tmp, int n) {
    if (n > info_len) return;
    file.open(file_name);
    file.seekg((n - 1) * sizeof(int));
    file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
  }

  // 将tmp写入第n个int的位置，1_base
  void write_info(int tmp, int n) {
    if (n > info_len) return;
    file.open(file_name);
    file.seekp((n - 1) * sizeof(int));
    file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
  }

  // 在文件合适位置写入类对象t，并返回写入的位置索引index
  // 位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  int write(T &t, int size) {
    file.open(file_name, std::ios::app);
    int index = file.tellp();
    file.write(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
    return index;
  }

  // 用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(T &t, const int index, int size) {
    file.open(file_name);
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
  }

  // 读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void read(T &t, const int index,int size) {
    file.open(file_name);
    file.seekg(index);
    file.read(reinterpret_cast<char*>(&t),sizeofT*size);
    file.close();
  }

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int index) {
    update(T{},index);
  }
};

template <typename T>
class Directory {
  const int sizeofU_ = sizeof(Unit<T>);
  const int maxm_size_ = 2048;
  const int limit = 2000;
  MemoryRiver<Unit<T>, 2> directory_;  // 0:sum 1:head 2:max_size=sqrt(n)
  MemoryRiver<Unit<T>, 0> body_;
  vector<Unit<T>> current_unit_;
  vector<Unit<T>> load_;//保证 sum 严格等于 load_ 元素个数， sum 存储总开节点数

public:
  Directory(const string file_name = "");

  void insert(Unit<T> item);

  void del(Unit<T> item) {
    int sum = 0, head = 0;
    directory_.get_info(sum, 1);
    directory_.get_info(head, 2);
    load_.resize(sum+1);
    directory_.read(load_[1], 2 * sizeof(int), sum);
    //load_[starter]<item<load[ender]
    //item could be in
    int starter = head, ender = 0;
    for (int i = head; i; i = load_[i].next) {
      int tmp=strcmp(load_[i].index,item.index);
      if (tmp<0) {
        starter = i;
      }
      if(tmp>0) {
        ender=i;
        break;
      }
    }
    for(int i=starter;i!=ender;i=load_[i].next) {
      current_unit_.resize(load_[i].size+1);
      body_.read(current_unit_[1],load_[i].pos,load_[i].size);
      auto it=std::lower_bound(current_unit_.begin()+1,current_unit_.begin()+load_[i].size+1,item);
      if(it!=current_unit_.end()) {
        while(it!=current_unit_.end()&&strcmp(item.index,it->index)==0) {
          if(item.value==it->value) {
            if(it==current_unit_.begin()+1) {

              if(load_[i].size==1) {
                if(i==head) {
                  head=load_[i].next;
                  sum--;

                  directory_.write_info(sum,1);
                  directory_.write_info(head,2);
                  return;
                }

                for(int j=head;j;j=load_[j].next) {
                  if(load_[j].next==i) {
                    load_[j].next=load_[i].next;
                    sum--;
                    directory_.update(load_[1],2*sizeof(int),sum);
                    directory_.write_info(sum,1);
                    return;
                  }
                }
              }

              Unit<T>tmp=current_unit_[2];
              tmp.pos=load_[i].pos;
              tmp.next=load_[i].next;
              tmp.size=load_[i].size;
              load_[i]=tmp;
            }

            current_unit_.erase(it);
            load_[i].size--;
            body_.update(current_unit_[1],load_[i].pos,load_[i].size);
            directory_.update(load_[1],2*sizeof(int),sum);
            return;
          }
          it++;
        }
      }
    }
  }

  void find(Unit<T> item);

  void spilt(int place);

  void test_print() {
    int head=0,sum=0;
    directory_.get_info(sum,1);
    directory_.get_info(head,2);
    load_.resize(sum+1);
    directory_.read(load_[1],2*sizeof(int),sum);
    for(int i=head;i;i=load_[i].next) {
      current_unit_.resize(load_[i].size+1);
      body_.read(current_unit_[1],load_[i].pos,load_[i].size);
      std::cout<<"\nHEAD: "<<load_[i].index<<" "<<load_[i].value<<"\nBODY:\n";
      for(int j=1;j<=load_[i].size;++j) {
        std::cout<<current_unit_[j].index<<" "<<current_unit_[j].value<<"\n";
      }
    }
  }

  void unite();

  /*Method:insert_find
   *---------------------
   *返回 item 应该被归入的块编号
   */
  int insert_find(Unit<T> &item);
};

template <typename T>
Directory<T>::Directory(const string file_name) {
  directory_.initialise(file_name + "_directory.txt");
  body_.initialise(file_name + "_body.txt");
}

template <typename T>
void Directory<T>::insert(Unit<T> item) {
  int sum = 0;
  directory_.get_info(sum, 1);
  load_.resize(sum+1);
  directory_.read(load_[1], 2 * sizeof(int), sum);
  if (sum == 0) {
    sum++;
    Unit<T> tmp = item;
    tmp.size = 1;
    tmp.pos = body_.write(item, tmp.size);
    directory_.write(tmp, sum);
    directory_.write_info(sum, 1);
    directory_.write_info(1, 2);
    return;
  }
  int place = insert_find(item);
  current_unit_.resize(load_[place].size+1);
  body_.read(current_unit_[1], load_[place].pos, load_[place].size);
  auto it = std::upper_bound(current_unit_.begin()+1, current_unit_.begin() + load_[place].size+1, item);
  if (it == current_unit_.begin()+1) {
    Unit<T> tmp = item;
    tmp.next = load_[place].next;
    tmp.pos = load_[place].pos;
    tmp.size = load_[place].size;
    load_[place] = tmp;
  }
  if (it == current_unit_.end()) {
    current_unit_.push_back(item);
  } else {
    current_unit_.insert(it, item);
  }
  load_[place].size++;
  if (load_[place].size >= limit) {
    spilt(place);
  } else {
    body_.update(current_unit_[1], load_[place].pos, load_[place].size);
    directory_.update(load_[1], 2 * sizeof(int), sum );
  }
}


template <typename T>
int Directory<T>::insert_find(Unit<T> &item) {
  int head = 0, place = 0;
  directory_.get_info(head, 2);
  for (int i = head; i; i = load_[i].next) {
    if (!load_[i].next) {
      return i;
    }
    if (load_[load_[i].next] > item) {
      return i;
    }
  }
  return -1;
}

template <typename T>
void Directory<T>::spilt(int place) {
  int sum = 0, mid = load_[place].size / 2;  // mid为换走位置的起点
  directory_.get_info(sum, 1);
  sum++;
  directory_.write_info(sum, 1);
  Unit<T> tmp = current_unit_[mid];
  tmp.next = load_[place].next;
  load_[place].next = sum;
  tmp.size = load_[place].size - mid+1;
  tmp.pos = body_.write(current_unit_[mid], tmp.size);
  load_[place].size = mid-1;
  load_.push_back(tmp);
  directory_.update(load_[1], 2 * sizeof(int), sum );
  current_unit_.resize(mid);
  body_.update(current_unit_[1], load_[place].pos, load_[place].size);
}

template <typename T>
void Directory<T>::find(Unit<T> item) {
  int sum = 0, head = 0;
  directory_.get_info(sum, 1);
  directory_.get_info(head, 2);
  load_.resize(sum+1);
  directory_.read(load_[1], 2 * sizeof(int), sum);
  //load_[starter]<item<load[ender]
  //item could be in
  int starter = head, ender = 0;
  for (int i = head; i; i = load_[i].next) {
    int tmp=strcmp(load_[i].index,item.index);
    if (tmp<0) {
      starter = i;
    }
    if(tmp>0) {
      ender=i;
      break;
    }
  }
  bool flag=false;
  for(int i=starter;i!=ender;i = load_[i].next) {
    current_unit_.resize(load_[i].size+1);
    body_.read(current_unit_[1],load_[i].pos,load_[i].size);
    auto it=std::lower_bound(current_unit_.begin()+1,current_unit_.begin()+load_[i].size+1,item);
    if(it!=current_unit_.end()&&!strcmp(it->index,item.index)) {
      do {
        if(strcmp(it->index,item.index))break;
        flag=true;
        std::cout<<it->value<<" ";
        ++it;
      }while(it!=current_unit_.end());
    }
  }
  if(!flag) {
    std::cout<<"null\n";
  }else {
    std::cout<<"\n";
  }
}

template <typename T>
Unit<T>::Unit(const char * str) {
  strncpy(index,str,sizeof(index));
}

template <typename T>
Unit<T>::Unit(const char *str, T val):value(val) {
  strncpy(index,str,sizeof(index));
}

template <typename T>
bool Unit<T>::operator<(const Unit &other) const {
  int tmp=strcmp(index,other.index);
  if(tmp!=0) {
    return tmp<0;
  }
  return value<other.value;
}

template <typename T>
bool Unit<T>::operator>(const Unit &other) const {
  return other.operator<(*this);
}

template <typename T>
bool Unit<T>::operator<=(const Unit &other) const {
  return operator>(other)^1;
}

template <typename T>
bool Unit<T>::operator>=(const Unit &other) const {
  return operator<(other)^1;
}

int main() {
  Directory<int>dir("123");
  int n;
  char opt[80],tmp1[80];
  int tmp2;
  std::cin>>n;
  for(int i=1;i<=n;++i) {
    std::cin>>opt;
    switch (opt[0]) {
      case 'i':{
        std::cin>>tmp1>>tmp2;
        dir.insert(Unit<int>(tmp1,tmp2));
        break;
      }
      case 'd': {
        std::cin>>tmp1>>tmp2;
        dir.del(Unit<int>(tmp1,tmp2));
        break;
      }
      case 'f': {
        std::cin>>tmp1;
        dir.find(tmp1);
        break;
      }
      default: {
        dir.test_print();
        break;
      }
    }
  }
  return 0;
}