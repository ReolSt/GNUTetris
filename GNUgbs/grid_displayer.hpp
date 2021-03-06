#ifndef BASIC_SYSTEM_GRID_DISPLAYER
#define BASIC_SYSTEM_GRID_DISPLAYER
#include <iostream>
#include "ncursesw.hpp"
#include "grid.hpp"
namespace basic_system {
  template <const size_t xsize,const size_t ysize>
  class GridDisplayer {
  public:
    GridDisplayer(Grid2D<xsize,ysize> *grid) {
      this->_grid=grid;
    }
    inline std::ostream& clear(std::ostream &stream) {
      stream << "\033c";
      return stream;
    }
    inline std::ostream& operator>>=(std::ostream &stream) {
      clear(stream);
      for(int i=0;i<ysize;i++) {
        for(int j=0;j<xsize;j++) {
          stream << (*_grid)[i][j];
        }
        stream << "\n";
      }
      return stream;
   }
    inline
    ncursesw::WINDOW*
    operator>>=(ncursesw::WINDOW* scr) {
      for(int i=0;i<ysize;i++) {
        for(int j=0;j<xsize;j++) {
          ncursesw::wprintw(scr,"%c",(*_grid)[i][j]);
        }
        ncursesw::wprintw(scr,"\n");
      }
      return scr;
    }
  protected:
    Grid2D<xsize,ysize> *_grid;
  private:
    std::ostream& display(std::ostream &stream) {
      return this >>= stream;
    }
    std::ostream& display() {
      return this >>= std::cout;
    }
  };
}
#endif
