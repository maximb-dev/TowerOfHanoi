#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
 public:

  Tower(int disks_num) {
    FillTower(disks_num);
  }

  int GetDisksNum() const {
    return disks_.size();
  }

  void SetDisks(int disks_num) {
    FillTower(disks_num);
  }

  void AddToTop(int disk) {
    int top_disk_num = disks_.size() - 1;
    if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
      throw invalid_argument("Невозможно поместить большой диск на маленький");
    } else {
      disks_.push_back(disk);
    }
  }

  int RemoveFromTop() {
    int disk = disks_.back();
    disks_.pop_back();
    return disk;
  }

 private:
  vector<int> disks_;

  void FillTower(int disks_num) {
    for (int i = disks_num; i > 0; i--) {
      disks_.push_back(i);
    }
  }
};

void MoveDisk(int amount, Tower &source, Tower &destination, Tower &buffer) {
  if (amount > 1) {
    MoveDisk(amount - 1, source, buffer, destination);
  }
  int disk = source.RemoveFromTop();
  destination.AddToTop(disk);
  if (amount > 1) {
    MoveDisk(amount - 1, buffer, destination, source);
  }
}

void SolveHanoi(vector<Tower> &towers) {
  int disks_num = towers[0].GetDisksNum();

  MoveDisk(disks_num, towers[0], towers[2], towers[1]);
}

int main() {
  system("chcp 65001");
  int towers_num = 3;
  int disks_num = 3;
  vector<Tower> towers;
  for (int i = 0; i < towers_num; ++i) {
    towers.push_back(0);
  }
  towers[0].SetDisks(disks_num);

  SolveHanoi(towers);
}