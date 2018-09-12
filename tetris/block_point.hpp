#ifndef BLOCK_POINT
#define BLOCK_POINT
#include <array>
namespace tetris {
  template <const int xsize,const int ysize>
  struct BlockPoint {
  public:
    BlockPoint(int x, int y) {
      _x=x,_y=y;
    }
    BlockPoint(std::array<int,2> &array) {
      _x=array[0],_y=array[1];
    }
    BlockPoint(std::initializer_list<int> &array) {
      _x=*(array.begin()),_y=*(array.begin()+1);
    }
    BlockManager<xsize,ysize>&
    operator>>=(BlockManager<xsize,ysize>& bm) {
      bm._cur_block.x+=_x;
      bm._cur_block.y+=_y;
      return bm;
    }
    int operator[](int idx) {
      if(idx==0) {
        return _x;
      }
      else if(idx==1) {
        return _y;
      }
      else {
        return NULL;
      }
    }
  private:
    int _x,_y;
  };
}
#endif
