#ifndef __HGCalSimulation_FastShower_tree_h__
#define __HGCalSimulation_FastShower_tree_h__

#ifdef STANDALONE
#include "Cell.h"
#include "Rectangle.h"
#else
#include "HGCalSimulation/FastShower/interface/Cell.h"
#include "HGCalSimulation/FastShower/interface/Rectangle.h"
#endif

#include <vector>

class Tree {

  public:
    Tree(Rectangle*, int);
    ~Tree();

    bool empty();
    void addCell(Cell*);
    int countCells();
    std::vector<Cell*>* getCells();
    Tree* getLeaf(Point*);
    Tree* getLeaf(float, float);

  private:
    //4 childrens
    Tree* nw;
    Tree* ne;
    Tree* sw;
    Tree* se;

  void subdivide(int);

  // Cells selected in the tree
  std::vector<Cell*>* cells;

  protected:
  Rectangle* rectangle;
};

#endif
