#pragma once
#include "CHcn.h"
class Oso :
    public CHcn
{
public:
    
    //int sl;
    int dong;
    int so;
    //int gtri;
    Oso() :CHcn() {
        //sl = 0;
        so = 0;
        dong = 1;
    }
    void draw(CClientDC* dc);
    void draw(CPaintDC* dc);
    //int setNum(CPaintDC*dc, CPoint p, int num);
};

