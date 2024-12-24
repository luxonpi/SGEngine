

#include "TableView.h"

namespace sge {
    
    TableView::TableView(){
    
        
    }
    
    TableView::~TableView(){
    
        
        
    }
    
    void TableView::initTableView(Vec2 size, unsigned int rows, unsigned int columns){
    
        _cellTexture= Texture::get("assets/textures/cellBg.png");
        
        setSize(size.x, size.y);
        _numberOfColums=1;
        _numberOfRows=5;
        
        _padding.set(20, 20, 20, 20);
        _cellSize.set(50, 50);
        
        _marginBetweenRows=10;
        _marginBetweenColumns=10;
        
        _scrollBarVertical= View::create(5, size.y*0.6, Color(255,255,255, 0.05));
        _scrollBarVertical->setPosition(3, _size.y-size.y*0.6-10);
        this->addSubview(_scrollBarVertical);
        
        rePositionCells();
    
    }
    
    void TableView::setMargin(float rowMargin, float columnMargin){
    
        _marginBetweenRows=columnMargin;
        _marginBetweenColumns=rowMargin ;
        
        rePositionCells();

    }
    
    void TableView::setPadding(Vec4 padding){

        _padding=padding;
        rePositionCells();
    
    }
    
    void TableView::setCellSize(Vec2 cellSize){
    
        _cellSize=cellSize;
        rePositionCells();
    
    }
    
    void TableView::setScrollBarVisible(bool visible){
    
        _scrollBarVertical->getRenderObject()->setVisible(visible);
    
    }
    
    TableView* TableView::create(Vec2 size, unsigned int rows, unsigned int columns){
    
        TableView* table= new TableView();
        table->initTableView(size, rows, columns);
        return table;
    
    
    }
    
    void TableView::setSize(float width, float height){
    
        View::setSize(Vec2(width, height));
        
    
    }
    
    void TableView::rePositionCells(){
    
        _scrollBarVertical->setPosition(3, _size.y-_size.y*0.6-_padding.y);

        _numberOfColums= (_size.x-_padding.x-_padding.z ) / (_cellSize.x+_marginBetweenColumns);
        _numberOfRows= (_size.y-_padding.y-_padding.w ) / (_cellSize.y+_marginBetweenRows);
        
        int numberOfCells= _numberOfRows*_numberOfColums;
        
        while (_cells.size()>numberOfCells) {
            
            TableViewCell* cell= _cells.back();
            cell->removeFromParent();
            _cells.pop_back();
            
            delete cell;
            
        }
        
        
        while (_cells.size()<numberOfCells) {
            
            TableViewCell* cell= TableViewCell::create(_cellSize);
            cell->setTexture(_cellTexture);
            cell->setTintColor(Color(255, 255, 255, 0.05));
            
            _cells.push_back(cell);
            
            this->addSubview(cell);
            
        }
        
        float x=_padding.x;
        float y=_cellSize.y+_padding.y;
        
        for (int i=0; i<_cells.size(); i++) {
            
            TableViewCell* cell= _cells[i];
            cell->setPosition(x, _size.y-y);
            cell->setSize(Vec2(_cellSize.x, _cellSize.y));
            
            x+=_cellSize.x+ _marginBetweenColumns;
            
            if(x>=_size.x-_cellSize.x-_padding.z){
            
                x=_padding.x;
                y+=_cellSize.y+_marginBetweenRows;
            
            }
            
            
        }
        
    
    }
    

    
    
}