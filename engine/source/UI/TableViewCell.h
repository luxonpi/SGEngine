

#ifndef SGENGINE_TABLEVIEWCELL_H
#define SGENGINE_TABLEVIEWCELL_H

#include "SBase.h"
#include "View.h"

namespace sge{

    class TableViewCell: public View{
    
    private:
        
        
    public:
    
        static TableViewCell* create(Vec2 size);
    
    };


}


#endif