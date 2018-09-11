#ifndef BLOCK_MANAGER
#define BLOCK_MANAGER
#include <cmath>
#include "../basic_system/basic_system.hpp"
#include "env.hpp"
namespace tetris {
  struct Block{
  int x,y,block;
};
template <const int xsize,const int ysize>
  class CollideChecker;

  template <const int xsize,const int ysize>
  class BlockManager;

  template <const int xsize,const int ysize>
  class BlockManager {
  public:
    BlockManager() {
      _seq=basic_system::random::random_sequence<blocknumber>();
    }
    unsigned int
    rotate_r(unsigned int b) {
      return
        (((b&0x8000)>>3)|((b&0x800)<<2)|((b&0x80)<<7)|((b&0x8)<<12))|
        (((b&0x4000)>>6)|((b&0x400)>>1)|((b&0x40)<<4)|((b&0x4)<<9))|
        (((b&0x2000)>>9)|((b&0x200)>>4)|((b&0x20)<<1)|((b&0x2)<<6))|
        (((b&0x1000)>>12)|((b&0x100)>>7)|((b&0x10)>>2)|((b&0x1)<<3));
    }
    unsigned int
    rotate_l(unsigned int b) {
      return
        (((b&0x8000)>>12)|((b&0x800)>>9)|((b&0x80)>>6)|((b&0x8)>>3))|
        (((b&0x4000)>>7)|((b&0x400)>>4)|((b&0x40)>>1)|((b&0x4)<<2))|
        (((b&0x2000)>>2)|((b&0x200)<<1)|((b&0x20)<<4)|((b&0x2)<<7))|
        (((b&0x1000)<<3)|((b&0x100)<<6)|((b&0x10)<<9)|((b&0x1)<<12));
    }
    void move_block(int dx,int dy) {
      _cur_block.x+=dx;
      _cur_block.y+=dy;
    }
    void change_block() {
      int blockidx;
      _seq >>= blockidx;
      _cur_block.block=tetromino[blockidx];
      _cur_block.x=startx;
      _cur_block.y=starty;
    }
    inline BlockManager<xsize,ysize>&
    operator!() {
      change_block();
      return *this;
    }
    inline basic_system::Drawer<xsize,ysize>&
    operator>>=(basic_system::Drawer<xsize,ysize> &drawer) {
      drawer.draw_block(_cur_block.block,_cur_block.x,_cur_block.y);
      return drawer;
    }
    inline bool
    operator>>=(CollideChecker<xsize,ysize> &cc) {
      return cc.check(_cur_block.block,_cur_block.x,_cur_block.y);
    }
    template <typename T>
    inline BlockManager<xsize,ysize>&
    operator<<=(std::array<T,2> d) {
      _cur_block.x+=d[0];
      _cur_block.y+=d[1];
      return *this;
    }
    basic_system::random::random_sequence<blocknumber> _seq;
  protected:
    Block _cur_block;
  private:
  };
}
#endif
