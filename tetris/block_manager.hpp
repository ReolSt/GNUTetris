#ifndef BLOCK_MANAGER
#define BLOCK_MANAGER
#include <cmath>
#include "../GNUgbs/basic_system.hpp"
#include "env.hpp"
#include "block.hpp"
#include "block_point.hpp"
#include "block_stacker.hpp"
#include "block_holder.hpp"
#include "collide_checker.hpp"
namespace tetris _GLIBCXX_VISIBILITY(hidden){
  inline unsigned int
  _rotate_r(unsigned int b) {
    return
      (((b&0x8000)>>3)|((b&0x800)<<2)|((b&0x80)<<7)|((b&0x8)<<12))|
      (((b&0x4000)>>6)|((b&0x400)>>1)|((b&0x40)<<4)|((b&0x4)<<9))|
      (((b&0x2000)>>9)|((b&0x200)>>4)|((b&0x20)<<1)|((b&0x2)<<6))|
      (((b&0x1000)>>12)|((b&0x100)>>7)|((b&0x10)>>2)|((b&0x1)<<3));
  }
  inline unsigned int
  _rotate_l(unsigned int b) {
    return
      (((b&0x8000)>>12)|((b&0x800)>>9)|((b&0x80)>>6)|((b&0x8)>>3))|
      (((b&0x4000)>>7)|((b&0x400)>>4)|((b&0x40)>>1)|((b&0x4)<<2))|
      (((b&0x2000)>>2)|((b&0x200)<<1)|((b&0x20)<<4)|((b&0x2)<<7))|
      (((b&0x1000)<<3)|((b&0x100)<<6)|((b&0x10)<<9)|((b&0x1)<<12));
  }
}
namespace tetris {
  template <const int xsize,const int ysize>
  class BlockManager {
  public:
    BlockManager() {
      _seq=basic_system::random::random_sequence<blocknumber>();
      !(*this);
    }

    void move_block(int dx,int dy) {
      _cur_block.x+=dx;
      _cur_block.y+=dy;
    }


    inline unsigned int
    rotate_r() {
      return _cur_block.block=_rotate_r(_cur_block.block);
    }

    inline unsigned int
    rotate_l() {
      return _cur_block.block=_rotate_l(_cur_block.block);
    }

    inline BlockManager<xsize,ysize>&
    operator!() {
      change_block();
      return *this;
    }

    inline basic_system::GridDrawer<xsize,ysize>&
    operator>>=(basic_system::GridDrawer<xsize,ysize> &drawer) {
      drawer.draw_block(_cur_block.block,_cur_block.x,_cur_block.y);
      return drawer;
    }

    inline bool
    operator>>=(CollideChecker<xsize,ysize> &cc) {
      return cc.check(_cur_block.block,_cur_block.x,_cur_block.y);
    }

    inline BlockStacker<xsize,ysize>&
    operator>>=(BlockStacker<xsize,ysize> &bs) {
      bs.add_block(_cur_block.block, _cur_block.x, _cur_block.y);
      bs.check_lines();
    }

    inline BlockHolder&
    operator>>=(BlockHolder &bh) {
      if(!bh.hold_block(_cur_block)) {
        !(*this);
      }
      return bh;
    }
  protected:
    basic_system::random::random_sequence<blocknumber> _seq;
    Block _cur_block;
  private:
    void change_block() {
      int blockidx;
      _seq >>= blockidx;
      _cur_block.block=tetromino[blockidx];
      _cur_block.x=startx;
      _cur_block.y=starty;
    }
  };

}
#endif
