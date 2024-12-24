

#ifndef SGENGINE_VIEW_H
#define SGENGINE_VIEW_H

#include <iostream>
#include <vector>

#include "Sprite.h"
#include "Rectangle.h"

namespace sge {
    
class View: public Sprite{
    
    
private:
    void addChild(Node* Node) final;

protected:
    
    bool _userInteractionEnabled;
    Texture* _maskTexture;
    Color _tintColor;
    Vec2 _size;
    View();
    
    int _order;
    View* _parentView;
    
    float _internalZ;
    
    Rectangle _textureRect;

    void initWithSizeColorTexture(float x, float y,const Color& color, Texture* texture);
    void shouldReorderSubview(View* view);

public:
    
    bool isUserInteractionEnabled();
    
    void setOverlayColor(Color color);
    void setTintColor(Color color);
    void setMaskTexture(Texture* texture);
    
    void setTextureRect(const Rectangle& rect);
    
    void addSubview(View* view);

    void setZOrder(int order);
    void setBackgroundTexture(Texture* texture);
    
    static View* create(float Width, float Height, Color backgroundColor);
    static View* create(float Width, float Height, std::string imageFile);
    static View* create(float Width, float Height, Texture* texture);

    void setPosition(Vec2 point);
    void setPosition(float x, float y);
    
    void setTexture(Texture* texture);
    
    Vec2 getSize();
    void setSize(const Vec2& size);
    
    
};
    
}
#endif
