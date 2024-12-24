

#include "Quad2D.h"
#include "Renderer.h"

namespace sge {

Quad2D::Quad2D(){
        
    VertexData p1;
    p1.position.set(0, 0, 0);
    p1.normal.set(1, 0, 0);
    p1.color.set(1, 1, 1);
    p1.U=0;
    p1.V=1;
    VertexData p2;
    p2.position.set(1, 0, 0);
    p2.normal.set(1, 0, 0);
    p2.color.set(1, 1, 1);
    p2.U=1;
    p2.V=1;
    VertexData p3;
    p3.position.set(1, 1, 0);
    p2.color.set(1, 1, 1);
    p3.normal.set(1, 0, 0);
    p3.U=1;
    p3.V=0;
    VertexData p4;
    p4.color.set(1, 1, 1);
    p4.position.set(0, 1, 0);
    p4.normal.set(1, 0, 0);
    p4.U=0;
    p4.V=0;
    
    indices={3,0,1,1,2,3};

    std::vector<VertexData> data={p1,p2,p3,p4};
 
    
    mesh= new Mesh( MESH_COLORS | MESH_TEXCOORDS);
    
    for (int i=0; i<data.size(); i++) {
        
        mesh->positions.push_back(data[i].position);
        mesh->colors.push_back(data[i].color);
        mesh->texCoords.push_back(Vec2(data[i].U, data[i].V));
    }
    
    mesh->indices={3,0,1,1,2,3};
    mesh->update();
    
    setColor(Color::white);

}
    
void Quad2D::setUVCoords(const Vec2& leftDown, const Vec2& leftUp, const Vec2& rightUp, const Vec2& rightDown){
    
    std::vector<Vec2> uvs;
    
    uvs.push_back(leftDown);
    uvs.push_back(rightDown);
    uvs.push_back(rightUp);
    uvs.push_back(leftUp);
    
    mesh->setTexCoords(uvs);
    mesh->update();

}

void Quad2D::setFlipUVVertical(bool flip){
    
    std::vector<Vec2> uvs;
    
    uvs.push_back(Vec2(0,0));
    uvs.push_back(Vec2(1,0));
    uvs.push_back(Vec2(1,1));
    uvs.push_back(Vec2(0,1));

    mesh->setTexCoords(uvs);
    
    mesh->update();

}


void Quad2D::setColor(const Color& color){
        
    std::vector<Vec3> colors;
    
    for (int i=0; i<4; i++) colors.push_back(Vec3(color.r, color.g, color.b));
    mesh->setColors(colors);
    
    mesh->update();


}

void Quad2D::setRect(float x, float y, float width, float height){

    mesh->positions[0].set(x, y, 0);
    mesh->positions[1].set(x+width, y, 0);
    mesh->positions[2].set(x+width, y+height, 0);
    mesh->positions[3].set(x, y+height, 0);
    
    mesh->update();
    
}
    
Quad2D::~Quad2D(){
    
    mesh->clear();
    delete mesh;

}

}
