

#ifndef SGENGINE_TABLEVIEW_H
#define SGENGINE_TABLEVIEW_H

#include "SBase.h"

#include "View.h"
#include "TableViewCell.h"

namespace sge {
    
    class TableView: public View{
    
    protected:
        
        Texture* _cellTexture;
        
        Vec2 _cellSize;
        View* _scrollBarVertical;
        
        std::vector< TableViewCell* > _cells;
        
        unsigned int _numberOfColums;
        unsigned int _numberOfRows;
        
        float _marginBetweenRows;
        float _marginBetweenColumns;
        
        Vec4 _padding;

        TableView();
        ~TableView();
        
        void initTableView(Vec2 size, unsigned int rows, unsigned int columns);
        
        void rePositionCells();
        
        Vec2 _contentSize;
        Vec2 _offset;
        
    public:
        
        void setScrollBarVisible(bool visible);
        void setMargin(float rowMargin, float columnMargin);
        void setPadding(Vec4 padding);
        void setCellSize(Vec2 cellSize);
        
        static TableView* create(Vec2 size, unsigned int rows, unsigned int columns);
        virtual void setSize(float width, float height);
        
        
    
    };
    
}


#endif
